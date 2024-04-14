#include <stdio.h>
#include <stdlib.h>
#define MAX 100
 
typedef struct Graph
{
    int data[MAX];//用一个数组来存储所有顶点
    int edge[MAX][MAX];//邻接矩阵 
    int nodenum, edgenum;
}Graph;
//定义邻接矩阵的存储结构
 
int Find(Graph &G, int node)
{
    for(int i = 0; i < G.nodenum; i++)
        if(G.data[i] == node) 
            return i;
    return -1;
}
//查找在顶点数组中的位置
 
void CreateGraph(Graph &G)
{
    printf("请输入顶点个数\n");
    scanf("%d", &G.nodenum);
    printf("请在下面一行依次输入每个顶点,顶点用数字表示，用空格分隔\n");
    for(int i = 0; i < G.nodenum; i++)
        scanf("%d", &G.data[i]);
    for(int i = 0; i < G.nodenum; i++)
        for(int j = 0; j < G.nodenum; j++)
            G.edge[i][j] = 0;
    printf("请输入边的条数\n");
    scanf("%d", &G.edgenum);
    printf("每行输入一条边的两个端点,用空格分开\n");
    for(int i = 0; i < G.edgenum; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        a = Find(G, a);
        b = Find(G, b);
        G.edge[a][b] = 1;
        G.edge[b][a] = 1;
    }//获取每一条边，存储到邻接矩阵
}
 
int visit[MAX];
 
int Next(Graph &G, int node)
{
    for(int i = 0; i < G.nodenum; i++)
        if(G.edge[node][i] == 1 && visit[i] == 0)//是邻接点，且还没被访问
            return i;//返回邻接点
    return -1;//没有符合的返回-1
}
//这个封装函数用于查找一个顶点尚未被访问的临界点
 
void DFS(Graph &G, int node)
{
    visit[node] = 1;
    printf("%d", G.data[node]);
    int p;
    while(Next(G, node) != -1)//有未访问的邻接点
    {
        p = Next(G, node);
        DFS(G, p);//对这个邻接点继续深度优先遍历
        p = Next(G, p);
    }
}
//深度优先遍历
 
void BFS(Graph &G, int node)
{
    int Queue[MAX];
    int front = 0, rear = 0;//初始化一个队列
    visit[node] = 1;
    printf("%d", G.data[node]);
    Queue[rear] = node;
    rear++;//访问起点后存入队列
    while(front != rear)
    {
        int a = Queue[front];
        front++;//队列非空出队
        int p;
        while(Next(G, a) != -1)//从未访问的邻接点继续
        {
            p = Next(G, a);
            visit[p] = 1;
            printf("%d", G.data[p]);
            Queue[rear] = p;
            rear++;//访问后进入队列
            p = Next(G, p);
        }
    }
}
//广度优先遍历
 
int main() {
    Graph G;
    CreateGraph(G);
    int node;
    printf("请输入一个顶点开始遍历\n");
    scanf("%d", &node);
    for(int i = 0; i < G.nodenum; i++) visit[i] = 0;//初始化所有顶点为未访问
    node = Find(G, node);
    printf("深度优先遍历的结果是：");
    DFS(G, node);
    printf("\n");
    for(int i = 0; i < G.nodenum; i++) visit[i] = 0;//初始化所有顶点为未访问
    printf("广度优先遍历的结果是：");
    BFS(G, node);
    printf("\n");
    system("pause");
    return 0;
}