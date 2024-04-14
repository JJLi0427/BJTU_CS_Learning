#include "Lab4_sort.h"

int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
//�ȽϺ�����qsort��Ҫ

//������Ҫ˼·�Ƕ������ݵ�����Ȼ���������¸�ֵ������

//���ַ�װ������Ӧ���������ݴ洢����

void sort1(int *ptr, int num){
    int *arr = (int *)malloc(num*sizeof(int));
    for(int i = 0; i < num; i++){
        arr[i] = ptr[i + 2];
    }
    qsort(arr, num, sizeof(int), cmp);
    for(int i = 0; i < num; i++) printf("%d\n", arr[i]);
    printf("\n����Ϊ��������\n");
}
//��άָ�����������

void sort2(DataItem *data, int num){
    int *arr = (int *)malloc(num*sizeof(int));
    for(int i = 0; i < num; i++){
        arr[i] = data[i].item3;
    }
    qsort(arr, num, sizeof(int), cmp);
    for(int i = 0; i < num; i++) printf("%d\n", arr[i]);
    printf("\n����Ϊ��������\n");
}
//�ṹ�����������

void sort3(DataItem **p, int num){
    int *arr = (int *)malloc(num*sizeof(int));
    for(int i = 0; i < num; i++){
        arr[i] = p[i]->item3;
    }
    qsort(arr, num, sizeof(int), cmp);
    for(int i = 0; i < num; i++) printf("%d\n", arr[i]);
    printf("\n����Ϊ��������\n");
}
//ָ�����������

void sort4(Link &L, int num){
    int *arr = (int *)malloc(num*sizeof(int));
    Link p;
    p = L;
    clock_t start,end;

    for(int i = 0; i < num; i++){
        p = p->next;
        arr[i] = p->item3;
    }
    //��������
    printf("\n��ѡ������ʽ��1.ð������2.��������\n");
    int opt;
    scanf("%d", &opt);
    if(opt != 1 && opt != 2) {
        printf("�������Ĭ�Ͽ�ʼð������\n");
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
    //ð������
    if(opt == 2){
        start = clock();
        quicksort(arr, 0, num-1);
        end = clock();
        
    }
    //��������
    double endtime=(double)(end-start)/CLOCKS_PER_SEC;

    for(int i = 0; i < num; i++) printf("%d\n", arr[i]);
    printf("\n����Ϊ��������\n");
    if(opt == 1) printf("%d��ð�������ʱ��%lfs\n", num, endtime);
    if(opt == 2) printf("%d�����������ʱ��%lfs\n", num, endtime);
}
//���������

void quicksort(int* a,int start,int end)   //��������������뺯��
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
