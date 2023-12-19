#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_LEN 1000

struct stack {
    char s[MAX_LEN];
    int i[MAX_LEN];
    int top;
};

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

void print(char *str, struct stack *stk, int now) { // 打印分析状态
    for(int i = 0; i <= stk->top; i++) {
        printf("%c:%2d   ", stk->s[i], stk->i[i]);
    }
    for(int i = 0; i <= 50 - stk->top*7; i++) {
        printf(" ");
    }
    for(int i = now; i < strlen(str); i++) {
        printf("%c", str[i]);
    }
    // printf("\n");
    // for(int i = 0; i <= stk->top; i++) {
    //     printf("%3d", stk->i[i]);
    // }
    printf("\n");
}

void getfour(char *str) {
    int tmp = 1;
    while(1) {
        int flag = 0, close = 0, ptr = 0, start = 0, end = strlen(str);
	for(int i = 0; i < strlen(str); i++) { // 括号优先级高，先找括号
	    if(str[i] == '(') start = i + 1;
	    else if(str[i] == ')') {
		end = i;
		break;
	    }
	}    
	for(int i = start; i < end; i++) { 
	    if(str[k] == '+' || str[k] == '-' || str[k] == '*' || str[k] == '/') {
		close = 1;
		break;
	    }
	}
	if(close == 0) {  // 如果括号内没有运算符，消除括号，再重新找括号
	    int t = start - 1;
	    for(int i = start; i < end; i++) {
		str[t++] = str[i];
	    }
	    for(int i = end + 1; i < strlen(str); i++) {
		str[t++] = str[i];
	    }
	    str[t] = '\0';
	    start = 0, end = strlen(str);
	    for(int i = 0; i < strlen(str); i++) {
    	        if(str[i] == '(') start = i + 1;
		else if(str[i] == ')') {
		    end = i;
		    break;
		}
	    }    
	}
        for(int i = start; i < end; i++) {
            if(str[i] == '*' || str[i] == '/') { // 优先乘除
                flag = 1;
                ptr = i;
                break;
            }
            else if(str[i] == '+' || str[i] == '-') { // 然后加减
                if(flag == 0) {
                    flag = 1;
                    ptr = i;
                }
            }
            else if(str[i] == '=') { 
                ptr = i;
            }
        }
        char left[MAX_LEN] = "";
        printf("(%c, ", str[ptr]);
        int j = ptr - 1, p = 0, k = ptr + 1;
        if(flag == 0) { // 当前为赋值运算
            while(k < end && str[k] != '+' && str[k] != '-' && str[k] != '*' && str[k] != '/' && str[k] != '=') {
                printf("%c", str[k++]);
            }
            printf(", , ");
            while(j >= start && str[j] != '+' && str[j] != '-' && str[j] != '*' && str[j] != '/' && str[j] != '=') {
                left[p++] = str[j];
                j--;
            }
            for(int q = p - 1; q >= 0; q--) {
                printf("%c", left[q]);
            }
            printf(")\n");
            break;
        }
        while(j >= start && str[j] != '+' && str[j] != '-' && str[j] != '*' && str[j] != '/' && str[j] != '=') {
            left[p++] = str[j];
            j--;
        }
        for(int q = p - 1; q >= 0; q--) { 
            printf("%c", left[q]); // 输出第一个操作数
        }
        printf(", ");
        while(k < end && str[k] != '+' && str[k] != '-' && str[k] != '*' && str[k] != '/' && str[k] != '=') {
            printf("%c", str[k++]); // 输出第二个操作数
        }
        printf(", ");
        char num[3] = "";
        sprintf(num, "T%d", tmp);
        printf("%s)\n", num); // 输出目的操作数
        tmp++;
        for(int q = 0; q < strlen(num); q++) {
            str[++j] = num[q];
        }
        for(int q = k; q < strlen(str); q++) {
            str[++j] = str[q];
        }
        str[j+1] = '\0'; // 更新串
    }
}

int SLR(char *str, struct stack *stk) { // SLR1分析函数
    int i = 0;
    int next;
    printf("stack:                                                    str:\n");
    while(i < strlen(str)) {
        if(stk->top < 0) return 0; // 分析栈不可能为空
        int y = getindex(str[i]);
        if(y == -1 || table[stk->i[stk->top]][y] == 0) { // 表中不存在的状态，分析报错
	    return 0;
	}
        if(table[stk->i[stk->top]][y] > 0) { // 移进操作
            next = table[stk->i[stk->top]][y];
            stk->top++;
            stk->s[stk->top] = str[i];
            stk->i[stk->top] = next;
            i++;
            print(str, stk, i);
        }
        else if(table[stk->i[stk->top]][y] < 0) { // 归约操作
            int tmp = -table[stk->i[stk->top]][y];
            if(tmp == 4 || tmp == 7 || tmp == 9 || tmp == 10) {
                stk->top--;
            }
            else {
                stk->top -= 3;
            }
            if(tmp == 1) { 
                y = getindex('S');
                next = table[stk->i[stk->top]][y];
                stk->top++;
                stk->s[stk->top] = 'S';
                stk->i[stk->top] = next; // 归约修改栈顶
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
            print(str, stk, i);
        }
    }
    return 0;
}

int main() {
	for(int m = 9; m <= 10; m++) {
		printf("\ntest%d:   ", m);
		char txt[] = "./lexical/analyze";
		char num[8];
		sprintf(num, "%d.txt", m);
		strcat(txt, num);
		FILE *fp = fopen(txt, "r");
		char buf[MAX_LEN] = "";
		char input[MAX_LEN] = "";
        char str[MAX_LEN] = "";
		fgets(buf, MAX_LEN, fp);
		int i = 0, j = 0;
		for(int k = 0; k < strlen(buf); k++) {
			if(buf[k] == '1' && buf[k+1] == ',') {
				str[i++] = 'i';
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
					str[i++] = buf[k];
					input[j++] = buf[k++];
				}
			}
		}
		printf("Input scentence: %s\n", input);
		str[i] = '#';
		fclose(fp);
        struct stack *stk;
        stk = (struct stack *)malloc(sizeof(struct stack));
		stk->s[0] = '#';
        stk->i[0] = 0;
        stk->top = 0;
		if(SLR(str, stk)) {
			printf("Gramma legal: %s\n", str);
            getfour(input);
		}
		else { 
			printf("Gramma illegal\n");
		}
	}
    return 0;
}
