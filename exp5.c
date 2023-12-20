#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_LEN 1000

struct stack {
    char s[MAX_LEN];
    int i[MAX_LEN];
    int point[MAX_LEN];
    int top;
}; // 分析栈数据结构

struct quadruple {
    char op[MAX_LEN];
    char arg1[MAX_LEN];
    char arg2[MAX_LEN];
    char result[MAX_LEN];
}; // 四元式数据结构

struct quadruple quad[MAX_LEN]; // 存储四元式
int quadTop = 0; // 四元式栈顶

// 1.S→V=E  2.E→E+T  3.E→E-T  4.E→T  5.T→T*F  6.T→T/F  7.T→F  8.F→(E) 9.F→i  10.V→i
// 表中大于0对应移进，小于0则对应先归约后移进，0为不存在的状态
                    //          GOTO           |    ACTION
                    //i, =, +, -, *, /, (, ), #, S, E, T, F, V
int table[20][14] ={{ 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2},// 0
                    { 0, 0, 0, 0, 0, 0, 0, 0,-11,0,0, 0, 0, 0},// 1
                    { 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},// 2
                    {-10,-10,-10,-10,-10,-10,-10,-10,-10, 0, 0, 0, 0, 0},//3
                    { 9, 0, 0, 0, 0, 0, 8, 0, 0, 0, 5, 6, 7, 0},// 4
                    {-1,-1,10,11,-1,-1,-1,-1,-1, 0, 0, 0, 0, 0},// 5
                    {-4,-4,-4,-4,12,13,-4,-4,-4, 0, 0, 0, 0, 0},// 6
                    {-7,-7,-7,-7,-7,-7,-7,-7,-7, 0, 0, 0, 0, 0},// 7
                    { 9, 0, 0, 0, 0, 0, 8, 0, 0, 0,14, 6, 7, 0},// 8
                    {-9,-9,-9,-9,-9,-9,-9,-9,-9, 0, 0, 0, 0, 0},// 9
                    { 9, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0,15, 7, 0},//10
                    { 9, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0,16, 7, 0},//11
                    { 9, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0,17, 0},//12
                    { 9, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0,18, 0},//13
                    { 0, 0,10,11, 0, 0, 0,19, 0, 0, 0, 0, 0, 0},//14
                    {-2,-2,-2,-2,12,13,-2,-2,-2, 0, 0, 0, 0, 0},//15
                    {-3,-3,-3,-3,12,13,-3,-3,-3, 0, 0, 0, 0, 0},//16
                    {-5,-5,-5,-5,-5,-5,-5,-5,-5, 0, 0, 0, 0, 0},//17
                    {-6,-6,-6,-6,-6,-6,-6,-6,-6, 0, 0, 0, 0, 0},//18
                    {-8,-8,-8,-8,-8,-8,-8,-8,-8, 0, 0, 0, 0, 0}};//19

int getindex(char ch) {
    switch(ch) {
        case 'i': return 0;
        case '=': return 1;
        case '+': return 2;
        case '-': return 3;
        case '*': return 4;
        case '/': return 5;
        case '(': return 6;
        case ')': return 7;
        case '#': return 8;
        case 'S': return 9;
        case 'E': return 10;
        case 'T': return 11;
        case 'F': return 12;
        case 'V': return 13;
        default: return -1;
    }
}

void printSLR(char *str, struct stack *stk, int now) { // 打印分析状态
    for(int i = 0; i <= stk->top; i++) {
        printf("%c:%2d   ", stk->s[i], stk->i[i]); // 栈状态
    }
    for(int i = 0; i <= 60 - stk->top*7; i++) {
        printf(" ");
    }
    for(int i = now; i < strlen(str); i++) {
        printf("%c", str[i]); // 串状态
    }
    printf("\n");
}

void printQuad() { // 打印四元式
    printf("Quadruples:\n");
    for(int i = 1; i <= quadTop; i++) {
        printf("(%s, %s, %s, %s)\n", quad[i].op, quad[i].arg1, quad[i].arg2, quad[i].result);
    }
}

int SLR(char *str, struct stack *stk) { // SLR1分析函数
    quadTop = 0;
    int i = 0;
    int next;
    printf("stack:                                                              str:                  operate:\n");
    while(i < strlen(str)) {
        if(stk->top < 0) return 0; // 分析栈不可能为空
        int y; // 列坐标
        if (str[i] >= 'a' && str[i] <= 'z') y = getindex('i'); // 终结符i
        else y = getindex(str[i]);
        if(y == -1 || table[stk->i[stk->top]][y] == 0) { // 表中不存在的状态，分析报错
            return 0;
        }
        if(table[stk->i[stk->top]][y] > 0) { // 移进操作
            next = table[stk->i[stk->top]][y];
            stk->top++;
            stk->s[stk->top] = str[i];
            stk->i[stk->top] = next;
            stk->point[stk->top] = i;
            i++;
            printSLR(str, stk, i);
        }
        else if(table[stk->i[stk->top]][y] < 0) { // 归约操作
            int tmp = -table[stk->i[stk->top]][y]; // 查GOTO表
            if(tmp == 4 || tmp == 7 || tmp == 9 || tmp == 10) {
                stk->top--; // 要归约1位
            }
            else if(tmp == 2 || tmp == 3 || tmp == 5 || tmp == 6){
                // 生成四元式
                quadTop++;
                if(tmp == 2) strcpy(quad[quadTop].op, "+");
                else if(tmp == 3) strcpy(quad[quadTop].op, "-");
                else if(tmp == 5) strcpy(quad[quadTop].op, "*");
                else strcpy(quad[quadTop].op, "/");
                if(stk->point[stk->top - 2] < 0) sprintf(quad[quadTop].arg1, "t%d", -stk->point[stk->top - 2]);
                else {
                    char arg1[2] = {str[stk->point[stk->top - 2]], '\0'};
                    strcpy(quad[quadTop].arg1, arg1);
                }
                if(stk->point[stk->top] < 0) sprintf(quad[quadTop].arg2, "t%d", -stk->point[stk->top]);
                else {
                    char arg2[2] = {str[stk->point[stk->top]], '\0'};
                    strcpy(quad[quadTop].arg2, arg2);
                }
                for(int j = 0; j < 90; j++) printf(" ");
                printf("t%d = %s %s %s\n", quadTop, quad[quadTop].arg1, quad[quadTop].op, quad[quadTop].arg2); // 打印语义动作
                sprintf(quad[quadTop].result, "t%d", quadTop);
                stk->top -= 3; // 归约3位
                stk->point[stk->top + 1] = -quadTop; // 记录归约产生的中间变量
            }
            else if(tmp == 8) {
                stk->top -= 3; // 归约3位
                stk->point[stk->top + 1] = stk->point[stk->top + 2]; // 消除括号规约
            }
            else if(tmp == 1){
                quadTop++;
                strcpy(quad[quadTop].op, "=");
                if(stk->point[stk->top] < 0) sprintf(quad[quadTop].arg1, "t%d", abs(stk->point[stk->top]));
                else {
                    char arg1[2] = {str[stk->point[stk->top]], '\0'};
                    strcpy(quad[quadTop].arg1, arg1);
                }
                sprintf(quad[quadTop].arg2, " ");
                char res[2] = {str[stk->point[stk->top - 2]], '\0'};
                strcpy(quad[quadTop].result, res);
                for(int i = 0; i < 90; i++) printf(" ");
                printf("%s = %s\n", quad[quadTop].result, quad[quadTop].arg1);
                stk->top -= 3; // 归约V=E
            }
            else stk->top -= 3;
            if(tmp == 1) { 
                y = getindex('S');
                next = table[stk->i[stk->top]][y]; // 查ACTION表
                stk->top++;
                stk->s[stk->top] = 'S';
                stk->i[stk->top] = next; // 归约要修改栈顶
            }
            else if(tmp == 2 || tmp ==3 || tmp == 4) {
                y = getindex('E');
                next = table[stk->i[stk->top]][y]; 
                stk->top++;
                stk->s[stk->top] = 'E';
                stk->i[stk->top] = next;
            }
            else if(tmp == 5 || tmp == 6 || tmp == 7) {
                y = getindex('T');
                next = table[stk->i[stk->top]][y];
                stk->top++;
                stk->s[stk->top] = 'T';
                stk->i[stk->top] = next;
            }
            else if(tmp == 8 || tmp == 9) {
                y = getindex('F');
                next = table[stk->i[stk->top]][y];
                stk->top++;
                stk->s[stk->top] = 'F';
                stk->i[stk->top] = next;
            }
            else if(tmp == 10) {
                y = getindex('V');
                next = table[stk->i[stk->top]][y];
                stk->top++;
                stk->s[stk->top] = 'V';
                stk->i[stk->top] = next;
            }
            else if(tmp == 11) {
                return 1; 
            }
            printSLR(str, stk, i);
        }
    }
    return 0;
}

int main() {
	for(int m = 9; m <= 10; m++) {
		printf("\ntest%d:   ", m);
		char txt[] = "./lexical/analyze"; //读取词法分析文件
		char num[8];
		sprintf(num, "%d.txt", m);
		strcat(txt, num);
		FILE *fp = fopen(txt, "r");
		char buf[MAX_LEN] = "";
		char input[MAX_LEN] = "";
		fgets(buf, MAX_LEN, fp);
		int j = 0;
		for(int k = 0; k < strlen(buf); k++) { // 解析二元序列
			if(buf[k] == '1' && buf[k+1] == ',') {
				k += 3;
				while(1) {
					if(buf[k] == ')' && buf[k+1] == ' ')
						break;
					input[j++] = buf[k++];
				}
				continue;
			}
			if(buf[k] == ',' && buf[k+1] == ' ') {
				k += 2;
				while(1) {
					if(buf[k] == ')' && buf[k+1] == ' ')
						break;
					input[j++] = buf[k++];
				}
			}
		}
		printf("Input scentence: %s\n", input); // input为输入串
		input[j] = '#'; // str为分析用的串，变量被替换为i
		fclose(fp);
        struct stack *stk;
        stk = (struct stack *)malloc(sizeof(struct stack));
		stk->s[0] = '#';
        stk->i[0] = 0;
        stk->point[0] = -1;
        stk->top = 0; //初始化分析栈
        if(!SLR(input, stk)) {
            printf("Gramma illegal\n");
        }
        else {
            printQuad(); // 打印四元式
        }
	}
    return 0;
}
