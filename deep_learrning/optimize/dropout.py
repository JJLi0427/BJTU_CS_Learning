#!/usr/bin/env python
# coding: utf-8

# In[1]:


import torch
import torch.nn as nn
import numpy as np
import torchvision
from torchvision import transforms
import time
from torch.utils.data import TensorDataset, DataLoader


# In[2]:


# 绘图函数
import matplotlib.pyplot as plt
def draw_loss(train_loss, test_acc):
    x = range(len(train_loss))
    # 创建一个1行2列的图像布局
    plt.figure(figsize=(10, 5))
    # 在第一个子图中绘制训练损失
    plt.subplot(1, 2, 1)
    plt.plot(x, train_loss, label="Train Loss")
    plt.xlabel("Epoch")
    plt.ylabel("Loss")
    plt.legend()
    # 在第二个子图中绘制测试精度
    plt.subplot(1, 2, 2)
    plt.plot(x, test_acc, color='r', label="Test Acc")
    plt.xlabel("Epoch")
    plt.ylabel("Accuracy")
    plt.legend()
    plt.tight_layout()
    plt.show()


# In[3]:


# minist数据集
mnist_train = torchvision.datasets.MNIST(root='~/Datasets/MNIST',train=True, download=True, transform=transforms.ToTensor())
mnist_test = torchvision.datasets.MNIST(root='~/Datasets/MNIST',train=False, transform=transforms.ToTensor())
# 通过DataLoader 读取小批量数据样本
batch_size = 128
train_iter = DataLoader(mnist_train, batch_size=batch_size, shuffle=True,num_workers=0)
test_iter = DataLoader(mnist_test, batch_size=batch_size, shuffle=False,num_workers=0)


# In[4]:


class Net(nn.Module):
    #网络定义
    def __init__(self,dropout=0.0):
        self.dropout = dropout
        num_inputs, num_outputs, num_hiddens1, num_hiddens2 = 784, 10, 256, 256
        W1 = torch.tensor(np.random.normal(0, 0.01, size=(num_hiddens1, num_inputs)), dtype=torch.float, requires_grad=True)
        b1 = torch.zeros(num_hiddens1, requires_grad=True)
        W2 = torch.tensor(np.random.normal(0, 0.01, size=(num_hiddens2, num_hiddens1)), dtype=torch.float, requires_grad=True)
        b2 = torch.zeros(num_hiddens2, requires_grad=True)
        W3 = torch.tensor(np.random.normal(0, 0.01, size=(num_outputs, num_hiddens2)), dtype=torch.float, requires_grad=True)
        b3 = torch.zeros(num_outputs, requires_grad=True)
        self.params = [W1, b1, W2, b2, W3, b3]
        # 定义模型结构
        self.input_layer = lambda x: x.view(x.shape[0], -1)
        self.hidden_layer1 = lambda x: torch.matmul(x, W1.t()) + b1
        self.hidden_layer2 = lambda x: torch.matmul(x, W2.t()) + b2
        self.output_layer = lambda x: torch.matmul(x, W3.t()) + b3
    
    # 训练状态
    def train(self):
        self.is_train = True
    def test(self):
        self.is_train = False
    
    def dropout_layer(self, x):
        dropout =self.dropout
        assert 0 <= dropout <= 1 
        #丢弃率在0-1之间
        if dropout == 1:
            return torch.zeros_like(x)
        if dropout == 0:
            return x
        #生成mask矩阵(向量)
        mask = (torch.rand(x.shape) < 1.0 - dropout).float()
        return mask * x / (1.0 - dropout)
    
    def forward(self, x):
        # 定义前向传播
        x = self.input_layer(x)
        if self.is_train:
            x = self.dropout_layer(x) 
        x = nn.ReLU()(self.hidden_layer1(x))
        if self.is_train:
            x = self.dropout_layer(x) 
        x = nn.ReLU()(self.hidden_layer2(x))
        if self.is_train:
            x = self.dropout_layer(x)
        x = self.output_layer(x)
        return x


# In[5]:


# 测试准确率评价函数
def evaluate_accuracy(data_iter, model):
    acc_sum, n= 0.0, 0
    for X, y in data_iter:
        result = model.forward(X)
        acc_sum += (result.argmax(dim=1) == y).float().sum().item()
        n += y.shape[0]
    return acc_sum / n


# In[6]:


# 训练函数
def train(net, train_iter, loss_func, epochs, optimizer):
    train_loss_list = []
    test_acc_list = []
    time_start = time.time()
    for epoch in range(epochs):
        train_l_sum, train_acc_sum, n, c = 0.0,0.0, 0,0
        # 训练状态
        net.train()
        for X,y in train_iter:
            y_hat = net.forward(X)
            l = loss_func(y_hat,y)
            optimizer.zero_grad()
            l.backward()
            optimizer.step()
            train_l_sum += l.item()
            train_acc_sum += (y_hat.argmax(dim=1) == y).sum().item()
            n += y.shape[0]
            c += 1
        # 测试状态
        net.test()
        test_acc = evaluate_accuracy(test_iter, net)
        train_loss_list.append(train_l_sum / c)
        test_acc_list.append(test_acc)
        print('epoch %d, train loss %.4f, train acc %.3f, test acc %.3f' % (epoch + 1, train_l_sum / c, train_acc_sum / n, test_acc))
    print("time spend: %.6f second" % (time.time() - time_start))
    draw_loss(train_loss_list, test_acc_list)


# In[7]:


epochs = 20
lr = 0.1
loss = nn.CrossEntropyLoss()


# In[8]:


net = Net() # 先使dropout为0
optimizer = torch.optim.SGD(net.params, lr)
train(net, train_iter, loss, epochs, optimizer)


# In[9]:


net = Net(0.2) # dropout为0.2
optimizer = torch.optim.SGD(net.params, lr)
train(net, train_iter, loss, epochs, optimizer)


# In[10]:


net = Net(0.5) # dropout为0.5
optimizer = torch.optim.SGD(net.params, lr)
train(net, train_iter, loss, epochs, optimizer)


# In[11]:


net = Net(0.8) # dropout为0.8
optimizer = torch.optim.SGD(net.params, lr)
train(net, train_iter, loss, epochs, optimizer)


# In[12]:


# torch.nn.Dropout层实现dropout
class FlattenLayer(torch.nn.Module):
    def __init__(self):
        super(FlattenLayer, self).__init__()
    def forward(self, x):
        return x.view(x.shape[0], -1)


# In[13]:


# 准确率计算函数
def evaluate_accuracy1(data_iter, net):
    acc_sum, n = 0.0, 0
    for X, y in data_iter:
        if isinstance(net,torch.nn.Module):
            net.eval() 
            #评估模式，不使用dropout
            acc_sum += (net (X).argmax (dim=1) == y).float ().sum().item()
            net.train()
            # 改回训练模式
        n += y.shape[0]
    return acc_sum / n


# In[14]:


def train1(net, train_iter, loss_func, epochs, optimizer):
    train_loss_list = []
    test_acc_list = []
    time_start = time.time()
    for epoch in range(epochs):
        train_l_sum, train_acc_sum, n, c = 0.0,0.0, 0,0
        for X,y in train_iter:
            y_hat = net.forward(X)
            l = loss_func(y_hat,y)
            optimizer.zero_grad()
            l.backward()
            optimizer.step()
            train_l_sum += l.item()
            train_acc_sum += (y_hat.argmax(dim=1) == y).sum().item()
            n += y.shape[0]
            c += 1
        test_acc = evaluate_accuracy1(test_iter, net)
        train_loss_list.append(train_l_sum / c)
        test_acc_list.append(test_acc)
        print('epoch %d, train loss %.4f, train acc %.3f, test acc %.3f' % (epoch + 1,train_l_sum / c, train_acc_sum / n, test_acc))
    print("time spend: %.6f second" % (time.time() - time_start))
    draw_loss(train_loss_list, test_acc_list)


# In[15]:


# 神经网络模型
def Net1(drop_prob): # 根据dropout的值来初始化
    drop_prob = 0.2
    net_pytorch = nn.Sequential(
        FlattenLayer(),
        nn.Linear(num_inputs, num_hiddens1),
        nn.ReLU(),
        nn.Dropout(drop_prob),
        nn.Linear(num_hiddens1, num_hiddens2),
        nn.ReLU(),
        nn.Dropout(drop_prob),
        nn.Linear(num_hiddens2, 10)
    )
    for param in net_pytorch.parameters():
        nn.init.normal_(param, mean=0, std=0.01)
    return net_pytorch


# In[16]:


num_inputs = 784
num_hiddens1 = 256
num_hiddens2 = 256


# In[17]:


net = Net1(0.2) # dropout为0.2
optimizer = torch.optim.SGD(net.parameters(), lr)
train1(net, train_iter, loss, epochs, optimizer)


# In[18]:


net = Net1(0.5) # dropout为0.5
optimizer = torch.optim.SGD(net.parameters(), lr)
train1(net, train_iter, loss, epochs, optimizer)


# In[19]:


net = Net1(0.8) # dropout为0.8
optimizer = torch.optim.SGD(net.parameters(), lr)
train1(net, train_iter, loss, epochs, optimizer)

