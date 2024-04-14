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
//函数功能为读取配置文件

void writeconf(CONF *conf){
    int opt = -1;
    //指示选择的项目
    while(opt != 0){

        printf("\n现在的程序设置是：\n默认生成文件目录：%s\n默认生成文件名：%s\n第1，2个元素取值范围(%d <= x <= %d)\n第3个元素取值范围(%d <= x <= %d)\n数据记录条数取值范围(%d =< x =< %d)\n",
            conf->filesavepath, conf->filename, conf->minvalue1, conf->maxvalue1, conf->minvalue2, conf->maxvalue2, conf->recordcount2, conf->recordcount1);
        if(conf->workmode == 1) printf("现在程序的工作模式是：1.自动模式\n");
        if(conf->workmode == 2) printf("现在程序的工作模式是：2.交互模式\n");
        printf("\n可执行的操作有：\n");
        printf("1. 更改1，2个元素的最大值\n");
        printf("2. 更改1，2个元素的最小值\n");
        printf("3. 更改第3个元素的最大值\n");
        printf("4. 更改第3个元素的最小值\n");
        printf("5. 更改数据记录条数的最大值\n");
        printf("6. 更改数据记录条数的最小值\n");
        printf("7. 更改程序工作模式\n");
        printf("8. 更改默认生成文件目录\n");
        printf("9. 更改默认生成文件名\n");
        printf("10. 重新从conf.ini载入参数配置\n");
        printf("11. 把现在的配置覆盖写入conf.ini，生成新的默认配置\n");
        printf("请输入你要执行的操作序号(输入0可以退出)：\n");
        //菜单界面

        scanf("%d", &opt);
        if(opt == 1) conf->maxvalue1 = getnewmax(conf->maxvalue1, conf->minvalue1);
        else if(opt == 2) conf->minvalue1 = getnewmin(conf->minvalue1, conf->maxvalue1);
        else if(opt == 3) conf->maxvalue2 = getnewmax(conf->maxvalue2, conf->minvalue2);
        else if(opt == 4) conf->minvalue2 = getnewmin(conf->minvalue2, conf->maxvalue2);
        else if(opt == 5) conf->recordcount2 = getnewmin(conf->recordcount2, conf->recordcount1);
        else if(opt == 6) conf->recordcount1 = getnewmax(conf->recordcount1, conf->recordcount2);

        else if(opt == 7){
            printf("\n程序有两种工作模式：1.自动模式 2.交互模式\n");
            printf("请输入你想要的工作模式的序号：\n");
            int t;
            scanf("%d", &t);
            if(t == 1) conf->workmode = 1;
            else if(t ==2) conf->workmode =2;
            else printf("输入错误，更改程序工作模式失败\n");
        }

        else if(opt == 8){
            printf("\n请输新的默认生成文件目录(绝对路径)：\n");
            char str[MAX_STR_LEN];
            scanf("%s", str);

            int i, flag = 0, len = strlen(str);
            for(i = 0; i < len; i++){
                if((str[i]==':' && i != 1)||str[i]=='*'||str[i]=='\"'||str[i]=='<'||str[i]=='>'||str[i]=='|')
                    break;
            }
            //扫描整个字符串
            if(i >= len) flag = 1;
            if(flag == 0) printf("输入含有非法字符，更改默认生成文件路径失败\n");
            if(flag == 1){
                strcpy(conf->filesavepath, str);
                conf->filesavepath[len] = '\0';
            }
        }
        else if(opt == 9){
            printf("\n请输新的默认生成文件名(.txt结尾)：\n");
            char str[MAX_STR_LEN];
            scanf("%s", str);

            int i, flag = 0, len = strlen(str);
            for(i = 0; i < len-4; i++){
                if((str[i]==':' && i != 1)||str[i]=='*'||str[i]=='\"'||str[i]=='<'||str[i]=='>'||str[i]=='|')
                    break;
            }
            //扫描整个字符串
            if(i >= len) flag = 1;
            if(str[len-1] != 't' || str[len-2] != 'x' || str[len-3] != 't' || str[len-4] != '.') flag = 0;
            if(flag == 0) printf("输入含有非法字符，更改默认生成文件名失败\n");
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
        else printf("输入错误,无此选项\n");
    }

}

//下面封装了获取新的最大值和最小值的函数，方便调用

int getnewmax(int max, int min){
    int t;
    printf("\n请输入新的最大值(x > %d)\n", min);
    scanf("%d", &t);
    if(t > min) max = t;
    else printf("输入错误，更改失败\n");
    return max;  
}
//更改最大值的函数

int getnewmin(int min, int max){
    int t;
    printf("\n请输入新的最小值(x < %d)\n", max);
    scanf("%d", &t);
    if(t < max) min = t;
    else printf("输入错误，更改失败\n");
    return min; 
}
//更改最小值的函数