#include "readfile.h"

void readfile(char* locate, struct List L[6]) {
    FILE* fp = fopen(locate, "r");

    for (int i = 0; i < 6; i++) {
        fscanf(fp, "%s", L[i].name);
    }
    //��ȡͳ����Ŀ��
    for (int i = 0; i < 6; i++) {
        fscanf(fp, "%d", &L[i].num);
    }
    //��ȡͳ����

    fclose(fp);
}
//��ȡͳ�ƽ���ļ����洢���ṹ������