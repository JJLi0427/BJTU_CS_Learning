#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MSIZE 100
 
typedef struct{
    char **data;
    int top;
    int size;
}Stack;
//结构体定义栈
 
typedef struct{
    char **data;
    int size;
    int front;
    int rear;
}Queue;
//定义一个队列，顺序存储
 
void InitStack(Stack &S, int n){
    S.data = (char **)malloc(n*sizeof(char *));
    for(int i = 0; i < n; i++)
    {
        S.data[i] = (char *)malloc(MSIZE*sizeof(char));
    }
    S.top = 0;
    S.size = n;
}
//根据用户自定义的停车场容量n初始化栈
 
void PushStack(Stack &S){
    char a;
    scanf("%s", S.data[S.top]);
    S.top++;
}
//入栈操作，车进入车库
 
char *PopStack(Stack &S){
    char *a;
    S.top--;
    a = S.data[S.top];
    return a;
}
//出栈操作，车离开停车场
 
void PrintStack(Stack &S){
    printf("停车场的车辆:\n");
    if(S.top == 0)
    {
        printf("NONE\n");//停车场没有车输出NONE
    }
    else
    {
        for(int i = S.top-1; i >= 0; i--)
        {
            printf("%s\n", S.data[i]);
        }
    }
}
//打印栈内容，显示停车场内全部车辆信息
 
void InitQueue(Queue &Q, int m){
    Q.data = (char **)malloc(m*sizeof(char *));
    for(int i = 0; i < m; i++)
    {
        Q.data[i] = (char *)malloc(MSIZE*sizeof(char));
    }
    Q.size = m;
    Q.front = 0;
    Q.rear = 0;
}
//初始化排队等候的车的队列，队列大小m由用户指定
 
void EnQueue(Queue &Q){
    char a[MSIZE];
    scanf("%s", Q.data[Q.rear]);
    Q.rear++;
}
//入队操作，车辆进入排队
 
char *OutQueue(Queue &Q){
    char *a;
    a = Q.data[Q.front++];
    return a;
}
//出队操作，车离队进入停车场
 
void PrintQueue(Queue &Q){
    printf("队列中的车辆:\n");
    if(Q.front-Q.rear == 0)
    {
        printf("NONE\n");//队列为空输出NONE
    }
    else
    {
        for(int i = Q.front; i < Q.rear; i++)
        {
            printf("%s\n", Q.data[i]);
        }
    }
}
//打印队列，输出在排队的所有车辆信息
 
int Deploy(Stack &S, Queue &Q, int x){
    if(x > S.size + Q.size)//超出容量，程序报错
    {
        printf("输入错误，程序结束！\n");
        return -1;//错误时返回0
    }
    printf("请输依次输入这些车的车牌\n");
    if(x <= S.size)
    {
        for(int i = 0; i < x; i++)
        {
            PushStack(S);
        }
        printf("所有车辆进入停车场\n");
        return 0;
    }
    else
    {
        for(int i = 0; i < S.size; i++)//前n辆车入栈
        {
            PushStack(S);
        }
        for(int i = 0; i < x-S.size; i++)//其余进入队列
        {
            EnQueue(Q);
        }
        printf("前%d辆车进入停车场，其余进入队列等候\n", S.size);
        return 0;
    }
}
 
int Come(Stack &S, Queue &Q){
            if(S.top == S.size)//先判断停车场有没有满，没满就直接进入停车场
            {
                printf("停车场已满\n");
            }
            else
            {
                printf("请输入车牌号\n");
                PushStack(S);
                printf("车辆停入停车场\n");
                return 0;
            }
            if(Q.front-Q.rear == Q.size)//判断队列是否满，不满则在队列中排队
            {
                printf("队列已满，无法再新增车辆！\n");
            }
            else
            {
                printf("请输入车牌号\n");
                EnQueue(Q);
                printf("车辆进入队列等待\n");
                return 0;
            }
}
//有车辆到来时的操作
 
void Leave(Stack &S, Queue &Q){
    char a[MSIZE];
    printf("请输入要离开停车场的车牌号\n");
    scanf("%s", a);//获取需要出停车场的车牌
    int flag = 0;//用flag表示离开停车场是否成功
    Stack S1;//新建一个栈暂存需要暂时出停车场的车
    InitStack(S1, S.size);
    int count = 0;//记录出库车的数量
    for(int i = S.top-1; i >= 0; i--)//在栈中查找
    {
        if(strcmp(S.data[i], a) != 0)
        {
            count++;
            strcpy(S1.data[S1.top], PopStack(S));//如果不是指定的车，先出栈，存到暂存栈
            S1.top++;
        }
        else
        {
            flag = 1;
            PopStack(S);//找到指定的车，出栈，结束查找
            printf("这辆车成功离开停车场\n");
            break;
        }
    }
    for(int i = 0; i < count; i++)
    {
        strcpy(S.data[S.top],PopStack(S1));//车从暂存栈回到原来的栈，指定车辆出停车场的操作完成
        S.top++;
    }
    if(flag == 1)
    {
        strcpy(S.data[S.top], OutQueue(Q));//如图有车辆成功离开停车场，则队列里面的第一辆车进入
        S.top++;
        printf("队列中第一辆车进入停车\n");
    }
    else
    {
        printf("这辆车不在停车场中！\n");
    }
}
//指定车辆出库
 
int Search(Stack &S, Queue &Q){
    char a[MSIZE];
    printf("请输入要查找的车牌号\n");
    scanf("%s", a);
    int where = 0;//用where记录位置
    int flag = 0;//flag表示是否找到
    for(int i = 0; i < S.top; i++)//从车库最里边（左侧）开始遍历查找
    {
        where++;
        if(strcmp(S.data[i], a) == 0)
        {
            flag = 1;
            break;
        }
    }
    if(flag == 1)
    {
        printf("这辆车在停车场从左往右第%d个\n", where);
        return 0;
    }//输出车辆的位置
    where = 0;//where重置为0，开始在队列中查找
    for(int i = Q.front; i <= Q.rear; i++)//从队列头部开始查找
    {
        where++;
        if(strcmp(Q.data[i], a) == 0)
        {
            flag = 1;
            break;
        }
    }
    if(flag == 1)
    {
        printf("这辆车在队列中排第%d个\n", where);
        return 0;
    }//输出车辆的位置
    else
    {
        printf("没有找到\n");
        return 0;
    }
}
//查找车辆
 
int main(){
    Stack S;
    Queue Q;
    int n, m;//停车场容量为n，队伍长度上限为m
    printf("请输入停车场容量大小\n");
    scanf("%d", &n);
    printf("请输入排队长度上限\n");
    scanf("%d", &m);
    InitStack(S, n);
    InitQueue(Q, m);
    int x;
    printf("请输入需要停车的车辆数(不超过停车场和队伍的容量和)\n");
    scanf("%d", &x);
 
    if(Deploy(S, Q, x) == -1) return 0;//部署这些车辆的位置，输入错误时Deploy返回值为-1，程序结束
 
    int option;
    do
    {
        printf("\n接下来你的操作是:\n1.有车到来\n2.有车离开停车场\n3.查看所有车辆\n4.查找指定车辆\n0.结束程序\n");
        scanf("%d", &option);
        printf("\n");
        if(option == 1)
        {
            Come(S, Q);//有车辆到来时，执行函数Come，执行车辆直接进入车库或者是队列，亦或是容量满了无法进入
        }
        else if(option == 2)
        {
            Leave(S, Q);//调用前面封装的Leave函数实现车辆离开停车场
        }
        else if(option == 3)
        {
            PrintStack(S);//打印栈
            PrintQueue(Q);//打印队列
        }
        else if(option == 4)
        {
            Search(S, Q);//在栈和队列中查找，调用前面的Search函数
        }
        else if(option != 0){
            printf("无此选项\n");
        }
    } while (option != 0);
}