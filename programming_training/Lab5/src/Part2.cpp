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
    //�����ж�ȡ��ַ���г��򣬶�ȡtxt�ļ���ַ��html����λ��

    cout << "��ѡ��ģʽ��\n1.�Զ����չʾģʽ\n2.��Ĭ���չʾģʽ\n";
    cin >> mode;
    //ʶ��ģʽ��������
    if (mode == '1') {
        sprintf_s(cmd, "start %s", argv[2]);
        system(cmd);
        //����ҳ
    }
    if (mode == '2') {
        cout << "������html�ļ����ļ�·��Ϊ��" << argv[2] << endl;
    }

    return 0;
}
