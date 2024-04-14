#pragma once
//这里是为了避免编译时候出现冲突

#define MAX_STR_LEN 100

typedef struct configinfo {
    char filesavepath[MAX_STR_LEN];     	 //用于存放数据记录文件的存储目录
    char filename[MAX_STR_LEN];              //用于存储数据记录文件的文件名信息
    int number;		                         //用于存放生成的记录条数
    int maxvalue1;   		                 //用于存放实验2中生成的数据记录三元组中第1、2个元素取值的上限
    int minvalue1; 		                     //用于存放实验2中生成的数据记录三元组中第1、2个元素取值的下限
    int maxvalue2;   	                     //用于存放实验2中生成的数据记录三元组中第3个元素取值的上限
    int minvalue2; 		                     //用于存放实验2中生成的数据记录三元组中第3个元素取值的下限
    int recordcount1;	                     //用于存放数据记录文件需要随机生成记录条数时条数值的上限
    int recordcount2;	                     //用于存放数据记录文件需要随机生成记录条数时条数值的下限
    int workmode;                            //用指定程序默认工作模式
} CONF;
//有关配置文件.ini的结构体

typedef struct DataItem{
    int item1;     //数据记录三元组第一个元素
    int item2;     //数据记录三元组第二个元素
    int item3;     //数据记录三元组第三个元素
} DataItem;
//需要用到的存储结构体

typedef struct Node{
    int item1;
    int item2;
    int item3;
    Node *next;
}Node, *Link;     
//链表的存储结构