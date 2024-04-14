#include "Lab4_conf.h"

void readconf(CONF *conf){
    FILE *fp = fopen("conf.ini", "r");
    fscanf(fp, "%s", conf->filesavepath);
    fscanf(fp, "%s", conf->filename);
    fscanf(fp, "%d", &conf->maxvalue1);
    fscanf(fp, "%d", &conf->minvalue1);
    fscanf(fp, "%d", &conf->maxvalue2);
    fscanf(fp, "%d", &conf->minvalue2);
    fscanf(fp, "%d", &conf->recordcount1);
    fscanf(fp, "%d", &conf->recordcount2);
    fscanf(fp, "%d", &conf->workmode);
    fclose(fp);
}
//��������Ϊ��ȡ�����ļ�

void writeconf(CONF *conf){
    int opt = -1;
    //ָʾѡ�����Ŀ
    while(opt != 0){

        printf("\n���ڵĳ��������ǣ�\nĬ�������ļ�Ŀ¼��%s\nĬ�������ļ�����%s\n��1��2��Ԫ��ȡֵ��Χ(%d <= x <= %d)\n��3��Ԫ��ȡֵ��Χ(%d <= x <= %d)\n���ݼ�¼����ȡֵ��Χ(%d =< x =< %d)\n",
            conf->filesavepath, conf->filename, conf->minvalue1, conf->maxvalue1, conf->minvalue2, conf->maxvalue2, conf->recordcount2, conf->recordcount1);
        if(conf->workmode == 1) printf("���ڳ���Ĺ���ģʽ�ǣ�1.�Զ�ģʽ\n");
        if(conf->workmode == 2) printf("���ڳ���Ĺ���ģʽ�ǣ�2.����ģʽ\n");
        printf("\n��ִ�еĲ����У�\n");
        printf("1. ����1��2��Ԫ�ص����ֵ\n");
        printf("2. ����1��2��Ԫ�ص���Сֵ\n");
        printf("3. ���ĵ�3��Ԫ�ص����ֵ\n");
        printf("4. ���ĵ�3��Ԫ�ص���Сֵ\n");
        printf("5. �������ݼ�¼���������ֵ\n");
        printf("6. �������ݼ�¼��������Сֵ\n");
        printf("7. ���ĳ�����ģʽ\n");
        printf("8. ����Ĭ�������ļ�Ŀ¼\n");
        printf("9. ����Ĭ�������ļ���\n");
        printf("10. ���´�conf.ini�����������\n");
        printf("11. �����ڵ����ø���д��conf.ini�������µ�Ĭ������\n");
        printf("��������Ҫִ�еĲ������(����0�����˳�)��\n");
        //�˵�����

        scanf("%d", &opt);
        if(opt == 1) conf->maxvalue1 = getnewmax(conf->maxvalue1, conf->minvalue1);
        else if(opt == 2) conf->minvalue1 = getnewmin(conf->minvalue1, conf->maxvalue1);
        else if(opt == 3) conf->maxvalue2 = getnewmax(conf->maxvalue2, conf->minvalue2);
        else if(opt == 4) conf->minvalue2 = getnewmin(conf->minvalue2, conf->maxvalue2);
        else if(opt == 5) conf->recordcount2 = getnewmin(conf->recordcount2, conf->recordcount1);
        else if(opt == 6) conf->recordcount1 = getnewmax(conf->recordcount1, conf->recordcount2);

        else if(opt == 7){
            printf("\n���������ֹ���ģʽ��1.�Զ�ģʽ 2.����ģʽ\n");
            printf("����������Ҫ�Ĺ���ģʽ����ţ�\n");
            int t;
            scanf("%d", &t);
            if(t == 1) conf->workmode = 1;
            else if(t ==2) conf->workmode =2;
            else printf("������󣬸��ĳ�����ģʽʧ��\n");
        }

        else if(opt == 8){
            printf("\n�����µ�Ĭ�������ļ�Ŀ¼(����·��)��\n");
            char str[MAX_STR_LEN];
            scanf("%s", str);

            int i, flag = 0, len = strlen(str);
            for(i = 0; i < len; i++){
                if((str[i]==':' && i != 1)||str[i]=='*'||str[i]=='\"'||str[i]=='<'||str[i]=='>'||str[i]=='|')
                    break;
            }
            //ɨ�������ַ���
            if(i >= len) flag = 1;
            if(flag == 0) printf("���뺬�зǷ��ַ�������Ĭ�������ļ�·��ʧ��\n");
            if(flag == 1){
                strcpy(conf->filesavepath, str);
                conf->filesavepath[len] = '\0';
            }
        }
        else if(opt == 9){
            printf("\n�����µ�Ĭ�������ļ���(.txt��β)��\n");
            char str[MAX_STR_LEN];
            scanf("%s", str);

            int i, flag = 0, len = strlen(str);
            for(i = 0; i < len-4; i++){
                if((str[i]==':' && i != 1)||str[i]=='*'||str[i]=='\"'||str[i]=='<'||str[i]=='>'||str[i]=='|')
                    break;
            }
            //ɨ�������ַ���
            if(i >= len) flag = 1;
            if(str[len-1] != 't' || str[len-2] != 'x' || str[len-3] != 't' || str[len-4] != '.') flag = 0;
            if(flag == 0) printf("���뺬�зǷ��ַ�������Ĭ�������ļ���ʧ��\n");
            if(flag == 1){
                strcpy(conf->filename, str);
                conf->filename[len] = '\0';
            }
        }

        else if(opt == 10) readconf(conf);
        else if(opt == 11){
            FILE *fp = fopen("conf.ini", "w+");
            fprintf(fp, "%s\n", conf->filesavepath);
            fprintf(fp, "%s\n", conf->filename);
            fprintf(fp, "%d\n", conf->maxvalue1);
            fprintf(fp, "%d\n", conf->minvalue1);
            fprintf(fp, "%d\n", conf->maxvalue2);
            fprintf(fp, "%d\n", conf->minvalue2);
            fprintf(fp, "%d\n", conf->recordcount1);
            fprintf(fp, "%d\n", conf->recordcount2);
            fprintf(fp, "%d\n", conf->workmode);
            fclose(fp);
        }

        else if(opt == 0) break;
        else printf("�������,�޴�ѡ��\n");
    }

}

//�����װ�˻�ȡ�µ����ֵ����Сֵ�ĺ������������

int getnewmax(int max, int min){
    int t;
    printf("\n�������µ����ֵ(x > %d)\n", min);
    scanf("%d", &t);
    if(t > min) max = t;
    else printf("������󣬸���ʧ��\n");
    return max;  
}
//�������ֵ�ĺ���

int getnewmin(int min, int max){
    int t;
    printf("\n�������µ���Сֵ(x < %d)\n", max);
    scanf("%d", &t);
    if(t < max) min = t;
    else printf("������󣬸���ʧ��\n");
    return min; 
}
//������Сֵ�ĺ���