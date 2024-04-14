#include <stdio.h>
#include <stdlib.h>
 
typedef struct Node{
	int data;
	Node *lchild;
    Node *rchild;
}Node,*Tree;
//二叉树的存储结构
 
Node *CreateTree(int n){
	Node *p = (Node*)malloc(sizeof(Node));
	p->data = n;
	p->lchild = NULL;
	p->rchild = NULL;
	return p;
}
//创建树
 
void Insert(Node *&T, int n){
	if(!T)
		T = CreateTree(n);
	else if(n > T->data) 
        Insert(T->rchild, n);//小于在左子树添加
	else            
        Insert(T->lchild, n);//大于在右子树添加
}
//增加元素
 
void Middle(Tree T){
	if (T)
	{
		if(T->lchild) Middle(T->lchild);
		printf("%d ",T->data);
		if(T->rchild) Middle(T->rchild);
	}
}
//中序遍历输出二叉树
 
int Search(Tree T, int n){
	if(!T)
		return 0;//树空返回0
	else if(n = T->data) 
        return 1;//相等返回1
	else if(n < T->data)           
        Search(T->lchild, n);//小于查找左子树
    else if(n > T->data)
        Search(T->rchild, n);//大于查找右子树
}
//在二叉排序树中查找元素
 
int main(){
    Node *T = NULL;//树的头节点
	int n;
 
    printf("输入一个无序关键字序列，空格分隔，以EOF结束\n");
	while(scanf("%d", &n) != EOF)
		Insert(T, n);
    //获取用户输入，创建树
 
    printf("中序遍历二叉排序树：\n");
	Middle(T);
    //输出中序遍历
 
    printf("\n输入你要查找的数：\n");
    scanf("%d", &n);
    if(Search(T, n)) 
        printf("这个数在树中\n");//找到这个数
    else
    {
        printf("无此数，将数添加到树，再输出中序遍历\n");
        Insert(T, n);//没找到，插入到树
        Middle(T);//再次遍历输出
    }
    
	return 0;
}