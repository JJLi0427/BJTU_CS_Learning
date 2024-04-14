#include "Lab2_fun.h"

int getnum(int amt) {
    cout << "请输入数据条数" << endl;
    int i;
    i = scanf("%d", &amt);
    while(i == 0) {
        cout << "数据条数获取错误，请输入数字" << endl;
        while(getchar() != '\n') {}
        i = scanf("%d", &amt);
    }
    //判断输入是否正确
    return amt;
}
//获取数据条数

int** newarry(int amt) {
    int** arr;
    //创建二维指针
    arr = new int* [amt];
    for (int i = 0; i < amt; i++) {
        arr[i] = new int[3];
        if (NULL == arr[i]) {
            cout << "数组空间创建失败" << endl;
            exit(0);
        }
    }
    //为每一行申请空间
    return arr;
}
//根据所需数据量创建二维数组

int** random(int** arr, int x, int y) {
    srand(time(0));
    //加入随机数种子
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            arr[i][j] = rand() % 101;
            //随机数范围为0-100
        }
    }
    //随机数存储到二维数组
    return arr;
}
//产生随机数，并且暂存到二维数组

void writetxt(int** arr, int x, int y, char* name) {
    FILE* fp = fopen(name, "w+");
    if (NULL == fp) {
        cout << "打开文件失败" << endl;
        exit(0);
    }
    fprintf(fp,"%d\n", x);
    //打开文件并且写入 
    for (int i = 0; i < x; i++) {
        fprintf(fp, "%d,%d,%d\n", arr[i][0], arr[i][1], arr[i][2]);
        //写入数据到txt
        printf("%d,%d,%d\n", arr[i][0], arr[i][1], arr[i][2]);
        //输出数据到屏幕
    }
    fclose(fp);
}
//把数组存储的随机数写入到txt文件并且输出到屏幕展示

void opentxt(char* name) {
    char cmd[100];
    sprintf(cmd, "start %s", name);
    system(cmd);
}
//把写好的txt文件打开展示
