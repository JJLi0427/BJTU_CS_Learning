#include <iostream>
#include <cstring>
#include "List.h"
#include "readfile.h"
#include "writehtml.h"

using namespace std;

int main(int argc, char* argv[]) {

    char mode, cmd[100];
    struct List datalist[6];

    readfile(argv[1], datalist);
    writehtml(argv[2], datalist);
    //命令行读取地址运行程序，读取txt文件地址和html生成位置

    cout << "请选择模式：\n1.自动结果展示模式\n2.静默结果展示模式\n";
    cin >> mode;
    //识别模式并且运行
    if (mode == '1') {
        sprintf_s(cmd, "start %s", argv[2]);
        system(cmd);
        //打开网页
    }
    if (mode == '2') {
        cout << "已生成html文件，文件路径为：" << argv[2] << endl;
    }

    return 0;
}
