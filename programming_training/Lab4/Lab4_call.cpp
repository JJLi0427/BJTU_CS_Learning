#include "Lab4_call.h"

void c1(CONF *conf){
    char where[MAX_STR_LEN]; 
    strcpy(where, conf->filesavepath);
    strcat(where, "/");
    strcat(where, conf->filename);
    //获取数据条数和文件的位置

    srand(time(NULL));
    conf->number = rand() % (conf->recordcount1 - conf->recordcount2 + 1) + conf->recordcount2; 
    //随机数生成文件数据条数

    char cmd[1024];
    sprintf(cmd, "Lab3.exe %d %s", conf->number, where);
    //直接用r调用Lab3.exe的默认模式
    system(cmd);
}
//自动默认模式运行Lab3.exe

void c2(int x, char *where){
    char cmd[1024];
    sprintf(cmd, "Lab3.exe %d %s", x, where);
    system(cmd);
}
//交互模式运行