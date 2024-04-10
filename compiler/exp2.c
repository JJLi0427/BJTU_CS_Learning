#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_LEN 1000
char str[MAX_LEN];
int i, j, flag;
void S();
void E();
void E1();
void T();
void T1(); 
void F();
void A(); 
void M(); 
void V();

void S() {
    if(flag == 0) {
        printf("S->");
        if(str[i] == 'i') {
            V();
			if(flag == 0 && str[i] == '=') {
				i++;
				E();
			}
			else {
				flag = 1;
				printf("error\n"); 
			}
        }	
		else {
            flag = 1;
            printf("error\n"); 
        }
    }
}

void E() {
    if(flag == 0) {
        printf("E->");
        if(str[i] == '(' || str[i] == 'i') {
            T();
            if(flag == 0) {
				if(str[i] == '+' || str[i] == '-')
					E1();
				else if(str[i] == ')' || str[i] == '#')
                    return;
				else {
					flag = 1;
					printf("error\n"); 
				}
			}
        }
        else {
			flag = 1;
			printf("error\n"); 
		}
    }
}

void E1() {
    if(flag == 0) {
		printf("E'->");
        if(str[i] == '+' || str[i] == '-') {
            A();
            if(flag == 0) {
				if(str[i] == '(' || str[i] == 'i') {
					T();
					if(flag == 0){
						if(str[i] == '+' || str[i] == '-')
							E1();
						else if(str[i] == ')' || str[i] == '#')
							return;
						else {
							flag = 1;
							printf("error\n"); 
						}
					}
				}
				else{
					flag = 1;
					printf("error\n"); 
				}
			}
        }
        else if(str[i] == ')' || str[i] == '#')
			return;
        else {
			flag = 1;
			printf("error\n"); 
		}
    }
}

void T() {
    if(flag == 0) {
		printf("T->");
        if(str[i] == '(' || str[i] == 'i') {
            F();
            if(flag == 0) {
				if(str[i] == '*' || str[i] == '/')
					T1();
				else if(str[i] == '+' || str[i] == '-' || str[i] == ')' || str[i] == '#')
					return;
				else {
					flag = 1;
					printf("error\n"); 
				}
			}
        }
        else {
			flag = 1;
			printf("error\n"); 
		}
    }
}

void T1() {
	if(flag == 0) {
		printf("T'->");
		if(str[i] == '*' || str[i] == '/') {
			M();
			if(flag == 0) {
				F();
				if(flag == 0)
					T1();
			}
		}
		else if(str[i] == '+' || str[i] == '-' || str[i] == ')' || str[i] == '#')
			return;			
		else {
			flag = 1;
			printf("error\n"); 
		}
	}
}

void F() {
	if(flag == 0){
		printf("F->");
		if(str[i] == '(') {
			i++;
			if(str[i] == '(' || str[i] == 'i') {
				E();
				if(flag == 0) {
					if(str[i] == ')')
						i++;
					else {
						flag = 1;
						printf("error\n"); 
					}
				}
			}
			else {
				flag = 1;
				printf("error\n");
			}
		}
		else if(str[i] == 'i') {
			i++;
		}
		else {
			flag = 1;
			printf("error\n");
		}
	}
}

void A() {
	if(flag == 0) {
		printf("A->");
		if(str[i] == '+' || str[i] == '-')
			i++;
		else {
			flag = 1;
			printf("error\n");
		}
	}
}

void M() {
	if(flag == 0) {
		printf("M->");
		if(str[i] == '*' || str[i] == '/')
			i++;
		else {
			flag=1;
			printf("error\n");
		}
	}
}

void V() {
	if(flag == 0){
		printf("V->");
		if(str[i] == 'i')
			i++;
		else{
			flag = 1;
			printf("error\n");
		}
	}
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
		i = 0, j = 0;

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
		str[i] = '#', input[j] = '#';
		fclose(fp);
		flag = 0, i = 0;
		S();
		if(str[i] == '#' && flag == 0) {
			printf("end\n");
			printf("Gramma legal: %s\n", str);
		}
		else
			printf("Gramma illegal\n");
	}
    return 0;
}