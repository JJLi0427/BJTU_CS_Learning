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

char rs0[MAX_LEN];
char rs1[MAX_LEN]; // 设置两个寄存器

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

int english(char ch) {
	if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) return 1;
	else return 0;
}
int number(char ch) {
	if(ch >= '0' && ch <= '9') return 1;
	else return 0;
}
int reserved(char str[]) {
	if(strcmp(str, "void") == 0) return 3;
    else if(strcmp(str, "int") == 0) return 4;
    else if(strcmp(str, "float") == 0) return 5;
    else if(strcmp(str, "double") == 0) return 6;
    else if(strcmp(str, "if") == 0) return 7;
    else if(strcmp(str, "else") == 0) return 8;
    else if(strcmp(str, "for") == 0) return 9;
    else if(strcmp(str, "do") == 0) return 10;
    else if(strcmp(str, "while") == 0) return 11;
	else if(strcmp(str, "break") == 0) return 12;
    else if(strcmp(str, "return") == 0) return 13;
    else return 1;
}
int symbol(char ch) {
	if(ch == ';') return 14;
	else if(ch == ',') return 15;
	else if(ch == '(') return 16;
	else if(ch == ')') return 17;
	else if(ch == '{') return 18;
	else if(ch == '}') return 19;
	else if(ch == '[') return 20;
	else if(ch == ']') return 21;
	else if(ch == '%') return 22;
	else if(ch == '?') return 23;
	else if(ch == ':') return 24;
	else if(ch == '\'') return 25;
	else if(ch == '\"') return 26;
	else if(ch == '.') return 27;
	else return 0;
}

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

int use0(int p) { // 判断是否还会用到寄存器rs0内容
    for(int i = p; i <= quadTop; i++) {
        if(strcmp(quad[i].arg1, rs0) == 0 || strcmp(quad[i].arg2, rs0) == 0) {
            return 1;
        }
    }
    return 0;
}
int use1(int p) { // 判断是否还会用到寄存器rs1内容
    for(int i = p; i <= quadTop; i++) {
        if(strcmp(quad[i].arg1, rs1) == 0 || strcmp(quad[i].arg2, rs1) == 0) {
            return 1;
        }
    }
    return 0;
}

void assembly() {
    printf("Assembly Code:\n"); 
    for(int i = 1; i <= quadTop; i++) {
        char opstr[MAX_LEN];
        if(quad[i].op[0] == '=') { // 赋值语句的处理
            if(strcmp(quad[i].arg1, rs0) == 0){
                printf("MOV %s, R0\n", quad[i].result);
            }
            if(strcmp(quad[i].arg1, rs1) == 0) {
                printf("MOV %s, R1\n", quad[i].result);
            }
            continue;
        }
        else if(quad[i].op[0] == '+') { // 获取对应操作码字符串
            strcpy(opstr, "ADD");
        }
        else if(quad[i].op[0] == '-') {
            strcpy(opstr, "SUB");
        }
        else if(quad[i].op[0] == '*') {
            strcpy(opstr, "MUL");
        }
        else if(quad[i].op[0] == '/') {
            strcpy(opstr, "DIV");
        }
        int flag = 0; // flag为0表示两个寄存器都空闲，1表示找到第一个操作数，2表示找到第二个操作数, 3表示两个操作数都找到
        int tag = -1; // tag为0表示值在rs0，1表示值在rs1
        if((strcmp(rs0, quad[i].arg1) == 0 && strcmp(rs1, quad[i].arg2) == 0) || (strcmp(rs0, quad[i].arg2) == 0 && strcmp(rs1, quad[i].arg1) == 0)) {
            flag = 3;
        }
        else if(strcmp(rs0, quad[i].arg1) == 0) {
            flag = 1, tag = 0;
        }
        else if(strcmp(rs1, quad[i].arg1) == 0) {
            flag = 1, tag = 1;
        }
        else if(strcmp(rs0, quad[i].arg2) == 0) {
            flag = 2, tag = 0;
        }
        else if(strcmp(rs1, quad[i].arg2) == 0) {
            flag = 2, tag = 1;
        }
        if(flag == 0) {
            if(rs0[0] == '\0') {
                printf("MOV R0, %s\n", quad[i].arg1);
                printf("%s R0, %s\n", opstr, quad[i].arg2);
                strcpy(rs0, quad[i].result);
                if(use0(i + 1) == 0) {
                    rs0[0] = '\0';
                }
            }
            else if(rs1[0] == '\0') {
                printf("MOV R1, %s\n", quad[i].arg1);
                printf("%s R1, %s\n", opstr, quad[i].arg2);
                strcpy(rs1, quad[i].result);
                if(use1(i + 1) == 0) {
                    rs1[0] = '\0';
                }
            }
            else {
                printf("Assembly failed\n");
                return;
            }
        }
        else if(flag == 1) {
            if(tag == 0) {
                printf("%s R0, %s\n", opstr, quad[i].arg2);
                strcpy(rs0, quad[i].result);
                if(use0(i + 1) == 0) {
                    rs0[0] = '\0';
                }
            }
            else {
                printf("%s R1, %s\n", opstr, quad[i].arg2);
                strcpy(rs1, quad[i].result);
                if(use1(i + 1) == 0) {
                    rs1[0] = '\0';
                }
            }
        }
        else if(flag == 2) {
            if(tag == 0) {
                printf("%s R0, %s\n", opstr, quad[i].arg1);
                strcpy(rs0, quad[i].result);
                if(use0(i + 1) == 0) {
                    rs0[0] = '\0';
                }
            }
            else {
                printf("%s R1, %s\n", opstr, quad[i].arg1);
                strcpy(rs1, quad[i].result);
                if(use1(i + 1) == 0) {
                    rs1[0] = '\0';
                }
            }
        }
        else if(flag == 3) {
            if(use0(i + 1) == 0) {
                printf("%s R0, R1\n", opstr);
                strcpy(rs0, quad[i].result);
            }
            else {
                printf("%s R1, R0\n", opstr);
                strcpy(rs1, quad[i].result);
            }
        }
    }
}

int SLR(char *str, struct stack *stk) { // SLR1分析函数
    quadTop = 0;
    int i = 0;
    int next;
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
        }
    }
    return 0;
}

int main() {
    for(int i = 9; i <= 10; i++){
		char txt1[] = "./test/test";
		char num[8];
		sprintf(num, "%d.txt", i);
		strcat(txt1, num);
		FILE *fp = fopen(txt1, "r");
		int flag = 0;
		char ch = fgetc(fp);	
		while(!feof(fp)) {
			int j = 0;
			if(ch == ' ' || ch == '\t') {
				ch = fgetc(fp);
				continue;
			}
			else if(ch == '\n'){
				ch = fgetc(fp);
				continue;
			}
			else if(english(ch)) {
				do{
					ch = fgetc(fp);
				}while(english(ch)||number(ch));
			}
			else if(number(ch)) {
				do{
					ch = fgetc(fp);
				}while(number(ch));
			}
			else if(symbol(ch) != 0) {
				ch = fgetc(fp);
			}
			else if(ch == '>') {
				ch = fgetc(fp);
				if(ch == '=') {
					ch = fgetc(fp);
				}
				else if(ch == '>') {
					ch = fgetc(fp);
				}
			}
			else if(ch == '<') {
				ch = fgetc(fp);
				if(ch == '=') {
					ch = fgetc(fp);
				}
				else if(ch == '<') {
					ch = fgetc(fp);
				}
			}
			else if(ch == '!') {
				ch = fgetc(fp);
				if(ch == '=') {
					ch = fgetc(fp);
				}
			}
			else if(ch == '=') {
				ch = fgetc(fp);
				if(ch == '=') {
					ch = fgetc(fp);
				}
			}
			else if(ch == '/') {
				ch = fgetc(fp);
				if(ch == '*') {
					do {
						ch = fgetc(fp);
						if(ch == '*') {
							ch = fgetc(fp);
							if(ch == '/') {
								ch = fgetc(fp);
								break;
							}
						}
					}while(1);
				}
				else if(ch == '/') {
					do {
						ch = fgetc(fp);
					}while(ch != '\n');
					ch = fgetc(fp);
				}
				else if(ch == '=') {
					ch = fgetc(fp);
				}
			}
			else if(ch == '&') {
				ch = fgetc(fp);
				if(ch == '&') {
					ch = fgetc(fp);
				}
			}
			else if(ch == '|') {
				ch = fgetc(fp);
				if(ch == '|') {
					ch = fgetc(fp);
				}
			}
			else if(ch == '+') {
				ch = fgetc(fp);
				if(ch == '=') {
					ch = fgetc(fp);
				}
				else if(ch == '+') {
					ch = fgetc(fp);
				}
			}
			else if(ch == '-') {
				ch = fgetc(fp);
				if(ch == '=') {
					ch = fgetc(fp);
				}
				else if(ch == '-') {
					ch = fgetc(fp);
				}
			}
			else if(ch == '*') {
				ch = fgetc(fp);
				if(ch == '=') {
					ch = fgetc(fp);
				}
			}
			else if(ch == '\\') {
				ch = fgetc(fp);
				if(ch == 'n') {
					ch = fgetc(fp);
				}
			}
			else {
				printf("\ntest%d: Undefined Symbol!\n", i); 
				flag = 1;
				break;
			}
		}
        if(flag == 0) printf("\ntest%d: Lexical Legal\n", i);
        else continue;
        fclose(fp);
        FILE *fa = fopen(txt1, "r");
		char input[MAX_LEN] = "";
		fgets(input, MAX_LEN, fa);
        printf("Input scentence: %s\n", input); // input为输入串
        int len = strlen(input);
        input[len] = '#';
		fclose(fa);
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
            //printQuad(); // 打印四元式
            rs0[0] = '\0';
            rs1[0] = '\0';
            assembly(); // 生成汇编代码
        }
	}
    return 0;
}