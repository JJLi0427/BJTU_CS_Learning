#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <cstring>
#include "Lab3_data.h"
using namespace std;

int getnum(int max, int min);
//获取有效的数据条数的值

void OP1(CONF conf, char *where);
//模式1运行

void OP2(CONF conf, char *where);
//模式2运行

void opentxt(char *name);
//打开txt文件

int random(int max, int min);
//产生随机数