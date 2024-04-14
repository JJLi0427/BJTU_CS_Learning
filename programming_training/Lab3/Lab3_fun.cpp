#include "Lab3_fun.h"

int getnum(int max, int min) {
    printf("��������������n:(%d<=n<=%d)\n", min, max);
    char c[16];
    int amt;
    scanf("%d", &amt);
    while(amt < min || amt > max) {
        printf("����������������Ϸ�\n");
        printf("��������������n:(%d<=n<=%d),����r�������ָ����������\n", min, max);
        scanf("%s", c);
        if(strlen(c) == 1 && c[0] == 'r'){//���ַ����ж��Ƿ��û�ѡ�������
            srand(time(0));
            amt = rand() % (max-min+1) + min;
            return amt;
        }
        else amt = atoi(c);
    }
    //�ж������Ƿ������Ʒ�Χ��
    return amt;
}//��ȡ��������

void opentxt(char *name) {
    char cmd[100];
    sprintf(cmd, "start %s", name);
    system(cmd);
}//��д�õ�txt�ļ���չʾ

int random(int max, int min){
    return rand() % (max-min+1)+min;
}//����ָ����Χ�������

void OP1(CONF conf, char *where){
    int **arr;//������άָ��
    arr = new int *[conf.number];
    for (int i = 0; i < conf.number; i++) {
        arr[i] = new int[3];
        if (NULL == arr[i]) {
            printf("����ռ䴴��ʧ��\n");
            exit(0);
        }
    }//��̬����ռ�
    srand(time(0));//�������������
    for (int i = 0; i < conf.number; i++) {
        arr[i][0] = random(conf.maxvalue1, conf.minvalue1);
        arr[i][1] = random(conf.maxvalue1, conf.minvalue1);
        arr[i][2] = random(conf.maxvalue2, conf.minvalue2);
    }//������洢����ά����
    FILE *fp = fopen(where, "w+");
    if (NULL == fp) {
        printf("���ļ�ʧ��\n");
        exit(0);
    }
    fprintf(fp,"%d\n", conf.number);//���ļ�����д�� 
    for (int i = 0; i < conf.number; i++) {
        fprintf(fp, "%d,%d,%d\n", arr[i][0], arr[i][1], arr[i][2]);//д�����ݵ�txt
        printf("%d,%d,%d\n", arr[i][0], arr[i][1], arr[i][2]);//������ݵ���Ļ
    }
    fclose(fp);
    opentxt(where);
}
//ģʽ1���У���ά����ķ�ʽ

void OP2(CONF conf, char *where){
    DATAITEM *data;
    data = new DATAITEM[conf.number];
    srand(time(0));//�������������
    for (int i = 0; i < conf.number; i++) {
        data[i].item1 = random(conf.maxvalue1, conf.minvalue1);
        data[i].item2 = random(conf.maxvalue1, conf.minvalue1);
        data[i].item3 = random(conf.maxvalue2, conf.minvalue2);
    }//�����������ṹ������
    FILE *fp = fopen(where, "w+");
    if (NULL == fp) {
        printf("���ļ�ʧ��\n");
        exit(0);
    }
    fprintf(fp,"%d\n", conf.number);//���ļ�����д�� 
    for (int i = 0; i < conf.number; i++) {
        fprintf(fp, "%d,%d,%d\n", data[i].item1, data[i].item2, data[i].item3);//д�����ݵ�txt
        printf("%d,%d,%d\n", data[i].item1, data[i].item2, data[i].item3);//������ݵ���Ļ
    }
    fclose(fp);
    opentxt(where);
}//ģʽ2���У��ṹ��ķ�ʽ
