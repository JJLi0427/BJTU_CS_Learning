#include "Lab4_view.h"
//主要功能为显示结果

//四个封装函数主要对应四种数据存储格式的数据操作
//输出的算法都是一致的，for循环遍历

void view1(int *ptr, int num){
    printf("\n");
    for(int i = 0; i < num; i++){
        printf("%d %d %d\n", ptr[3*i], ptr[3*i + 1], ptr[3*i + 2]);
    }
    printf("\n已打印所有读取到的数据(共%d条)↑\n", num);
}
//显示二维指针数组的结果

void view2(DataItem *data, int num){
    printf("\n");
    for(int i = 0; i < num; i++){
        printf("%d %d %d\n", data[i].item1, data[i].item2, data[i].item3);
    }
    printf("\n已打印所有读取到的数据(共%d条)↑\n", num);
}
//显示结构体数组的结果

void view3(DataItem **p, int num){
    printf("\n");
    for(int i = 0; i < num; i++){
        printf("%d %d %d\n", p[i]->item1, p[i]->item2, p[i]->item3);
    }
    printf("\n已打印所有读取到的数据(共%d条)↑\n", num);
}
//显示指针数组的结果

void view4(Link &L, int num){
    printf("\n");
    Link p;
    p = L;
    for(int i = 0; i < num; i++){
        p = p->next;
        printf("%d %d %d\n", p->item1, p->item2, p->item3);
    }
    printf("\n已打印所有读取到的数据(共%d条)↑\n", num);
}
//显示链表的结果