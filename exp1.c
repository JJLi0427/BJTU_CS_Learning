#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(){
	for(int i = 1; i <= 4; i++){
		char txt1[] = "./test/test";
		char num[6];
		sprintf(num, "%d.txt", i);
		strcat(txt1, num);
		char txt2[] = "./lexical/analyze";
		sprintf(num, "%d.txt", i);
		strcat(txt2, num);
		FILE *fp = fopen(txt1, "r");
		FILE *fw = fopen(txt2, "wt+");
		int flag = 0;

		char ch = fgetc(fp);	
		while(!feof(fp)) {
			char str[32];
			int j = 0;
			if(ch == ' ' || ch == '\t') {
				ch = fgetc(fp);
				continue;
			}
			else if(ch == '\n'){
				fprintf(fw, "\n");
				ch = fgetc(fp);
				continue;
			}
			else if(english(ch)) {
				str[j++] = ch;
				do{
					ch = fgetc(fp);
					str[j++] = ch;
				}while(english(ch)||number(ch));
				str[j-1] = '\0';
				int id = reserved(str);
				fprintf(fw, "(%d, %s) ", id, str);
			}
			else if(number(ch)) {
				str[j++] = ch;
				do{
					ch = fgetc(fp);
					str[j++] = ch;
				}while(number(ch));
				str[j-1] = '\0';
				fprintf(fw, "(2, %s) ", str);
			}
			else if(symbol(ch) != 0) {
				fprintf(fw, "(%d, %c) ", symbol(ch), ch);
				ch = fgetc(fp);
			}
			else if(ch == '>') {
				ch = fgetc(fp);
				if(ch == '=') {
					fprintf(fw, "(29, >=) ");
					ch = fgetc(fp);
				}
				else if(ch == '>') {
					fprintf(fw, "(30, >>) ");
					ch = fgetc(fp);
				}
				else fprintf(fw, "(28, >) ");
			}
			else if(ch == '<') {
				ch = fgetc(fp);
				if(ch == '=') {
					fprintf(fw, "(32, <=) ");
					ch = fgetc(fp);
				}
				else if(ch == '<') {
					fprintf(fw, "(33, <<) ");
					ch = fgetc(fp);
				}
				else fprintf(fw, "(31, <) ");
			}
			else if(ch == '!') {
				ch = fgetc(fp);
				if(ch == '=') {
					fprintf(fw, "(35, !=) ");
					ch = fgetc(fp);
				}
				else fprintf(fw, "(34, !) ");
			}
			else if(ch == '=') {
				ch = fgetc(fp);
				if(ch == '=') {
					fprintf(fw, "(37, ==) ");
					ch = fgetc(fp);
				}
				else fprintf(fw, "(36, =) ");
			}
			else if(ch == '/') {
				ch = fgetc(fp);
				if(ch == '*') {
					fprintf(fw, "(Start annotate, /*) ");
					do {
						ch = fgetc(fp);
						if(ch == '*') {
							ch = fgetc(fp);
							if(ch == '/') {
								fprintf(fw, "(End annotate, */) ");
								ch = fgetc(fp);
								break;
							}
						}
					}while(1);
				}
				else if(ch == '/') {
					fprintf(fw, "(annotate, //) ");
					do {
						ch = fgetc(fp);
					}while(ch != '\n');
					fprintf(fw, "\n");
					ch = fgetc(fp);
				}
				else if(ch == '=') {
					fprintf(fw, "(39, /=) ");
					ch = fgetc(fp);
				}
				else fprintf(fw, "(38, /) ");
			}
			else if(ch == '&') {
				ch = fgetc(fp);
				if(ch == '&') {
					fprintf(fw, "(41, &&) ");
					ch = fgetc(fp);
				}
				else fprintf(fw, "(40, &) ");
			}
			else if(ch == '|') {
				ch = fgetc(fp);
				if(ch == '|') {
					fprintf(fw, "(43, ||) ");
					ch = fgetc(fp);
				}
				else fprintf(fw, "(42, |) ");
			}
			else if(ch == '+') {
				ch = fgetc(fp);
				if(ch == '=') {
					fprintf(fw, "(46, +=) ");
					ch = fgetc(fp);
				}
				else if(ch == '+') {
					fprintf(fw, "(45 ++) ");
					ch = fgetc(fp);
				}
				else fprintf(fw, "(44, +) ");
			}
			else if(ch == '-') {
				ch = fgetc(fp);
				if(ch == '=') {
					fprintf(fw, "(49, -=) ");
					ch = fgetc(fp);
				}
				else if(ch == '-') {
					fprintf(fw, "(48, --) ");
					ch = fgetc(fp);
				}
				else fprintf(fw, "(47, -) ");
			}
			else if(ch == '*') {
				ch = fgetc(fp);
				if(ch == '=') {
					fprintf(fw, "(51, *=) ");
					ch = fgetc(fp);
				}
				else fprintf(fw, "(50, *) ");
			}
			else if(ch == '\\') {
				ch = fgetc(fp);
				if(ch == 'n') {
					ch = fgetc(fp);
				}
			}
			else {
				fprintf(fw, "Undefined symbol!");
				printf("test%d: Undefined symbol!\n", i); 
				flag = 1;
				break;
			}
		}
		fclose(fp);
		fclose(fw);
		if(flag) continue;
		printf("test%d: Finish analyzing.\n", i);
	}
} 