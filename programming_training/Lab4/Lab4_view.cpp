#include "Lab4_view.h"
//��Ҫ����Ϊ��ʾ���

//�ĸ���װ������Ҫ��Ӧ�������ݴ洢��ʽ�����ݲ���
//������㷨����һ�µģ�forѭ������

void view1(int *ptr, int num){
    printf("\n");
    for(int i = 0; i < num; i++){
        printf("%d %d %d\n", ptr[3*i], ptr[3*i + 1], ptr[3*i + 2]);
    }
    printf("\n�Ѵ�ӡ���ж�ȡ��������(��%d��)��\n", num);
}
//��ʾ��άָ������Ľ��

void view2(DataItem *data, int num){
    printf("\n");
    for(int i = 0; i < num; i++){
        printf("%d %d %d\n", data[i].item1, data[i].item2, data[i].item3);
    }
    printf("\n�Ѵ�ӡ���ж�ȡ��������(��%d��)��\n", num);
}
//��ʾ�ṹ������Ľ��

void view3(DataItem **p, int num){
    printf("\n");
    for(int i = 0; i < num; i++){
        printf("%d %d %d\n", p[i]->item1, p[i]->item2, p[i]->item3);
    }
    printf("\n�Ѵ�ӡ���ж�ȡ��������(��%d��)��\n", num);
}
//��ʾָ������Ľ��

void view4(Link &L, int num){
    printf("\n");
    Link p;
    p = L;
    for(int i = 0; i < num; i++){
        p = p->next;
        printf("%d %d %d\n", p->item1, p->item2, p->item3);
    }
    printf("\n�Ѵ�ӡ���ж�ȡ��������(��%d��)��\n", num);
}
//��ʾ����Ľ��