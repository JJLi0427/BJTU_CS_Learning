#include "Lab2_run.h"

void run(int n, char *argv[]) {
    if (n == 2 || n > 3) {
        cout << "��������Ƿ��������������" << endl;
        exit(0);
    }
    //�ж��Ƿ�Ϊ�Ƿ�����

    int amt;
    char *name;
    //����amtΪ����
    if (n == 3) {
        name = strcat(argv[2], ".txt");
        if(strspn(argv[1], "0123456789") == strlen(argv[1])) amt = atoi(argv[1]);
        else {
            cout << "����������ȡ���󣬺��������ַ�" << endl; 
            amt = getnum(amt);
        }
    }
    //����������㹻�ҺϹ����ȡ�����ɵ�����

    if (n == 1) {
        amt = getnum(amt);
        char out[10]="out.txt";
        name = out;
        //Ĭ������out.txt�ļ�
    }
    //��ȡȱ�ٵĲ�������

    writetxt(random(newarry(amt), amt, 3), amt, 3, name);
    //��������������飬Ȼ��д�뵽txt�����Ҵ�ӡ����Ļ��չʾ
    opentxt(name);
    //չʾtxt�ļ�
}