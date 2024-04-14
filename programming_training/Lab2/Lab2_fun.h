#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <cstring>
using namespace std;

int getnum(int amt);

int** newarry(int amt);

int** random(int** arr, int x, int y);

void writetxt(int** arr, int x, int y, char* name);

void opentxt(char* name);


