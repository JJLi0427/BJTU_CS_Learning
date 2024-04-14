#include "Lab4_main.h"

void run(int n, char *argv[]){

    CONF *conf;
    conf = (CONF *)malloc(sizeof(CONF));
    //新建一个conf结构体，申请空间
    readconf(conf);
    //调用封装函数读入配置文件数据，下面直接调用即可

    int opt = -1;
    while(opt != 0){

        printf("\n");
        printf("李佳骏的实验4程序：\n");  
        printf("1. 调用实验3程序生成记录文件\n");
        printf("2.读取指定数据记录文件（二维数组存储方式）\n"); 
        printf("3.读取指定数据记录文件（结构体数组存储方式）\n"); 
        printf("4.读取指定数据记录文件（指针数组存储方式）\n"); 
        printf("5.读取指定数据记录文件（链表存储方式）\n"); 
        printf("6. 调用实验3生成数据记录文件，同时读取数据记录文件（二维数组方式存储）\n"); 
        printf("7. 调用实验3生成数据记录文件，同时读取数据记录文件（结构体数组方式存储）\n"); 
        printf("8. 调用实验3生成数据记录文件，同时读取数据记录文件（指针数组方式存储）\n"); 
        printf("9. 调用实验3生成数据记录文件，同时读取数据记录文件（链表方式存储）\n"); 
        printf("10. 调用实验3生成数据记录文件，同时读取数据记录文件并排序（二维数组方式存储）\n"); 
        printf("11. 调用实验3生成数据记录文件，同时读取数据记录文件并排序（结构体数组方式存储）\n"); 
        printf("12. 调用实验3生成数据记录文件，同时读取数据记录文件并排序（指针数组方式存储）\n"); 
        printf("13. 调用实验3生成数据记录文件，同时读取数据记录文件并排序（链表方式存储）\n"); 
        printf("14. 重新设置配置参数值\n"); 
        printf("0. 退出\n"); 
        printf("请输入您要执行的程序序号：\n");
        //菜单界面

        scanf("%d", &opt);
        getchar();
        //下面这个if包含的是需要调用Lab3.exe程序的
        if(opt == 1 || opt == 6 || opt == 7 || opt == 8 || opt == 9 || opt == 10 || opt == 11 || opt == 12 || opt == 13){

            //readconf(conf);
            //先执行一遍readconf清除之前运行的缓存

            printf("\n程序有两种工作模式：1.自动模式 2.交互模式\n");
            if(conf->workmode == 1)
                printf("当前默认为：(1.自动模式)\n");
            if(conf->workmode == 2) 
                printf("当前默认为：(2.交互模式)\n");
            //程序工作模式的提示

            printf("\n");
            char *where;
            //where是生成文件的位置

            if(conf->workmode == 1){
                //执行自动模式
                c1(conf);
                where = conf->filesavepath;
                strcat(where, "/");
                strcat(where, conf->filename);
                //这里是自动模式直接从配置文件拼接出完整文件路径
            }

            if(conf->workmode == 2){
                //执行交互模式
                int x;
                printf("请输入你要生成的数据条数(%d =< x =< %d)\n", conf->recordcount2, conf->recordcount1);
                scanf("%d", &x);
                while(x < conf->recordcount2 || x > conf->recordcount1){
                    printf("你输入的数据不合法，请重新输入：(%d <= x <= %d)\n", conf->recordcount2, conf->recordcount1);
                    scanf("%d", &x);
                    //获得正确的数据条数
                }

                printf("请输需要生成的文件绝对路径\n");
                char str[MAX_STR_LEN];
                scanf("%s", str);

                int len = strlen(str);
                //len为字符串长
                int flag = 0;
                //指示字符串是否为合法路径
                int i;
                while (flag == 0){
                    for(i = 0; i < len; i++){
                        if((str[i]==':' && i != 1)||str[i]=='*'||str[i]=='\"'||str[i]=='<'||str[i]=='>'||str[i]=='|')
                            break;
                    }
                    //扫描整个字符串
                    if(i >= len){
                        flag = 1;
                        break;
                    }
                    if(flag == 0) printf("输入的路径含有非法字符，请重新输入：\n");
                    scanf("%s", str);
                    //合法字符串跳出循环
                }
                where = str;
                c2(x, where);
            }
            //在交互模式下要获取一下用户选定的文件完整路径和数据条数

            printf("\n请确保Lab3.exe已经运行完毕\n");
            system("pause");
            //暂停一会等待执行完Lab3.exe,在经过用户确认前面程序执行完成后继续

            if(opt == 6) load1(where, 0);
            if(opt == 7) load2(where, 0);
            if(opt == 8) load3(where, 0);
            if(opt == 9) load4(where, 0);
            if(opt == 10) load1(where, 1);
            if(opt == 11) load2(where, 1);
            if(opt == 12) load3(where, 1);
            if(opt == 13) load4(where, 1);
            //进入程序不同的工作模式
            //所有load函数第二个参数是是否需要排序的指示，1表示需要排序，0表示不需要

        }
        
        //以下选项是读取文件数据的
        if(opt == 2 || opt == 3 || opt == 4 || opt == 5){

            char *where;
            char str[MAX_STR_LEN];
            printf("请输入文件的地址\n");
            scanf("%s", str);
            where = str;
            //在读取指定文件的情况下获取文件名和地址
            if(opt == 2) load1(where, 0);
            if(opt == 3) load2(where, 0);
            if(opt == 4) load3(where, 0);
            if(opt == 5) load4(where, 0);
        }

        if(opt == 14) writeconf(conf);
        //重置程序，重新读入结构体

    }
    //while实现循环菜单显示
}