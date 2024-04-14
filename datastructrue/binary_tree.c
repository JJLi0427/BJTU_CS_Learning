#include <stdio.h>
#include <stdlib.h>
#define MSIZE 100

typedef struct Node{
    char data;
    struct Node *lchild;
    struct Node *rchild;
}Node, *Tree;
//定义一个二叉树

void CreatTree(Tree *T){
    char ch;
    scanf("%c",&ch);
    if(ch == ' ')
        (*T) = NULL;
    else
    {
        (*T) = (Tree)malloc(sizeof(Node));
        (*T)->data = ch;
        CreatTree(&((*T)->lchild));
        CreatTree(&((*T)->rchild));
    }
}
//读入用户输入生成一个二叉树

void Front(Tree T){
    if(T)
    {
        printf("%c", T->data);
        Front(T->lchild);
        Front(T->rchild);
    }
}
//先序遍历的递归实现

void Middle(Tree T){
    if(T)
    {
        Middle(T->lchild);
        printf("%c", T->data);
        Middle(T->rchild);
    }
}
//中序遍历的递归实现

void Last(Tree T){
    if(T)
    {
        Last(T->lchild);
        Last(T->rchild);
        printf("%c", T->data);
    }
}
//后序遍历的递归实现

void Middle2(Tree T){
    Node *stack[MSIZE];//定义一个栈
    int top = -1;
    Node *p;//定义一个临时指针p
    p = T;
    while(p || top > -1)
    {
        if(p)
        {
            top++;
            stack[top] = p;
            p = p->lchild;//p不为空，遍历左子树
        }
        else
        {
            p = stack[top];
            printf("%c", p->data);
            top--;
            p = p->rchild;//遍历右子树
        }
    }
}
//利用栈实现非递归中序遍历

void level(Tree T){
    Node *queue[MSIZE];//定义队列
    int front = 0;
    int rear = 0;
    int count;
    Node *p;//定义临时指针p
    rear++;
    queue[rear] = T;//根节点进入队列
    while(front != rear)//队列不空
    {
        count = rear - front;
        while(count > 0)
        {
            count--;
            front++;
            p = queue[front];
            printf("%c", p->data);
            if(p->lchild)
            {
                rear++;
                queue[rear] = p->lchild;
            }
            if(p->rchild)
            {
                rear++;
                queue[rear] = p->rchild;
            }
        }
    }
}
//二叉树的层次遍历

int NodeCount(Tree T){
    if(!T) 
        return 0;
    else
        return (NodeCount(T->lchild) + NodeCount(T->rchild) + 1);
}

int TreeDepth(Tree T){
    int a, b;
    if(!T)
        return 0;
    else
    {
        a = TreeDepth(T->lchild);
        b = TreeDepth(T->rchild);
        if(a > b)
            return (a + 1);
        else
            return (b + 1);
    }
}

int main() {
    Tree T = NULL;
    printf("请输入数的先序扩展序列，输入空格表示该位置是空，按回车结束\n");
    CreatTree(&T);//生成树
    printf("前序遍历：");
    Front(T);
    printf("\n");
    printf("中序遍历：");
    Middle(T);
    printf("\n");
    printf("后序遍历：");
    Last(T);
    printf("\n");
    printf("非递归中序遍历：");
    Middle2(T);
    printf("\n");
    printf("非递归层次遍历：");
    level(T);
    printf("\n");
    printf("树的结点个数为：%d\n", NodeCount(T));
    printf("树的深度为：%d\n", TreeDepth(T));
    system("pause"); 
}
