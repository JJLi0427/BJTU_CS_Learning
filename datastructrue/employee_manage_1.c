#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MSIZE 100
 
typedef struct {
    char **name;
    char **job;
    char **num;
    int len;
    int listsize;
}list;
//定义一个顺序表，存储姓名，职务，和工号，字符串数组利用二维指针保存
 
void InitList(list &L) {
    L.name = (char**)malloc(MSIZE*MSIZE*sizeof(char*));
    for(int i = 0; i < MSIZE; i++) {
        L.name[i] = (char*)malloc(MSIZE*sizeof(char));
    }
    L.job = (char**)malloc(MSIZE*MSIZE*sizeof(char*));
    for(int i = 0; i < MSIZE; i++) {
        L.job[i] = (char*)malloc(MSIZE*sizeof(char));
    }
    L.num = (char**)malloc(MSIZE*MSIZE*sizeof(char*));
    for(int i = 0; i < MSIZE; i++) {
        L.num[i] = (char*)malloc(MSIZE*sizeof(char));
    }
    L.len = 0;
    L.listsize = MSIZE;
}
//新建顺序表，申请存储空间
 
void Getlist(list &L) {
    printf("请输入公司原有的员工数量(100以内)\n");
    scanf("%d", &L.len);
    printf("请在每行按照以下格式输入：\n姓名 职务 工号\n");
    for(int i = 0; i < L.len; i++) {
        scanf("%s %s %s", L.name[i], L.job[i], L.num[i]);
    }
    printf("基本数据获取完成\n");
}
//获取初始的数据，存到顺序表
 
void Outlist(list &L) {
    printf("所有员工数据为：\n");
    for(int i = 0; i < L.len; i++) {
        printf("%d. 姓名：%s 职务：%s 工号：%s\n", i, L.name[i], L.job[i], L.num[i]);
    }
}
//打印顺序表函数
 
int Insert(list &L) {
    L.len++;
    if(L.len > MSIZE) {
        printf("列表已满，操作失败\n");
        L.len = MSIZE;
        return 0;
    }
    printf("请按照格式输入员工的信息：\n姓名 职务 工号\n");
    scanf("%s", L.name[L.len - 1]);
    scanf("%s", L.job[L.len - 1]);
    scanf("%s", L.num[L.len - 1]);
    return 0;
}
//员工入职，加入列表末尾位置
 
int Dele(list &L, int p) {
    if(p < 0 || p > L.len - 1) {
        printf("删除的位置不合法，操作失败\n");
        return 0;
    }
    char **name = &L.name[p], **job = &L.job[p], **num = &L.num[p];
    for(int i = p; p < L.len - 1; i++) {
        L.name[i] = L.name[i + 1];
        L.job[i] = L.job[i + 1];
        L.num[i] = L.num[i + 1];
    }
    L.len--;
    printf("姓名：%s 职务：%s 工号：%s 已删除\n", *name, *job, *num);
    return 0;
}
//员工离职，指定位置删除
 
void Search(list &L) {
    printf("请选择查找方式(输入对应编号)：\n1.按照姓名查找\n2.按照职务查找\n3.按照工号查找\n");
    int mode;
    scanf("%d", &mode);
    if(mode == 1) {
        char name[MSIZE];
        int flag = 0;//flag作为一个标识符，表示是否有查找到
        printf("请输入姓名\n");
        scanf("%s", name);
        for(int i = 0; i < L.len; i++) {
            if(strcmp(name, L.name[i]) == 0) {
                flag = 1;
                printf("表中位置：%d. 姓名：%s 职务：%s 工号：%s\n", i, L.name[i], L.job[i], L.num[i]);
            }
        }
        if(flag == 0) printf("没有找到\n");
    }
 
    if(mode == 2) {
        char job[MSIZE];
        int flag = 0;//flag作为一个标识符，表示是否有查找到
        printf("请输入职务\n");
        scanf("%s", job);
        for(int i = 0; i < L.len; i++) {
            if(strcmp(job, L.job[i]) == 0) {
                flag = 1;
                printf("表中位置：%d. 姓名：%s 职务：%s 工号：%s\n", i, L.name[i], L.job[i], L.num[i]);
            }
            //可能有多个人职务一样，故在此不会结束循环
        }
        if(flag == 0) printf("没有找到\n");
    }
 
    if(mode == 3) {
        char num[MSIZE];
        int flag = 0;//flag作为一个标识符，表示是否有查找到
        printf("请输入工号\n");
        scanf("%s", num);
        for(int i = 0; i < L.len; i++) {
            if(strcmp(num, L.num[i]) == 0) {
                flag = 1;
                printf("表中位置：%d. 姓名：%s 职务：%s 工号：%s\n", i, L.name[i], L.job[i], L.num[i]);
                break;
            }
        }
        if(flag == 0) printf("没有找到\n");
    }
}
//查找员工
 
int main() {
    list L;
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
 
 