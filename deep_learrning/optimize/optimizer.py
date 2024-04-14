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
    
    def forward(self, x):
        # 定义前向传播
        x = self.input_layer(x)
        x = nn.ReLU()(self.hidden_layer1(x))
        x = nn.ReLU()(self.hidden_layer2(x))
        x = self.output_layer(x)
        return x


# In[6]:


# 手动实现RMSprop算法
def init_rmsprop_states(params):
    states = []
    for p in params:
        states.append(torch.zeros_like(p))
    return states
def rmsprop(params, states, lr, gamma, eps=1e-6):
    for p, s in zip(params, states):
        with torch.no_grad():
            s[:] = gamma * s + (1 - gamma) * torch.square(p.grad)
            p[:] -= lr * p.grad / torch.sqrt(s + eps)
        p.grad.data.zero_()


# In[7]:


# 训练函数
def train1(net, train_iter, loss, epochs, gamma):
    train_loss_list = []
    test_acc_list = []
    time_start = time.time()
    params = list(net.parameters())
    states = init_rmsprop_states(params)
    for epoch in range(epochs):
        train_l_sum, train_acc_sum, n, c = 0.0, 0.0, 0, 0
        for X, y in train_iter:
            y_hat = net(X)
            l = loss(y_hat, y)
            l.backward()
            rmsprop(params, states, lr, gamma)
            for p in params:
                if p.grad is not None:
                    p.grad.data.zero_()
            train_l_sum += l.item()
            train_acc_sum += (y_hat.argmax(dim=1) == y).sum().item()
            n += y.shape[0]
            c += 1
        test_acc = evaluate_accuracy(test_iter, net)
        train_loss_list.append(train_l_sum / c)
        test_acc_list.append(test_acc)
        print('epoch %d, train loss %.4f, train acc %.3f, test acc %.3f' % (epoch + 1, train_l_sum / c, train_acc_sum / n, test_acc))
    print("time spend: %.6f second" % (time.time() - time_start))
    draw_loss(train_loss_list, test_acc_list)


# In[8]:


epochs = 20
lr = 0.01
loss = nn.CrossEntropyLoss()
net = Net()
gamma = 0.9
train1(net, train_iter, loss, epochs, gamma)


# In[9]:


def train2(net, train_iter, loss, epochs, optimizer):
    train_loss_list = []
    test_acc_list = []
    time_start = time.time()
    for epoch in range(epochs):
        train_l_sum, train_acc_sum, n, c = 0.0,0.0, 0,0
        for X,y in train_iter:
            y_hat = net.forward(X)
            l = loss(y_hat,y)
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
    draw_loss(train_loss_list, test_acc_list)


# In[10]:


net = Net()
optimizer = torch.optim.RMSprop(net.parameters(), lr, alpha=0.99, eps=1e-6)
train2(net, train_iter, loss, epochs, optimizer)


# In[11]:


# 手动实现momentum算法
def init_momentum_states(params):
    states = []
    for p in params:
        states.append(torch.zeros_like(p))
    return states
def sgd_momentum(params, states , lr, momentum):
    for p, v in zip(params, states):
        with torch.no_grad():
            v[:] = momentum * v - p.grad
            p[:] += lr * v
        p.grad.data.zero_()


# In[12]:


def train3(net, train_iter, loss, epochs, momentum):
    train_loss_list = []
    test_acc_list = []
    time_start = time.time()
    params = list(net.parameters())
    states = init_rmsprop_states(params)
    for epoch in range(epochs):
        train_l_sum, train_acc_sum, n, c = 0.0, 0.0, 0, 0
        for X, y in train_iter:
            y_hat = net(X)
            l = loss(y_hat, y)
            l.backward()
            sgd_momentum(params, states, lr, momentum)
            for p in params:
                if p.grad is not None:
                    p.grad.data.zero_()
            train_l_sum += l.item()
            train_acc_sum += (y_hat.argmax(dim=1) == y).sum().item()
            n += y.shape[0]
            c += 1
        test_acc = evaluate_accuracy(test_iter, net)
        train_loss_list.append(train_l_sum / c)
        test_acc_list.append(test_acc)
        print('epoch %d, train loss %.4f, train acc %.3f, test acc %.3f' % (epoch + 1, train_l_sum / c, train_acc_sum / n, test_acc))
    print("time spend: %.6f second" % (time.time() - time_start))
    draw_loss(train_loss_list, test_acc_list)


# In[13]:


net = Net()
momentum = 0.5
train3(net, train_iter, loss, epochs, momentum)


# In[14]:


net = Net()
optimizer = torch.optim.SGD(net.parameters(), lr, momentum=0.5)
train2(net, train_iter, loss, epochs, optimizer)


# In[15]:


# 手动实现Adam算法
def init_adam_states(params):
    states = []
    for p in params:
        states.append((torch.zeros_like(p), torch.zeros_like(p)))
    return states
def adam(params, states , lr, t):
    beta1, beta2, eps =0.9, 0.999, 1e-6 
    for p, (v, s) in zip(params, states):
        with torch.no_grad():
            # Compute the first and second moment
            v[:] = beta1 * v + (1 - beta1) * p.grad
            s[:] = beta2 * s + (1 - beta2) * p.grad**2
            # Bias correction
            v_hat = v / (1 - beta1 ** t)
            s_hat = s / (1 - beta2 ** t)
            # Update the parameters
            p -= lr * v_hat / (torch.sqrt(s_hat) + eps)
        p.grad.data.zero_()
    t += 1


# In[16]:


def train3(net, train_iter, loss, epochs, t):
    train_loss_list = []
    test_acc_list = []
    time_start = time.time()
    params = list(net.parameters())
    states = init_adam_states(params)
    for epoch in range(epochs):
        train_l_sum, train_acc_sum, n, c = 0.0,0.0, 0,0
        for X, y in train_iter:
            y_hat = net(X)
            l = loss(y_hat, y)
            for p in params:
                if p.grad is not None:
                    p.grad.data.zero_()
            l.backward()
            adam(params, states, lr, t)
            train_l_sum += l.item()
            train_acc_sum += (y_hat.argmax(dim=1) == y).sum().item()
            n += y.shape[0]
            c += 1
        test_acc = evaluate_accuracy(test_iter, net)
        train_loss_list.append(train_l_sum / c)
        test_acc_list.append(test_acc)
        print('epoch %d, train loss %.4f, train acc %.3f, test acc %.3f' % (epoch + 1, train_l_sum / c, train_acc_sum / n, test_acc))
    print("time spend: %.6f second" % (time.time() - time_start))
    draw_loss(train_loss_list, test_acc_list)


# In[17]:


net = Net()
t = 1
train3(net, train_iter, loss, epochs, t)


# In[18]:


net = Net()
optimizer = torch.optim.Adam(net.parameters(), lr)
train2(net, train_iter, loss, epochs, optimizer)


# In[ ]:




