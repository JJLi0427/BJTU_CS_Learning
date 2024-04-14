#include "Lab2_run.h"

void run(int n, char *argv[]) {
    if (n == 2 || n > 3) {
        cout << "输入参数非法，程序结束运行" << endl;
        exit(0);
    }
    //判断是否为非法输入

    int amt;
    char *name;
    //定义amt为行数
    if (n == 3) {
        name = strcat(argv[2], ".txt");
        if(strspn(argv[1], "0123456789") == strlen(argv[1])) amt = atoi(argv[1]);
        else {
            cout << "数据条数获取错误，含有其他字符" << endl; 
            amt = getnum(amt);
        }
    }
    //若传入参数足够且合规则读取需生成的行数

    if (n == 1) {
        amt = getnum(amt);
        char out[10]="out.txt";
        name = out;
        //默认生成out.txt文件
    }
    //获取缺少的参数数据

    writetxt(random(newarry(amt), amt, 3), amt, 3, name);
    //生成随机数到数组，然后写入到txt，并且打印到屏幕上展示
    opentxt(name);
    //展示txt文件
}