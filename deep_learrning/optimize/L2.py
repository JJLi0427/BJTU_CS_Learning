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


# minist数据集
mnist_train = torchvision.datasets.MNIST(root='~/Datasets/MNIST',train=True, download=True, transform=transforms.ToTensor())
mnist_test = torchvision.datasets.MNIST(root='~/Datasets/MNIST',train=False, transform=transforms.ToTensor())
# 通过DataLoader 读取小批量数据样本
batch_size = 128
train_iter = DataLoader(mnist_train, batch_size=batch_size, shuffle=True,num_workers=0)
test_iter = DataLoader(mnist_test, batch_size=batch_size, shuffle=False,num_workers=0)


# In[3]:


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


# In[4]:


# 测试准确率评价函数
def evaluate_accuracy(data_iter, model):
    acc_sum, n= 0.0, 0
    for X, y in data_iter:
        result = model.forward(X)
        acc_sum += (result.argmax(dim=1) == y).float().sum().item()
        n += y.shape[0]
    return acc_sum / n


# In[5]:


class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        num_inputs, num_outputs, num_hiddens1, num_hiddens2 = 784, 10, 256, 256
        self.W1 = nn.Parameter(torch.tensor(np.random.normal(0, 0.01, size=(num_hiddens1, num_inputs)), dtype=torch.float, requires_grad=True))
        self.b1 = nn.Parameter(torch.zeros(num_hiddens1, requires_grad=True))
        self.W2 = nn.Parameter(torch.tensor(np.random.normal(0, 0.01, size=(num_hiddens2, num_hiddens1)), dtype=torch.float, requires_grad=True))
        self.b2 = nn.Parameter(torch.zeros(num_hiddens2, requires_grad=True))
        self.W3 = nn.Parameter(torch.tensor(np.random.normal(0, 0.01, size=(num_outputs, num_hiddens2)), dtype=torch.float, requires_grad=True))
        self.b3 = nn.Parameter(torch.zeros(num_outputs, requires_grad=True))
        self.params = [self.W1, self.b1, self.W2, self.b2, self.W3, self.b3]
        # 定义模型结构
        self.input_layer = lambda x: x.view(x.shape[0], -1)
        self.hidden_layer1 = lambda x: torch.matmul(x, self.W1.t()) + self.b1
        self.hidden_layer2 = lambda x: torch.matmul(x, self.W2.t()) + self.b2
        self.output_layer = lambda x: torch.matmul(x, self.W3.t()) + self.b3
        
    # 定义𝐿2范数惩罚项
    def l2_penalty(self):
        return (self.W1**2).sum() / 2 + (self.W2**2).sum() / 2 + (self.W3**2).sum() / 2
    
    def forward(self, x):
        # 定义前向传播
        x = self.input_layer(x)
        x = nn.ReLU()(self.hidden_layer1(x))
        x = nn.ReLU()(self.hidden_layer2(x))
        x = self.output_layer(x)
        return x


# In[6]:


# 训练函数
def train(net, train_iter, loss_func, epochs, optimizer, lambd):
    train_loss_list = []
    test_acc_list = []
    time_start = time.time()
    for epoch in range(epochs):
        train_l_sum, train_acc_sum, n, c = 0.0,0.0, 0,0
        for X,y in train_iter:
            y_hat = net.forward(X)
            l = loss_func(y_hat,y) + lambd * net.l2_penalty()
            optimizer.zero_grad()
            l.backward()
            optimizer.step()
            train_l_sum += l.item()
            train_acc_sum += (y_hat.argmax(dim=1) == y).sum().item()
            n += y.shape[0]
            c += 1
        test_acc = evaluate_accuracy(test_iter, net)
        train_loss_list.append(train_l_sum / c)
        test_acc_list.append(test_acc)
        print('epoch %d, train loss %.4f, train acc %.3f, test acc %.3f' % (epoch + 1, train_l_sum / c, train_acc_sum / n, test_acc))
    print("time spend: %.6f second" % (time.time() - time_start))
    print('L2 norm of weights:', torch.norm(net.W1).item() + torch.norm(net.W2).item() + torch.norm(net.W3).item())
    draw_loss(train_loss_list, test_acc_list)


# In[7]:


epochs = 20
lr = 0.1
loss = nn.CrossEntropyLoss()
net = Net()
optimizer = torch.optim.SGD(net.parameters(), lr)
train(net, train_iter, loss, epochs, optimizer, 0)


# In[8]:


net = Net()
optimizer = torch.optim.SGD(net.parameters(), lr)
train(net, train_iter, loss, epochs, optimizer, 0.01)


# In[9]:


net = Net()
optimizer = torch.optim.SGD(net.parameters(), lr)
train(net, train_iter, loss, epochs, optimizer, 0.02)


# In[10]:


net = Net()
optimizer = torch.optim.SGD(net.parameters(), lr)
train(net, train_iter, loss, epochs, optimizer, 0.05)


# In[11]:


net = Net()
optimizer = torch.optim.SGD(net.parameters(), lr)
train(net, train_iter, loss, epochs, optimizer, 0.1)


# In[12]:


# 使用torch.nn实现L2正则化，要修改训练函数
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
        test_acc = evaluate_accuracy(test_iter, net)
        train_loss_list.append(train_l_sum / c)
        test_acc_list.append(test_acc)
        print('epoch %d, train loss %.4f, train acc %.3f, test acc %.3f' % (epoch + 1, train_l_sum / c, train_acc_sum / n, test_acc))
    print("time spend: %.6f second" % (time.time() - time_start))
    print('L2 norm of weights:', torch.norm(net.W1).item() + torch.norm(net.W2).item() + torch.norm(net.W3).item())
    draw_loss(train_loss_list, test_acc_list)


# In[13]:


net = Net()
optimizer = torch.optim.SGD(net.parameters(), lr, weight_decay = 0.01)
train1(net, train_iter, loss, epochs, optimizer)


# In[14]:


net = Net()
optimizer = torch.optim.SGD(net.parameters(), lr, weight_decay = 0.02)
train1(net, train_iter, loss, epochs, optimizer)


# In[15]:


net = Net()
optimizer = torch.optim.SGD(net.parameters(), lr, weight_decay = 0.05)
train1(net, train_iter, loss, epochs, optimizer)

