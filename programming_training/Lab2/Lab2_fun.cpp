#include "Lab2_fun.h"

int getnum(int amt) {
    cout << "��������������" << endl;
    int i;
    i = scanf("%d", &amt);
    while(i == 0) {
        cout << "����������ȡ��������������" << endl;
        while(getchar() != '\n') {}
        i = scanf("%d", &amt);
    }
    //�ж������Ƿ���ȷ
    return amt;
}
//��ȡ��������

int** newarry(int amt) {
    int** arr;
    //������άָ��
    arr = new int* [amt];
    for (int i = 0; i < amt; i++) {
        arr[i] = new int[3];
        if (NULL == arr[i]) {
            cout << "����ռ䴴��ʧ��" << endl;
            exit(0);
        }
    }
    //Ϊÿһ������ռ�
    return arr;
}
//��������������������ά����

int** random(int** arr, int x, int y) {
    srand(time(0));
    //�������������
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            arr[i][j] = rand() % 101;
            //�������ΧΪ0-100
        }
    }
    //������洢����ά����
    return arr;
}
//����������������ݴ浽��ά����

void writetxt(int** arr, int x, int y, char* name) {
    FILE* fp = fopen(name, "w+");
    if (NULL == fp) {
        cout << "���ļ�ʧ��" << endl;
        exit(0);
    }
    fprintf(fp,"%d\n", x);
    //���ļ�����д�� 
    for (int i = 0; i < x; i++) {
        fprintf(fp, "%d,%d,%d\n", arr[i][0], arr[i][1], arr[i][2]);
        //д�����ݵ�txt
        printf("%d,%d,%d\n", arr[i][0], arr[i][1], arr[i][2]);
        //������ݵ���Ļ
    }
    fclose(fp);
}
//������洢�������д�뵽txt�ļ������������Ļչʾ

void opentxt(char* name) {
    char cmd[100];
    sprintf(cmd, "start %s", name);
    system(cmd);
}
//��д�õ�txt�ļ���չʾ
