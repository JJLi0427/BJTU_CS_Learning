#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <cstring>
#include "Lab3_data.h"
using namespace std;

int getnum(int max, int min);
//��ȡ��Ч������������ֵ

void OP1(CONF conf, char *where);
//ģʽ1����

void OP2(CONF conf, char *where);
//ģʽ2����

void opentxt(char *name);
//��txt�ļ�

int random(int max, int min);
//���������