#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include "kk.h"
#include <fstream>
#include <Windows.h>
using namespace std;

struct tongji {
	char num[10];
	char tongjixinag[100];
};
struct jinitaimei {
	int danci;//单词
	int shuzi;//数字
	int kongbai;//空白
	int zimu;//字母
	int qita;//其他字符
}sum;
struct adc {
	char we[1024];
}nm[100];

int main() {
	int cn;
	int ui = 0;
	char cmy[1024];
	ofstream q;
	fstream gc;

	while (1) {
		char ty[1024] = "D:\\2022_code\\c-language-programming-\\ruoyu_1_10\\x64\\Debug\\ruoyu_1_10.exe ";
		char xy[1024] = "D:\\2022_code\\c-language-programming-\\ruoyu_2_10\\x64\\Debug\\ruoyu_2_10.exe D:\\2022_code\\c-language-programming-\\ruoyu_1_10\\ruoyu_1_10\\ruoyu_1.txt";
		char xxw[1024];
		char m2[1024];
		char m3[1024];
		char m4[1024];
		char rtyu[1024];
		char _op[1024];
		struct dirent* de;
		DIR* dr;
		ofstream nc;
		char cnm[1024];
		cout << "XXX组的实验5程序：" << endl;
		cout << "  1.对单个英文文档进行统计" << endl;
		cout << "  2.对批量英文文档进行统计" << endl;
		cout << "  0.退出" << endl;
		cout << "请输入您要执行的程序序号" << endl;
		cin >> cn;
		FILE* q;
		switch (cn) {
		case 1:
			char dan[1024];
			cout << "请输入要统计英文文档的路径" << endl;
			cin >> dan;
			//cout << dan << endl;
			strcat(ty, dan);
			strcat(ty, " 2");
			system(ty);
			strcat(xy, " 1");
			system(xy);

			break;
		case 2:
			cout << "请输入待统计文件夹的绝对路径" << endl;

			cin >> xxw;
			//cout << xxw;
			dr = opendir(xxw);
			if (dr == NULL)
			{
				cout << "Could not open current directory" << endl;
				return 0;
			}
			while ((de = readdir(dr)) != NULL)
			{
				//cout << de->d_name << endl;
				strcpy(nm[ui].we, de->d_name);
				//cout << nm[ui].we << endl;
				ui++;
			}
			//文件名应该从2开始
		//	cout << ui << endl;
			q = fopen("D:\\2022_code\\c-verbal-learning\\ruoyu_10_7\\ruoyu_10_7\\testn.html", "w");
			if (!q)
			{
				cout << "文件打开失败" << endl;
				return 0;
			}
			fprintf(q, "<!DOCTYPE html>\n");
			fprintf(q, "<html lang=\"en\" xmlns=\"http://www.w3.org/1999/xhtml\">\n");
			fprintf(q, "<body>\n");
			for (int i = 2; i < ui; i++)
			{
				strcpy(m4, xxw);
				strcat(m4, "\\");
				strcat(m4, nm[i].we);//m4是完整的文件名称

				ifstream gry;
				//cout << "请输入英文文件的路径：" << endl;
				gry.open(m4, ios::in);
				if (!gry.is_open())
				{
					cout << "文件打开失败" << endl;
					return 0;
				}
				char c;
				int flag = 0;
				//sum.qita--;
				while ((c = gry.get()) != EOF) {
					if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') sum.zimu++;
					else if (c >= '0' && c <= '9') sum.shuzi++;
					else if (c == ' ') sum.kongbai++;
					else sum.qita++;
					if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
						flag = 1;
					}
					if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) && flag == 1) {
						flag = 0;
						sum.danci++;
					}
					if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) && flag == 0) {
						continue;
					}
				}
				if (sum.danci == 0 && flag == 1) {
					sum.danci = 1;
				}
				gry.close();
				ofstream ly;
				sprintf(cnm, "D:\\2022_code\\c-language-programming-\\ruoyu_1_10\\ruoyu_1_10\\test_%d.txt", i - 1);
				ly.open(cnm, ios::out);
				ly << "单词数目\t数字个数\t空白个数\t字母个数\t其它字符" << endl;
				ly << sum.danci << "\t\t" << sum.shuzi << "\t\t" << sum.kongbai << "\t\t" << sum.zimu << "\t\t" << sum.qita << endl;
				ly.close();

				gc.open(cnm, ios::in);
				if (!gc.is_open()) {
					cout << "实验san读取失败" << endl;
					return 0;
				}
				struct tongji we[5];
				char laji[1024];
				for (int i = 0; i < 4; i++) {
					gc.getline(we[i].tongjixinag, sizeof(we[i].tongjixinag), '\t');
					//cout << we[i].tongjixinag<<'\t';
				}
				gc.getline(we[4].tongjixinag, sizeof(we[4].tongjixinag), '\n');
				//cout << we[4].tongjixinag << endl;

				for (int i = 0; i < 4; i++) {
					gc.getline(we[i].num, sizeof(we[i].num), '\t');
					gc.getline(laji, sizeof(laji), '\t');
				}
				gc.getline(we[4].num, sizeof(we[4].num), '\n');
				//cout << we[4].num << endl;
				gc.close();
				sprintf(rtyu, "D:\\2022_code\\c-language-programming-\\ruoyu_2_10\\ruoyu_2_10\\test_2_%d.html", i - 1);
				nc.open(rtyu, ios::out);
				if (!nc.is_open()) {
					cout << "文件san打开失败" << endl;
					return 0;
				}
				nc << "<!DOCTYPE html>" << endl;
				nc << "<html lang=\"en\" xmlns=\"http://www.w3.org/1999/xhtml\">" << endl;
				nc << "<body>" << endl;
				//nc << "   <p>";
				nc << "<table border=\"1\">\n       <caption>统计结果</caption>\n        <tr>\n";
				for (int i = 0; i < 5; i++) {
					nc << "<th>" << we[i].tongjixinag <<"</th>" << endl;
				}
				nc << " </tr> \n<tr>\n";
				for (int i = 0; i < 5; i++) {
					nc << "<td>" << we[i].num <<"</td>" << endl;
				}
				nc << "    </tr>\n    </table>\n</body>" << endl;
				nc << "</html>" << endl;
				nc.close();
				fprintf(q, "<p>第%d个文档统计结果</p>", i - 1);
				fprintf(q, "<a href=%s target=\"_blank\">访问链接</a>", rtyu);
				fprintf(q, "<br>\n");
			}

			fprintf(q, "</body>\n");
			fprintf(q, "</html>\n");
			closedir(dr);
			system("D:\\2022_code\\c-verbal-learning\\theend\\endfile_html\\HTMLPage1.html");
			break;
		case 0:
			break;
		default:
			system("cls");
			cout << "输入错误，请重新输入！！！" << endl;
			cout << "**********************" << endl;
			break;
		}
		if (cn == 0) break;
	}
	return 0;
}