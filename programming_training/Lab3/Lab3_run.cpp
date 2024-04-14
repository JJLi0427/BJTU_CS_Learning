#include "Lab3_run.h"

void run(int n, char *argv[]) {
    CONF conf;
    FILE *fp = fopen("conf.ini", "r");
    fscanf(fp, "%s", conf.filesavepath);
    fscanf(fp, "%s", conf.filename);
    fscanf(fp, "%d", &conf.maxvalue1);
    fscanf(fp, "%d", &conf.minvalue1);
    fscanf(fp, "%d", &conf.maxvalue2);
    fscanf(fp, "%d", &conf.minvalue2);
    fscanf(fp, "%d", &conf.recordcount1);
    fscanf(fp, "%d", &conf.recordcount2);
    fclose(fp);
    //��ini�ļ����ݶ���ṹ��

    char *name = NULL;//ָ�������ļ�·��
    int amt;//�������ݵ�����

    if (n == 1) amt = getnum(conf.recordcount1, conf.recordcount2);//�������в���ֻ��һ��ʱ

    if (n == 2) {
        if(strspn(argv[1], "0123456789") == strlen(argv[1])){//��һ������ǵڶ�������������
            amt = atoi(argv[1]);
            if(amt >= conf.recordcount1 || amt <= conf.recordcount2){
                printf("����������������Ϸ�\n");
                amt = getnum(conf.recordcount1, conf.recordcount2);
            }
        }
        else{//����һ�������û���������ݣ��������ļ��������ǵ�ַ
            name = argv[1];
            amt = getnum(conf.recordcount1, conf.recordcount2);
        }
    }//�������в���������

    if (n == 3) {
        amt = atoi(argv[1]);//��ȡ������������
        if(amt >= conf.recordcount1 || amt <= conf.recordcount2){
            printf("����������������Ϸ�\n");
            amt = getnum(conf.recordcount1, conf.recordcount2);
        }
        name = argv[2];//��ȡ�����ļ�����λ��
    }//���������������в���

    if(n > 3){
        printf("����������࣬�������\n");
        exit;
    }
    //�������������򱨴����

    if(name == NULL){
        printf("�����������ļ�·�����ļ���\n");
        char na[MAX_STR_LEN];
        scanf("%s", na);
        name = na;
    }
    //nameΪ��ʱ��ȡ�û�����ĵ�ַ

    int flag = 0;//flag�����ж�����ĺϷ���
    int i = 0;
    int check = 0;//check��ʾ�Ƿ�ʹ��Ĭ�ϴ洢λ��

    while(flag == 0){

        int n = strlen(name);

        for(i = 0; i < n; i++) if((name[i]==':' && i != 1) ||name[i]=='*'||name[i]=='\"'||name[i]=='<'||name[i]=='>'||name[i]=='|') break;
        //���Ƿ��ַ�
        if(name[n-1]!='t'||name[n-2]!='x'||name[n-3]!='t'||name[n-4]!='.') i = 0;
        //����ǲ���txt��β
        if(i >= n){
            flag = 1;
            break;
        }
        printf("���벻�Ϸ�\n");
        printf("�����������ļ�·�����ļ���,����r����ʹ��Ĭ��·�����ļ���\n");
        char na1[MAX_STR_LEN];
        scanf("%s", na1);
        if(na1[0] == 'r' && strlen(na1) == 1){//�ж��ַ���ȷ���û��Ƿ�ѡ�������
            check = 1;
            break;
        }
        name = na1;     
    }
    //ѭ��ֱ����ȡ���Ϸ�����

    if(check == 1) conf.number = amt;//ʹ��Ĭ��λ��
    else{
        conf.number = amt;//д����������
        for(i = strlen(name)-4; i > 0; i--) if(name[i] == '/') break;//�ж��û��������ļ�������·��
        if(i == 0){
            for(int j = 0; j < strlen(name); j++) conf.filename[j] = name[j];
            conf.filename[strlen(name)] = '\0';
            exit;
        }
        //ֻ�������ļ���ʱ
        else{
            for(int j = 0; j < i; j++) conf.filesavepath[j] = name[j];
            conf.filesavepath[i] = '\0';
            for(int j = i+1; j < strlen(name); j++) conf.filename[j-i-1]=name[j];
            conf.filename[strlen(name)-i-1] = '\0';
        }
    }

    char *where = conf.filesavepath;
    strcat(where, "/");
    strcat(where, conf.filename);
    //where��ʾ����·��

    int mode;
    printf("��ѿ���ʵ��3����:\n1.�������ݼ�¼�ļ�(ʹ�ö�ά����洢)\n2.�������ݼ�¼�ļ�(ʹ�ýṹ������洢)\n��������Ҫִ�е����:\n");
    //���в˵�����

    scanf("%d", &mode);
    if(mode == 1) OP1(conf, where);//�ö�ά����
    else if(mode == 2) OP2(conf, where);//ʹ�ýṹ��
    else printf("�������,�������\n");
}