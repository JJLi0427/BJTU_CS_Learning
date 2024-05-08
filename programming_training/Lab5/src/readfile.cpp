#include "readfile.h"

void readfile(char* locate, struct List L[6]) {
    FILE* fp = fopen(locate, "r");

    for (int i = 0; i < 6; i++) {
        fscanf(fp, "%s", L[i].name);
    }
    //读取统计项目名
    for (int i = 0; i < 6; i++) {
        fscanf(fp, "%d", &L[i].num);
    }
    //读取统计数

    fclose(fp);
}
//读取统计结果文件，存储到结构体数组