#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MSIZE 100
 
typedef struct emp{
    char name[MSIZE];
    char job[MSIZE];
    char num[MSIZE];
    emp *next;
}emp;
//定义一个链表，存储姓名，职务，和工号，字符串数组利用二维指针保存
 
void InitList(emp *L) {
    L = (emp *)malloc(sizeof(emp));
    L->next = NULL;
}
 
void Getlist(emp *L) {
    L->next = NULL;
    int n;
    emp *p;
    printf("请输入公司原有的员工数量\n");
    scanf("%d", &n);
    printf("请在每行按照以下格式输入：\n姓名 职务 工号\n");
    for(int i = 0; i < n; i++) {
        p = (emp*)malloc(sizeof(emp));
        scanf("%s %s %s", p->name, p->job, p->num);
        p->next = L->next;
        L->next = p;
    }
    printf("基本数据获取完成\n");
}
//获取初始的数据，存到链表
 
void Outlist(emp *L) {
    int i = 0;
    emp *p;
    p = L->next;
    printf("所有员工数据为：\n");
    while(p != NULL) {
        i++;
        printf("%d. 姓名：%s 职务：%s 工号：%s\n", i, p->name, p->job, p->num);
        p = p->next;
    }
    printf("总共有%d人\n", i);
}
//打印链表存储的数据
 
void Insert(emp *L) {
    emp *p;
    p = (emp*)malloc(sizeof(emp));
    printf("请按照格式输入员工的信息：\n姓名 职务 工号\n");
    scanf("%s %s %s", p->name, p->job, p->num);
    p->next = L->next;
    L->next = p;
}
//员工入职，加入列表头部
 
int Dele(emp *L, int n) {
    emp *p, *t;
    p = L->next;
    for(int i = 0; i < n - 2; i++) {
        p = p->next;
    }
    t = p->next;
    p->next = t->next;
    printf("姓名：%s 职务：%s 工号：%s 已删除\n", t->name, t->job, t->num);
    free(t);
    return 0;
}
//员工离职，指定位置删除
 
void Search(emp *L) {
    printf("请选择查找方式(输入对应编号)：\n1.按照姓名查找\n2.按照职务查找\n3.按照工号查找\n");
    int mode;
    scanf("%d", &mode);
    if(mode == 1) {
        int i = 0;
        emp *p;
        p = L->next;
        char name[MSIZE];
        int flag = 0;//flag作为一个标识符，表示是否有查找到
        printf("请输入姓名\n");
        scanf("%s", name);
        while(p != NULL) {
            i++;
            if(strcmp(name, p->name) == 0) {
                flag = 1;
                printf("表中位置：%d. 姓名：%s 职务：%s 工号：%s\n", i, p->name, p->job, p->num);
            }
            p = p->next;
        }
        if(flag == 0) printf("没有找到\n");
    }
 
    if(mode == 2) {
        int i = 0;
        emp *p;
        p = L->next;
        char job[MSIZE];
        int flag = 0;//flag作为一个标识符，表示是否有查找到
        printf("请输入职务\n");
        scanf("%s", job);
        while(p != NULL) {
            i++;
            if(strcmp(job, p->job) == 0) {
                flag = 1;
                printf("表中位置：%d. 姓名：%s 职务：%s 工号：%s\n", i, p->name, p->job, p->num);
                p = p->next;
            }
            p = p->next;
        }
        if(flag == 0) printf("没有找到\n");
    }
 
    if(mode == 3) {
        int i = 0;
        emp *p;
        p = L->next;
        char num[MSIZE];
        int flag = 0;//flag作为一个标识符，表示是否有查找到
        printf("请输入工号\n");
        scanf("%s", num);
        while(p != NULL) {
            i++;
            if(strcmp(num, p->num) == 0) {
                flag = 1;
                printf("表中位置：%d. 姓名：%s 职务：%s 工号：%s\n", i, p->name, p->job, p->num);
                break;
            }
            p = p->next;
        }
        if(flag == 0) printf("没有找到\n");
    }
}
//查找员工
 
int main() {
    emp *L;
    L = (emp *)malloc(sizeof(emp));
    InitList(L);//初始化列表L
    Getlist(L);//获取初始数据
    Outlist(L);
    int a;
    do {
        printf("\n接下来你想进行的操作是(输入数字)：\n1.员工入职\n2.员工离职\n3.查找员工\n4.查看所有数据\n5.结束程序\n");
        scanf("%d", &a);
        printf("\n");
        if(a == 1) {
            Insert(L);
            Outlist(L);
 
        }
        if(a == 2) {
            int p;
            printf("请输入要在表中删除的位置\n");
            scanf("%d", &p);
            Dele(L, p);
            Outlist(L);
        }
        if(a == 3) {
            Search(L);
        }
        if(a == 4) {
            Outlist(L);
        }
    } while(a != 5);
    return 0;
}