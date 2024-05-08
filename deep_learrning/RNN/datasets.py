import numpy as np
import pandas as pd
import torch
import torch.utils.data as data
import warnings
warnings.filterwarnings("ignore")

# 定义dataset
class my_Dataset(data.Dataset):
    def __init__(self, features, labels):
        self.X = features
        self.y = labels

    def __getitem__(self, index):
        return self.X[index], self.y[index]

    def __len__(self):
        return self.X.shape[0]


class TrafficDataset:
    def __init__(self, sensor=10, target=0):
        # 选取适当的检测器用作序列数据
        self.raw_data = np.load('./dataset/traffic-flow/traffic.npz')['data']
        self.sensor = sensor
        self.target = target

        # 数据标准化
        self.min = self.raw_data.min()
        self.max = self.raw_data.max()
        self.data = (self.raw_data - self.min) / (self.max - self.min)

    def denormalize(self, x):
        return x * (self.max - self.min) + self.min

    def construct_set(self, train_por=0.6, test_por=0.2, window_size=12, label=0):
        train_x = []
        train_y = []
        val_x = []
        val_y = []
        test_x = []
        test_y = []

        # 选择前20个传感器的数据
        data = self.data[:, :20, :]

        len_train = int(data.shape[0] * train_por)
        len_val = int(data.shape[0] * (train_por + test_por))

        # 训练集
        train_seqs = data[:len_train]
        for i in range(train_seqs.shape[0] - window_size):
            for j in range(train_seqs.shape[1]):
                train_x.append(train_seqs[i:i+window_size, j, :].squeeze())
                train_y.append(train_seqs[i+window_size, j, self.target].squeeze())

        # 验证集
        val_seqs = data[len_train:len_val]
        for i in range(val_seqs.shape[0] - window_size):
            for j in range(val_seqs.shape[1]):
                val_x.append(val_seqs[i:i+window_size, j, :].squeeze())
                val_y.append(val_seqs[i+window_size, j, self.target].squeeze())

        # 测试集
        test_seqs = data[len_val:]
        for i in range(test_seqs.shape[0] - window_size):
            for j in range(test_seqs.shape[1]):
                test_x.append(test_seqs[i:i+window_size, j, :].squeeze())
                test_y.append(test_seqs[i+window_size, j, self.target].squeeze())

        train_set = my_Dataset(torch.Tensor(train_x), torch.Tensor(train_y))
        val_set = my_Dataset(torch.Tensor(val_x), torch.Tensor(val_y))
        test_set = my_Dataset(torch.Tensor(test_x), torch.Tensor(test_y))
        return train_set, val_set, test_set



class FourSquareDataset:
    def __init__(self, data_path):
        # 适当修改数据读取过程
        self.raw_data = pd.read_csv(data_path)
        self.min = self.raw_data.min()
        self.max = self.raw_data.max()
        self.data = (self.raw_data - self.min) / (self.max - self.min)

    def denormalize(self, x, feat):
        return x * (self.max - self.min) + self.min

    def construct_set(self, train_por, test_por, window_size, label=0):
        train_x = []
        train_y = []
        val_x = []
        val_y = []
        test_x = []
        test_y = []

        # 补全构造过程
        pass

        train_set = my_Dataset(torch.Tensor(train_x), torch.Tensor(train_y))
        val_set = my_Dataset(torch.Tensor(val_x), torch.Tensor(val_y))
        test_set = my_Dataset(torch.Tensor(test_x), torch.Tensor(test_y))
        return train_set, val_set, test_set
