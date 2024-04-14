#include "Lab4_loadfile.h"
#include "Lab4_sort.h"
#include "Lab4_view.h"

void getwhere(char *where){
    printf("请输入刚刚生成的文件路径\n");
    char str[MAX_STR_LEN];
    scanf("%s", str);

    where = str;
    //指针指向这个路径的字符串
}
//获取文件路径的函数

//以下四个封装函数对应四种数据存储类型

void load1(char *where, int sort){
    //printf("%s\n", where);
    FILE *fp = fopen(where, "r");
    if (NULL == fp) {
        printf("打开文件失败\n");
        exit(0);
    }
    int num;
    fscanf(fp, "%d", &num);
    //printf("\n读取到的数据条数%d\n", num);

    int *ptr = (int* ) malloc((num * 3) * sizeof(int));
    //动态申请二维数组

    for(int i = 0; i < num; i++){
        fscanf(fp, "%d,%d,%d\n", &ptr[3*i], &ptr[3*i+1], &ptr[3*i+2]);
    }

    view1(ptr, num);//显示数据
    if(sort == 1) sort1(ptr, num);
}
//动态二维数组的方式加载数据

void load2(char *where, int sort){
    FILE *fp = fopen(where, "r");
    if (NULL == fp) {
        printf("打开文件失败\n");
        exit(0);
    }
    int num;
    fscanf(fp, "%d", &num);
    //printf("\n读取到的数据条数%d\n", num);

    DataItem *data;//结构体指针
    data = (DataItem *)malloc(num * sizeof(DataItem));//申请数组

    for(int i = 0; i < num; i++){
        fscanf(fp, "%d,%d,%d\n", &data[i].item1, &data[i].item2, &data[i].item3);
    }

    view2(data, num);//显示数据
    if(sort == 1) sort2(data, num);
}
//动态结构体数组的方式

void load3(char *where, int sort){
    FILE *fp = fopen(where, "r");
    if (NULL == fp) {
        printf("打开文件失败\n");
        exit(0);
    }
    int num;
    fscanf(fp, "%d", &num);
    //printf("\n读取到的数据条数%d\n", num);

    DataItem **p = (DataItem **)malloc(num * sizeof(DataItem *));//申请指针数组
    for(int i = 0; i < num; i++){
        p[i] = (DataItem *)malloc(sizeof(DataItem));//指针数组内每个元素指向一个结构体
    }

    for(int i = 0; i < num; i++){
        fscanf(fp, "%d,%d,%d\n", &p[i]->item1, &p[i]->item2, &p[i]->item3);
    }

    view3(p, num);//显示数据
    if(sort == 1) sort3(p, num);
}
//动态指针数组，利用二维指针

void load4(char *where, int sort){
    FILE *fp = fopen(where, "r");
    if (NULL == fp) {
        printf("打开文件失败\n");
        exit(0);
    }
    int num;

    Link L, t;
    L = (Link)malloc(sizeof(Node));
    L->next = NULL;//链表头指针
    t = L;//新增一个下标，从头开始
    fscanf(fp, "%d", &num);
    //printf("\n读取到的数据条数%d\n", num);
    for(int i = 0; i < num; i++){

        Link p;
        p = (Link)malloc(sizeof(Node));
        //每读取一条数据创建一个链表的节点
        
        fscanf(fp, "%d,%d,%d\n", &p->item1, &p->item2, &p->item3);
        p->next = t->next;
        t->next = p;
        t = p;
    }
    //链表的尾插法读取数据
    view4(L, num);//显示数据
    if(sort == 1) sort4(L, num);
}
//链表的方式