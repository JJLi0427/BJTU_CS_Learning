#include "Lab4_call.h"

void c1(CONF *conf){
    char where[MAX_STR_LEN]; 
    strcpy(where, conf->filesavepath);
    strcat(where, "/");
    strcat(where, conf->filename);
    //��ȡ�����������ļ���λ��

    srand(time(NULL));
    conf->number = rand() % (conf->recordcount1 - conf->recordcount2 + 1) + conf->recordcount2; 
    //����������ļ���������

    char cmd[1024];
    sprintf(cmd, "Lab3.exe %d %s", conf->number, where);
    //ֱ����r����Lab3.exe��Ĭ��ģʽ
    system(cmd);
}
//�Զ�Ĭ��ģʽ����Lab3.exe

void c2(int x, char *where){
    char cmd[1024];
    sprintf(cmd, "Lab3.exe %d %s", x, where);
    system(cmd);
}
//����ģʽ����