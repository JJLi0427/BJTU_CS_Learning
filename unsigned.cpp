#include <iostream>
#include <string>
using namespace std;

// 状态转换表0: . 1: e 2: + or - 3: 0-9 4: other
int state[7][5] = {
    {3, -1, -1, 1, -1},
    {2, 4, -1, 1, -1},
    {-1, 4, -1, 2, -1},
    {-1, -1, -1, 2, -1},
    {-1, -1, 5, 6, -1},
    {-1, -1, -1, 6, -1},
    {-1, -1, -1, 6, -1}
};
int allend[3] = {1, 2, 6}; //可以结束的状态

int judge(char change) {
    if (change == '.') return 0;
    else if (change == 'E' || change == 'e') return 1;
    else if (change == '+' || change == '-') return 2;
    else if (change >= '0' && change <= '9') return 3;
    else return 4;
} //跳转函数

int isend(int now) {
    for (int i = 0; i < 3; i++) {
        if (now == allend[i]) return 1;
    }
    return 0;
} // 判断是否为结束状态

int main() {
    string s;
    while (cin >> s) {
        int now = 0;
        for (int i = 0; i < s.length(); i++) {
            cout << now << "->";
            int index = judge(s[i]);
            now = state[now][index];
            cout << now << endl;
            if (now == -1) break;
        }
        if (isend(now) == 1) cout << "yes\n";
        else cout << "no\n";
    }
    return 0;
}
