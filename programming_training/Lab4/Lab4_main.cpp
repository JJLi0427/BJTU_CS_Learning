#include "Lab4_main.h"

void run(int n, char *argv[]){

    CONF *conf;
    conf = (CONF *)malloc(sizeof(CONF));
    //�½�һ��conf�ṹ�壬����ռ�
    readconf(conf);
    //���÷�װ�������������ļ����ݣ�����ֱ�ӵ��ü���

    int opt = -1;
    while(opt != 0){

        printf("\n");
        printf("��ѿ���ʵ��4����\n");  
        printf("1. ����ʵ��3�������ɼ�¼�ļ�\n");
        printf("2.��ȡָ�����ݼ�¼�ļ�����ά����洢��ʽ��\n"); 
        printf("3.��ȡָ�����ݼ�¼�ļ����ṹ������洢��ʽ��\n"); 
        printf("4.��ȡָ�����ݼ�¼�ļ���ָ������洢��ʽ��\n"); 
        printf("5.��ȡָ�����ݼ�¼�ļ�������洢��ʽ��\n"); 
        printf("6. ����ʵ��3�������ݼ�¼�ļ���ͬʱ��ȡ���ݼ�¼�ļ�����ά���鷽ʽ�洢��\n"); 
        printf("7. ����ʵ��3�������ݼ�¼�ļ���ͬʱ��ȡ���ݼ�¼�ļ����ṹ�����鷽ʽ�洢��\n"); 
        printf("8. ����ʵ��3�������ݼ�¼�ļ���ͬʱ��ȡ���ݼ�¼�ļ���ָ�����鷽ʽ�洢��\n"); 
        printf("9. ����ʵ��3�������ݼ�¼�ļ���ͬʱ��ȡ���ݼ�¼�ļ�������ʽ�洢��\n"); 
        printf("10. ����ʵ��3�������ݼ�¼�ļ���ͬʱ��ȡ���ݼ�¼�ļ������򣨶�ά���鷽ʽ�洢��\n"); 
        printf("11. ����ʵ��3�������ݼ�¼�ļ���ͬʱ��ȡ���ݼ�¼�ļ������򣨽ṹ�����鷽ʽ�洢��\n"); 
        printf("12. ����ʵ��3�������ݼ�¼�ļ���ͬʱ��ȡ���ݼ�¼�ļ�������ָ�����鷽ʽ�洢��\n"); 
        printf("13. ����ʵ��3�������ݼ�¼�ļ���ͬʱ��ȡ���ݼ�¼�ļ�����������ʽ�洢��\n"); 
        printf("14. �����������ò���ֵ\n"); 
        printf("0. �˳�\n"); 
        printf("��������Ҫִ�еĳ�����ţ�\n");
        //�˵�����

        scanf("%d", &opt);
        getchar();
        //�������if����������Ҫ����Lab3.exe�����
        if(opt == 1 || opt == 6 || opt == 7 || opt == 8 || opt == 9 || opt == 10 || opt == 11 || opt == 12 || opt == 13){

            //readconf(conf);
            //��ִ��һ��readconf���֮ǰ���еĻ���

            printf("\n���������ֹ���ģʽ��1.�Զ�ģʽ 2.����ģʽ\n");
            if(conf->workmode == 1)
                printf("��ǰĬ��Ϊ��(1.�Զ�ģʽ)\n");
            if(conf->workmode == 2) 
                printf("��ǰĬ��Ϊ��(2.����ģʽ)\n");
            //������ģʽ����ʾ

            printf("\n");
            char *where;
            //where�������ļ���λ��

            if(conf->workmode == 1){
                //ִ���Զ�ģʽ
                c1(conf);
                where = conf->filesavepath;
                strcat(where, "/");
                strcat(where, conf->filename);
                //�������Զ�ģʽֱ�Ӵ������ļ�ƴ�ӳ������ļ�·��
            }

            if(conf->workmode == 2){
                //ִ�н���ģʽ
                int x;
                printf("��������Ҫ���ɵ���������(%d =< x =< %d)\n", conf->recordcount2, conf->recordcount1);
                scanf("%d", &x);
                while(x < conf->recordcount2 || x > conf->recordcount1){
                    printf("����������ݲ��Ϸ������������룺(%d <= x <= %d)\n", conf->recordcount2, conf->recordcount1);
                    scanf("%d", &x);
                    //�����ȷ����������
                }

                printf("������Ҫ���ɵ��ļ�����·��\n");
                char str[MAX_STR_LEN];
                scanf("%s", str);

                int len = strlen(str);
                //lenΪ�ַ�����
                int flag = 0;
                //ָʾ�ַ����Ƿ�Ϊ�Ϸ�·��
                int i;
                while (flag == 0){
                    for(i = 0; i < len; i++){
                        if((str[i]==':' && i != 1)||str[i]=='*'||str[i]=='\"'||str[i]=='<'||str[i]=='>'||str[i]=='|')
                            break;
                    }
                    //ɨ�������ַ���
                    if(i >= len){
                        flag = 1;
                        break;
                    }
                    if(flag == 0) printf("�����·�����зǷ��ַ������������룺\n");
                    scanf("%s", str);
                    //�Ϸ��ַ�������ѭ��
                }
                where = str;
                c2(x, where);
            }
            //�ڽ���ģʽ��Ҫ��ȡһ���û�ѡ�����ļ�����·������������

            printf("\n��ȷ��Lab3.exe�Ѿ��������\n");
            system("pause");
            //��ͣһ��ȴ�ִ����Lab3.exe,�ھ����û�ȷ��ǰ�����ִ����ɺ����

            if(opt == 6) load1(where, 0);
            if(opt == 7) load2(where, 0);
            if(opt == 8) load3(where, 0);
            if(opt == 9) load4(where, 0);
            if(opt == 10) load1(where, 1);
            if(opt == 11) load2(where, 1);
            if(opt == 12) load3(where, 1);
            if(opt == 13) load4(where, 1);
            //�������ͬ�Ĺ���ģʽ
            //����load�����ڶ����������Ƿ���Ҫ�����ָʾ��1��ʾ��Ҫ����0��ʾ����Ҫ

        }
        
        //����ѡ���Ƕ�ȡ�ļ����ݵ�
        if(opt == 2 || opt == 3 || opt == 4 || opt == 5){

            char *where;
            char str[MAX_STR_LEN];
            printf("�������ļ��ĵ�ַ\n");
            scanf("%s", str);
            where = str;
            //�ڶ�ȡָ���ļ�������»�ȡ�ļ����͵�ַ
            if(opt == 2) load1(where, 0);
            if(opt == 3) load2(where, 0);
            if(opt == 4) load3(where, 0);
            if(opt == 5) load4(where, 0);
        }

        if(opt == 14) writeconf(conf);
        //���ó������¶���ṹ��

    }
    //whileʵ��ѭ���˵���ʾ
}