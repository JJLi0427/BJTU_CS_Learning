#include <stdio.h>
#include <stdlib.h>
#define MAX 100
 
typedef struct EdgeNode
{
    int adj;//弧指向的顶点
    struct EdgeNode *next;//下一条弧指针
}EdgeNode;
 
typedef struct Node
{
    int data;//顶点的信息
    EdgeNode *first;//指向第一条弧
}Node, List[MAX];
 
typedef struct
{
    List list;//顶点数组
    int nodenum, edgenum;//分表表示顶点数和弧的数量
}Graph;
 
int Find(Graph &G, int node)
{
    for(int i = 0; i < G.nodenum; i++)
        if(G.list[i].data == node)//查找到指定的顶点
            return i;
    return -1;
}
//查找顶点在列表中的位置
 
void CreateGraph(Graph &G)
{
    printf("请输入顶点个数\n");
    scanf("%d", &G.nodenum);
    printf("请在下面一行依次输入每个顶点,顶点用数字表示，用空格分隔\n");
    for(int i = 0; i < G.nodenum; i++)
    {
        scanf("%d", &G.list[i].data);
        G.list[i].first = NULL;
    }
    printf("请输入边的条数\n");
    scanf("%d", &G.edgenum);
    printf("每行输入一条边的两个端点,用空格分开\n");
    for(int i = 0; i < G.edgenum; i++)
    {
        int a, b;
        EdgeNode *p1, *p2;
        scanf("%d %d", &a, &b);
        a = Find(G, a);//找到对应a的顶点
        b = Find(G, b);//找到对应b的顶点
        p1 = (EdgeNode*)malloc(sizeof(EdgeNode));
        p1->adj = b;
        p1->next = G.list[a].first;
        G.list[a].first = p1;//存储从a到b
        p2 = (EdgeNode*)malloc(sizeof(EdgeNode));
        p2->adj = a;
        p2->next = G.list[b].first;
        G.list[b].first = p2;//存储从b到a
    }
}
//邻接表的初始化
 
int visit[MAX];
 
void DFS(Graph &G, int node)
{
    EdgeNode *p;
    p = G.list[node].first;
    visit[node] = 1;
    printf("%d", G.list[node].data);//输出遍历到的点
    while(p)
    {
        if(visit[p->adj] == 0) DFS(G, p->adj);//尚未访问就继续调用DFS
        p = p->next;
    }
}
//深度优先遍历
 
void BFS(Graph &G, int node)
{
    int Queue[MAX];
    int front = 0, rear = 0;
    visit[node] = 1;
    printf("%d", G.list[node].data);//输出遍历到的点
    Queue[rear] = node;
    rear++;//遍历之后就进入队列
    EdgeNode *p;
    while(front != rear)//队列非空
    {
        int a = Queue[front];
        front++;//第一个元素出列
        for(EdgeNode *p = G.list[a].first; p != NULL; p = p->next)//尚未访问的邻接点
        {
            if(visit[p->adj] == 0)//未访问的在访问后入列
            {
                visit[p->adj] = 1;
                printf("%d", G.list[p->adj].data);//输出访问的点
                Queue[rear] = p->adj;
                rear++;//遍历到的点入列
            }
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