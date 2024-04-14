#include "Lab4_loadfile.h"
#include "Lab4_sort.h"
#include "Lab4_view.h"

void getwhere(char *where){
    printf("������ո����ɵ��ļ�·��\n");
    char str[MAX_STR_LEN];
    scanf("%s", str);

    where = str;
    //ָ��ָ�����·�����ַ���
}
//��ȡ�ļ�·���ĺ���

//�����ĸ���װ������Ӧ�������ݴ洢����

void load1(char *where, int sort){
    //printf("%s\n", where);
    FILE *fp = fopen(where, "r");
    if (NULL == fp) {
        printf("���ļ�ʧ��\n");
        exit(0);
    }
    int num;
    fscanf(fp, "%d", &num);
    //printf("\n��ȡ������������%d\n", num);

    int *ptr = (int* ) malloc((num * 3) * sizeof(int));
    //��̬�����ά����

    for(int i = 0; i < num; i++){
        fscanf(fp, "%d,%d,%d\n", &ptr[3*i], &ptr[3*i+1], &ptr[3*i+2]);
    }

    view1(ptr, num);//��ʾ����
    if(sort == 1) sort1(ptr, num);
}
//��̬��ά����ķ�ʽ��������

void load2(char *where, int sort){
    FILE *fp = fopen(where, "r");
    if (NULL == fp) {
        printf("���ļ�ʧ��\n");
        exit(0);
    }
    int num;
    fscanf(fp, "%d", &num);
    //printf("\n��ȡ������������%d\n", num);

    DataItem *data;//�ṹ��ָ��
    data = (DataItem *)malloc(num * sizeof(DataItem));//��������

    for(int i = 0; i < num; i++){
        fscanf(fp, "%d,%d,%d\n", &data[i].item1, &data[i].item2, &data[i].item3);
    }

    view2(data, num);//��ʾ����
    if(sort == 1) sort2(data, num);
}
//��̬�ṹ������ķ�ʽ

void load3(char *where, int sort){
    FILE *fp = fopen(where, "r");
    if (NULL == fp) {
        printf("���ļ�ʧ��\n");
        exit(0);
    }
    int num;
    fscanf(fp, "%d", &num);
    //printf("\n��ȡ������������%d\n", num);

    DataItem **p = (DataItem **)malloc(num * sizeof(DataItem *));//����ָ������
    for(int i = 0; i < num; i++){
        p[i] = (DataItem *)malloc(sizeof(DataItem));//ָ��������ÿ��Ԫ��ָ��һ���ṹ��
    }

    for(int i = 0; i < num; i++){
        fscanf(fp, "%d,%d,%d\n", &p[i]->item1, &p[i]->item2, &p[i]->item3);
    }

    view3(p, num);//��ʾ����
    if(sort == 1) sort3(p, num);
}
//��ָ̬�����飬���ö�άָ��

void load4(char *where, int sort){
    FILE *fp = fopen(where, "r");
    if (NULL == fp) {
        printf("���ļ�ʧ��\n");
        exit(0);
    }
    int num;

    Link L, t;
    L = (Link)malloc(sizeof(Node));
    L->next = NULL;//����ͷָ��
    t = L;//����һ���±꣬��ͷ��ʼ
    fscanf(fp, "%d", &num);
    //printf("\n��ȡ������������%d\n", num);
    for(int i = 0; i < num; i++){

        Link p;
        p = (Link)malloc(sizeof(Node));
        //ÿ��ȡһ�����ݴ���һ������Ľڵ�
        
        fscanf(fp, "%d,%d,%d\n", &p->item1, &p->item2, &p->item3);
        p->next = t->next;
        t->next = p;
        t = p;
    }
    //�����β�巨��ȡ����
    view4(L, num);//��ʾ����
    if(sort == 1) sort4(L, num);
}
//����ķ�ʽ