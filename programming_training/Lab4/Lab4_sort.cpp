#include "Lab4_sort.h"

int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
//比较函数，qsort需要

//排序主要思路是读入数据到数组然后排序，重新赋值回数组

//四种封装函数对应了四种数据存储类型

void sort1(int *ptr, int num){
    int *arr = (int *)malloc(num*sizeof(int));
    for(int i = 0; i < num; i++){
        arr[i] = ptr[i + 2];
    }
    qsort(arr, num, sizeof(int), cmp);
    for(int i = 0; i < num; i++) printf("%d\n", arr[i]);
    printf("\n以上为排序结果↑\n");
}
//二维指针数组的排序

void sort2(DataItem *data, int num){
    int *arr = (int *)malloc(num*sizeof(int));
    for(int i = 0; i < num; i++){
        arr[i] = data[i].item3;
    }
    qsort(arr, num, sizeof(int), cmp);
    for(int i = 0; i < num; i++) printf("%d\n", arr[i]);
    printf("\n以上为排序结果↑\n");
}
//结构体数组的排序

void sort3(DataItem **p, int num){
    int *arr = (int *)malloc(num*sizeof(int));
    for(int i = 0; i < num; i++){
        arr[i] = p[i]->item3;
    }
    qsort(arr, num, sizeof(int), cmp);
    for(int i = 0; i < num; i++) printf("%d\n", arr[i]);
    printf("\n以上为排序结果↑\n");
}
//指针数组的排序

void sort4(Link &L, int num){
    int *arr = (int *)malloc(num*sizeof(int));
    Link p;
    p = L;
    clock_t start,end;

    for(int i = 0; i < num; i++){
        p = p->next;
        arr[i] = p->item3;
    }
    //读入数据
    printf("\n请选择排序方式：1.冒泡排序，2.快速排序\n");
    int opt;
    scanf("%d", &opt);
    if(opt != 1 && opt != 2) {
        printf("输入错误，默认开始冒泡排序\n");
        opt = 1;
    }

    if(opt == 1){
        start = clock();
        for(int i = 0; i < num-1; i++){
            for(int j = 0; j < num-1-i; j++){
                if(arr[j] > arr[j+1]){
                    int t = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = t;
                }
            }
        }
        end = clock();
    }
    //冒泡排序
    if(opt == 2){
        start = clock();
        quicksort(arr, 0, num-1);
        end = clock();
        
    }
    //快速排序
    double endtime=(double)(end-start)/CLOCKS_PER_SEC;

    for(int i = 0; i < num; i++) printf("%d\n", arr[i]);
    printf("\n以上为排序结果↑\n");
    if(opt == 1) printf("%d个冒泡排序耗时：%lfs\n", num, endtime);
    if(opt == 2) printf("%d个快速排序耗时：%lfs\n", num, endtime);
}
//链表的排序

void quicksort(int* a,int start,int end)   //快速排序主体代码函数
{
	if(start>=end) return;
	int i = start;
	int j = end;
	int key = a[i];
	while (i<j)
	{
		while(i<j&&a[j]>=key)
		{
			j--;
		}
		a[i] = a[j];
		while(i<j&&a[i]<=key)
		{
			i++;
		}
		a[j] = a[i];
	}
	a[i] = key;
	quicksort(a,start,i-1);
	quicksort(a,i+1,end);
}
