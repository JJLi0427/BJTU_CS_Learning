#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_LEN 1000
char str[MAX_LEN];
char stack[MAX_LEN];
int top = 0;

int LL1(char *str, char *stack) {
    int i = 0;
    while(str[i] != '#') {
		if(top < 0) return 0;
		if(stack[top] == str[i]) {
			printf("%c -> ", stack[top]);
			top--;
			i++;
		}
        else if(stack[top] == 'S') {
			if(str[i] == 'i') {
				stack[top++] = 'E';
				stack[top++] = '=';
				stack[top] = 'V';
			}
			else return 0;
		}
		else if(stack[top] == 'E') {
			if(str[i] == 'i') {
				stack[top++] = 'e';
				stack[top] = 'T';
			}
			else if(str[i] == '(') {
				stack[top++] = 'e';
				stack[top] = 'T';
			}
			else return 0;
		}
		else if(stack[top] == 'e') {
			if(str[i] == '+') {
				stack[top++] = 'e';
				stack[top++] = 'T';
				stack[top] = 'A';
			}
			else if(str[i] == '-') {
				stack[top++] = 'e';
				stack[top++] = 'T';
				stack[top] = 'A';
			}
			else if(str[i] == ')' || str[i] == '#') {
				printf("%c -> ", str[i]);
				top--;
			}
			else return 0;
		}
		else if(stack[top] == 'T') {
			if(str[i] == 'i') {
				stack[top++] = 't';
				stack[top] = 'F';
			}
			else if(str[i] == '(') {
				stack[top++] = 't';
				stack[top] = 'F';
			}
			else return 0;
		}
		else if(stack[top] == 't') {
			if(str[i] == '*') {
				stack[top++] = 't';
				stack[top++] = 'F';
				stack[top] = 'M';
			}
			else if(str[i] == '/') {
				stack[top++] = 't';
				stack[top++] = 'F';
				stack[top] = 'M';
			}
			else if(str[i] == '+' || str[i] == '-' || str[i] == ')' || str[i] == '#') {
				printf("%c -> ", str[i]);
				top--;
			}
			else return 0;
		}
		else if(stack[top] == 'F') {
			if(str[i] == 'i') 
				stack[top] = 'i';
			else if(str[i] == '(') {
				stack[top++] = ')';
				stack[top++] = 'E';
				stack[top] = '(';
			}
			else return 0;
		}
		else if(stack[top] == 'A') {
			if(str[i] == '+')
				stack[top] = '+';
			else if(str[i] == '-')
				stack[top] = '-';
			else return 0;
		}
		else if(stack[top] == 'M') {
			if(str[i] == '*')
				stack[top] = '*';
			else if(str[i] == '/')
				stack[top] = '/';
			else return 0;
		}
		else if(stack[top] == 'V') {
			if(str[i] == 'i') 
				stack[top] = 'i';
			else return 0;
		}
		else return 0;
    }
	return 1;
}

int main() {
	for(int m = 1; m <= 4; m++) {
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
		fclose(fp);
		stack[0] = 'S', top = 0;
		int flag = LL1(str, stack);
		if(flag == 1) {
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