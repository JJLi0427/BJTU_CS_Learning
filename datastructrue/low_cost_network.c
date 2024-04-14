#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define MAXCOST 99999
 
typedef struct Graph
{
    int data[MAX];//用一个数组来存储所有顶点
    int edge[MAX][MAX];//邻接矩阵 
    int nodenum = 5, edgenum;
}Graph;
//定义邻接矩阵的存储结构
 
void CreateGraph(Graph &G)
{
    printf("初始化5个顶点为：0 1 2 3 4\n");
    for(int i = 0; i < G.nodenum; i++)
        G.data[i] = i;
    for(int i = 0; i < G.nodenum; i++)
        for(int j = 0; j < G.nodenum; j++)
            G.edge[i][j] = MAXCOST;
    printf("请输入边的条数\n");
    scanf("%d", &G.edgenum);
    printf("每行输入一条边的两个端点和权值,用空格分开\n");
    for(int i = 0; i < G.edgenum; i++)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        G.edge[a][b] = c;
        G.edge[b][a] = c;
    }//获取每一条边，存储到邻接矩阵
}
 
void Tree(Graph &G)
{
    int cost[MAX];//存储扫描到的最短边，下表是边的一个端点
    int from[MAX] = {0};//from数组，值为以下标为端点扫描到的最短边的另外一个端点
    int min, node, sum = 0;
    for(int i = 1; i < G.nodenum; i++)//初始以0为起点
        cost[i] = G.edge[0][i];
    for(int i = 1; i < G.nodenum; i++)
    {
        min = MAXCOST;//min初始化为最大
        node = 0;//最短边的一个端点
        for(int j = 1; j < G.nodenum; j++)
        {
            if(cost[j] < min && cost[j] != 0)
            {
                min = cost[j];
                node = j;
            }//得到最短边，更新端点node
        }
        printf("%d - %d: %d\n", from[node], node, min);
        sum += min;
        cost[node] = 0;
        for(int j = 1; j < G.nodenum; j++)//从node点继续扫描最短边
        {
            if(G.edge[node][j] < cost[j])
            {
                cost[j] = G.edge[node][j];
                from[j] = node;
            }//更新cost和from
        }
    }
    printf("建成最小代价为：%d\n", sum);
}
//Prim算法实现最小生成树
 
int main(){
    Graph G;
    CreateGraph(G);
    printf("最小代价用到的边:\n");
    Tree(G);
    system("pause");
    return 0;
}