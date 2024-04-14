#!/usr/bin/env python
# coding: utf-8

# In[1]:


import torch  
import torchvision
from torchvision import transforms
import numpy as np  
import random  
from matplotlib import pyplot as plt  
import os  
import shutil
import torch.nn as nn 
import time  
device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
# 启用CUDA加速


# In[2]:


def draw(acc1, acc2, loss1, loss2):
    x = range(len(acc1))
    # 创建一个1行2列的图像布局
    plt.figure(figsize=(8, 3))
    # 画图函数
    plt.subplot(1, 2, 1)
    plt.plot(x, acc1, label="train")
    plt.plot(x, acc2, color='r', label="test")
    plt.xlabel("epoch")
    plt.ylabel("acc")
    plt.legend()
    plt.subplot(1, 2, 2)
    plt.plot(x, loss1, label="train")
    plt.plot(x, loss2, color='r', label="test")
    plt.xlabel("epoch")
    plt.ylabel("loss")
    plt.legend()
    plt.tight_layout()
    plt.show()


# In[3]:


def reset(folders):
    for folder in folders:
        for filename in os.listdir(folder):
            filepath = os.path.join(folder, filename)
            if os.path.isfile(filepath) or os.path.islink(filepath):
                os.unlink(filepath)
            elif os.path.isdir(filepath):
                shutil.rmtree(filepath)

# 重置训练集和测试集
folders = ['./cardata/train/car', 
           './cardata/train/bus', 
           './cardata/train/truck',
           './cardata/test/car', 
           './cardata/test/bus', 
           './cardata/test/truck']

# 划分数据集函数
def makedata():
    random.seed(0)
    datapath = os.path.join(os.getcwd(), "cardata")
    traindata = os.path.join(datapath, "train")
    testdata = os.path.join(datapath, "test")
    types = ['car', 'bus', 'truck']
    for t in types:
        tpath = os.path.join(datapath, t)
        images = os.listdir(tpath)
        num = len(images)
        testimg = random.sample(images, k=int(num * 0.25)) # 25%做测试集
        for _, img in enumerate(images):
            if img in testimg:
                # 制作测试集
                imgpath = os.path.join(tpath, img)
                topath = os.path.join(testdata, t)
                shutil.copy(imgpath, topath)
            else:
                # 制作训练集
                imgpath = os.path.join(tpath, img)
                topath = os.path.join(traindata, t)
                shutil.copy(imgpath, topath)


# In[4]:


reset(folders)
makedata()
data_transform = {"train": transforms.Compose([transforms.Resize((64 ,64)), # 拉伸到统一大小
                            transforms.RandomHorizontalFlip(),
                            transforms.ToTensor(),
                            transforms.Normalize((0.5, 0.5, 0.5),(0.5, 0.5, 0.5))]),
                  "test": transforms.Compose([transforms.Resize((64, 64)),
                            transforms.ToTensor(),
                            transforms.Normalize((0.5, 0.5, 0.5),(0.5, 0.5, 0.5))])}

batch_size = 1024
train_dataset = torchvision.datasets.ImageFolder(root = os.path.join(os.getcwd(), "cardata/train"), transform = data_transform["train"])
train_loader = torch.utils.data.DataLoader(train_dataset, batch_size, shuffle = True, num_workers = 8)
test_dataset = torchvision.datasets.ImageFolder(root = os.path.join(os.getcwd(), "cardata/test"), transform = data_transform["test"])
test_loader = torch.utils.data.DataLoader(test_dataset, batch_size, shuffle=False, num_workers = 8)


# In[5]:


# 单通道卷积
def corr2d(X,K):
    batch_size,H,W = X.shape
    k_h,k_w = K.shape
    # 初始化结果矩阵
    Y = torch.zeros((batch_size, H - k_h + 1, W - k_w + 1)).to(device)
    for i in range(Y.shape[1]):  
        for j in range(Y.shape [2]):  
            Y[:, i, j] = (X[:, i: i + k_h, j: j + k_w] *  K).sum()  
    return Y

# 多通道卷积
def corr2d_multi_in(X,K):
    res = corr2d(X[:, 0, :, :], K[0, :, :])  
    for i in range(1, X.shape[1]):  
        # 按通道相加  
        res += corr2d(X[:, i, :, :], K[i, :, :])  
    return res

# 多输入/输出通道卷积
def corr2d_multi_in_out(X, K):  
    return torch.stack([corr2d_multi_in(X, k) for k in K],dim=1) 


# In[6]:


class MyConv2D(nn.Module):  
    def __init__(self,in_channels, out_channels,kernel_size):  
        super(MyConv2D,self).__init__()  
        # 初始化卷积层的2个参数:卷积核、偏差
        if isinstance(kernel_size,int):  
            kernel_size = (kernel_size,kernel_size)  
            self.weight = nn.Parameter(torch.randn((out_channels, in_channels) + kernel_size)).to(device)  
            self.bias = nn.Parameter(torch.randn(out_channels, 1, 1)).to(device)  
    def forward(self,x):    
        # x:输入图片，维度(batch_size,C_in,H,W) 
        return corr2d_multi_in_out(x, self.weight) + self.bias


# In[7]:


# 手动实现
class MyConvModule(nn.Module):  
    def __init__(self):  
        super(MyConvModule,self).__init__()  
        # 定义一层卷积层  
        self.conv = nn.Sequential(  
            MyConv2D(in_channels = 3,out_channels = 32,kernel_size = 3),  
            nn.BatchNorm2d(32),
            nn.ReLU(inplace=True))  
        # 输出层,将通道数变为分类数量  
        self.fc = nn.Linear(32, 3)  

    def forward(self,x):  
        # 图片经过一层卷积，输出维度变为(batch_size,C_out,H,W)  
        out = self.conv(x)  
        # 使用平均池化层将图片的大小变为1x1
        out = nn.functional.avg_pool2d(out,62)  
        # 将张量out从shape batchx32x1x1 变为 batch x32  
        out = out.squeeze()  
        # 输入到全连接层将输出的维度变为3  
        out = self.fc(out)  
        return out


# In[8]:


# 定义训练和测试函数
def trainmodel(net, traindata):  
    net.train() # 训练模式  
    train_batch_num = len(traindata)
    total_1oss = 0   
    correct = 0 
    sample_num = 0
    # 遍历batch进行训练  
    for i,(data, target) in enumerate (traindata): 
        data = data.to(device).float()  
        target = target.to(device).long()  
        optimizer.zero_grad()  
        output = net(data)  
        loss = criterion(output, target.squeeze())  
        loss.backward()  
        optimizer.step()  
        total_1oss += loss.item( )  
        # 预测类别，选择最大概率的
        prediction = torch.argmax(output, 1)  
        # 计算正确的数量  
        correct += (prediction == target).sum().item()    
        sample_num += len(prediction)
    # 计算loss和acc  
    loss = total_1oss / train_batch_num  
    acc = correct / sample_num  
    return loss, acc  

def testmodel(net, testdata):  
    net.eval() # 测试模式
    test_batch_num = len(testdata)  
    total_loss = 0  
    correct = 0  
    sample_num = 0  
    # 关闭梯度变化  
    with torch.no_grad():  
        for _,(data, target) in enumerate(testdata):  
            data = data.to(device).float()  
            target = target.to(device).long()   
            output = net(data)  
            loss = criterion(output, target)  
            total_loss += loss.item( )  
            prediction = torch.argmax(output, 1)  
            correct += (prediction == target).sum().item()  
            sample_num += len(prediction)  
    loss = total_loss / test_batch_num  
    acc = correct / sample_num  
    return loss,acc


# In[9]:


# 模型初始化
lr = 0.01
epochs = 10
net = MyConvModule().to(device)  
criterion = nn.CrossEntropyLoss()  
optimizer = torch.optim.Adam(net.parameters(),lr = lr)   
train_loss_list = []  
train_acc_list = []  
test_loss_list = []  
test_acc_list = []
timestart = time.time() 
for epoch in range(epochs):  
    print('Epoch %d: '%(epoch+1), end="")
    train_loss, train_acc = trainmodel(net, train_loader)
    print('train: loss %.6f acc %.6f; '%(train_loss, train_acc), end="") 
    test_loss, test_acc = testmodel(net, test_loader)  
    print('test: loss %.6f, acc %.6f'%(test_loss, test_acc))
    train_loss_list.append(train_loss)  
    train_acc_list.append(train_acc )  
    test_loss_list.append(test_loss)  
    test_acc_list.append(test_acc)      
spendtime = (time.time() - timestart)  
print('Spend time: %.3f'%(spendtime)) 
draw(train_acc_list, test_acc_list, train_loss_list, test_loss_list)
del net  # 删除对模型
torch.cuda.empty_cache()  # 释放显存


# In[10]:


# pytorch实现二维卷积
class ConvModule3(nn.Module):  
    def __init__(self):  
        super(ConvModule3,self).__init__()  
        # 三层卷积层  
        self.conv = nn.Sequential(  
            nn.Conv2d(in_channels = 3,out_channels = 32, kernel_size = 3 , stride = 1,padding=0), nn.BatchNorm2d(32), nn.ReLU(inplace=True),  
            nn.Conv2d(in_channels = 32,out_channels = 64, kernel_size = 3 , stride = 1,padding=0), nn.BatchNorm2d(64), nn.ReLU(inplace=True),  
            nn.Conv2d(in_channels = 64,out_channels = 128, kernel_size = 3 , stride = 1,padding=0), nn.BatchNorm2d(128), nn.ReLU(inplace=True)  )  
        # 输出层,将通道数变为分类数量  
        self.fc = nn.Linear(128, 3)  
    def forward(self,x):  
        # 图片经过三层卷积，输出维度变为(batch_size,C_out,H,W)  
        out = self.conv(x)  
        # 使用平均池化层将图片的大小变为 1 x 1
        out = nn.functional.avg_pool2d(out, 58)  
        # 将张量out从shape batch x 128 x 1 x 1 变为 batch x 128  
        out = out.squeeze()  
        # 输入到全连接层将输出的维度变为3  
        out = self.fc(out)  
        return out 
    def __str__(self):
        return "ConvModule3"


# In[11]:


# 增加到四层卷积
class ConvModule4(nn.Module):  
    def __init__(self):  
        super(ConvModule4,self).__init__()  
        self.conv = nn.Sequential(  
            nn.Conv2d(in_channels = 3,out_channels = 32, kernel_size = 3 , stride = 1,padding=0), nn.BatchNorm2d(32), nn.ReLU(inplace=True),  
            nn.Conv2d(in_channels = 32,out_channels = 64, kernel_size = 3 , stride = 1,padding=0), nn.BatchNorm2d(64), nn.ReLU(inplace=True),  
            nn.Conv2d(in_channels = 64,out_channels = 128, kernel_size = 3 , stride = 1,padding=0), nn.BatchNorm2d(128), nn.ReLU(inplace=True),
            nn.Conv2d(in_channels = 128,out_channels = 256, kernel_size = 3 , stride = 1,padding=0), nn.BatchNorm2d(256), nn.ReLU(inplace=True)
        )  
        # 输出层,将通道数变为分类数量  
        self.fc = nn.Linear(256, 3)  
    def forward(self,x):  
        out = self.conv(x)  
        out = nn.functional.avg_pool2d(out,54)  
        out = out.squeeze()   
        out = self.fc(out)  
        return out 
    def __str__(self):
        return "ConvModule4"


# In[12]:


# 降低数据集batchsize,pytorch的计算方式显存占用更高
batch_size = 128
train_dataset = torchvision.datasets.ImageFolder(root = os.path.join(os.getcwd(), "cardata/train"), transform = data_transform["train"])
train_loader = torch.utils.data.DataLoader(train_dataset, batch_size, shuffle = True, num_workers = 8)
test_dataset = torchvision.datasets.ImageFolder(root = os.path.join(os.getcwd(), "cardata/test"), transform = data_transform["test"])
test_loader = torch.utils.data.DataLoader(test_dataset, batch_size, shuffle=False, num_workers = 8)


# In[14]:


epochs = 30
netlist = [ConvModule3().to(device), ConvModule4().to(device)] 
for net in netlist:
    print(net)
    optimizer = torch.optim.Adam(net.parameters(),lr = lr)   
    train_loss_list = []  
    train_acc_list = []  
    test_loss_list = []  
    test_acc_list = []   
    timestart = time.time()  
    for epoch in range(epochs):  
        print('Epoch %d: '%(epoch+1), end="")
        train_loss, train_acc = trainmodel(net, train_loader)
        print('train: loss %.6f acc %.6f; '%(train_loss, train_acc), end="") 
        test_loss, test_acc = testmodel(net, test_loader)  
        print('test: loss %.6f, acc %.6f'%(test_loss, test_acc))
        train_loss_list.append(train_loss)  
        train_acc_list.append(train_acc )  
        test_loss_list.append(test_loss)  
        test_acc_list.append(test_acc)    
    spendtime = (time.time() - timestart)  
    print('Spend time: %.3f'%(spendtime)) 
    draw(train_acc_list, test_acc_list, train_loss_list, test_loss_list)
    del net
    torch.cuda.empty_cache()


# In[15]:


# 超参数对比分析
lr_list = [0.1, 0.001]
for lr in lr_list :
    print("lr: ",lr)
    net = ConvModule3().to(device) 
    optimizer = torch.optim.Adam(net.parameters(),lr = lr)
    train_loss_list = []  
    train_acc_list = []  
    test_loss_list = []  
    test_acc_list = []   
    timestart = time.time()  
    for epoch in range(epochs):  
        train_loss, train_acc = trainmodel(net, train_loader)  
        test_loss, test_acc = testmodel(net, test_loader)  
        train_loss_list.append(train_loss)  
        train_acc_list.append(train_acc )  
        test_loss_list.append(test_loss)  
        test_acc_list.append(test_acc)  
        print('epoch %d: train:loss %.6f acc %.6f; test:loss %.6f, acc %.6f'%(epoch+1, train_loss, train_acc, test_loss, test_acc)) 
    spendtime = (time.time() - timestart)  
    print('Spend time: %.3f'%(spendtime)) 
    draw(train_acc_list, test_acc_list, train_loss_list, test_loss_list)
    del net
    torch.cuda.empty_cache()


# In[ ]:




