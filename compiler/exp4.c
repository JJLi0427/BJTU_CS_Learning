#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_LEN 1000
char str[MAX_LEN];
char stack[MAX_LEN];
int top = 0;

                    //+, -, *, /, (, ), i, #
int table[8][8] =  {{ 1, 1,-1,-1,-1, 1,-1, 1}, // +
                    { 1, 1,-1,-1,-1, 1,-1, 1}, // -
                    { 1, 1, 1, 1,-1, 1,-1, 1}, // *
                    { 1, 1, 1, 1,-1, 1,-1, 1}, // /
                    {-1,-1,-1,-1,-1, 0,-1,-2}, // (
                    { 1, 1, 1, 1,-2, 1,-2, 1}, // )
                    { 1, 1, 1, 1,-2, 1,-2, 1}, // i
                    {-1,-1,-1,-1,-1,-2,-1, 0}};// #

int getindex(char ch) {
    switch(ch) {
        case '+': return 0;
        case '-': return 1;
        case '*': return 2;
        case '/': return 3;
        case '(': return 4;
        case ')': return 5;
        case 'i': return 6;
        case '#': return 7;
        default: return -1;
    }
}

int OPG(char *str, char *stack) {
    int i = 0;
    while(i < strlen(str)) {
        if(top < 0) return 0;
        int x = getindex(stack[top]);
        int y = getindex(str[i]);
        if(x == -1 || y == -1) return 0;
        if(table[x][y] == -1) {
            stack[++top] = str[i];
            printf("%c -> ", str[i++]);
        }
        else if(table[x][y] == 1) {
            top--;
        }
        else if(table[x][y] == 0) {
            top--;
            printf("%c -> ", str[i++]);
        }
        else if(table[x][y] == -2) {
            return 0;
        }
    }
    if(top+1 == 0) return 1;
    else return 0;
}

int main() {
	for(int m = 5; m <= 8; m++) {
		printf("test%d:\n", m);
		char txt[] = "./lexical/analyze";
		char num[6];
		sprintf(num, "%d.txt", m);
		strcat(txt, num);
		FILE *fp = fopen(txt, "r");
		char buf[MAX_LEN] = "";
		char input[MAX_LEN] = "";
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
        printf("str: %s\n", str);
		fclose(fp);
		stack[0] = '#', top = 0;
		if(OPG(str, stack)) {
			printf("end\n");
			printf("Gramma legal: %s\n", str);
		}
		else {
			printf("error\n");
			printf("Gramma illegal\n");
		}
	}
    return 0;
}