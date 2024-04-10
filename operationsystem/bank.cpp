#include<iostream>
using namespace std;

const int p=5; // 设置进程数量
const int r=4; // 设置资源种类
int allocate[p][r] = {{0, 1, 0, 0},
                      {2, 0, 0, 1},
                      {3, 0, 2, 1},
                      {2, 1, 1, 0},
                      {0, 0, 2, 0}}; // 已分配资源矩阵
int needs[p][r] = {{7, 4, 3, 3},
                   {1, 2, 2, 2},
                   {6, 0, 0, 0},
                   {0, 1, 1, 1},
                   {4, 3, 1, 1}}; // 需求资源矩阵
int avail[r] = {3, 3, 2, 2}; // 可利用资源向量

void init(int maximum[p][r], int allocation[p][r], int need[p][r], int available[r], int request[r]) {
    for(int i = 0; i < p; i++) {
        for(int j = 0; j < r; j++) {
            allocation[i][j] = allocate[i][j];
            need[i][j] = needs[i][j];
            maximum[i][j] = need[i][j]+allocation[i][j]; // maximum = allocation + need
        }
    } // 初始化，从矩阵读取数据
    for(int i = 0; i < r; i++) {
        available[i] = avail[i];
    }
}

void output(int maximum[p][r], int allocation[p][r], int need[p][r], int available[r]) {
    cout << "Maximum:           " << "Allocation:        " << "Need:              " << "Available: " << endl;
    for(int i = 0; i < p; i++) {
        cout << "Pid=" << i << ": ";
        for(int j = 0; j < r; j++) {
            cout << maximum[i][j] << ' ';
        }
        cout << "    Pid=" << i << ": ";
        for(int j = 0; j < r; j++) {
            cout << allocation[i][j] << ' ';
        }
        cout << "    Pid=" << i << ": ";
        for(int j = 0; j < r; j++) {
            cout << need[i][j] << ' ';
        }
        if(i == 0) {
            cout << "    ";
            for(int k = 0; k < r; k++){
                cout << available[k] << ' ';
            }
        }
        cout << endl;
    }
}

bool compare(int need[], int forwork[]) {
    // 比较函数，需要<=可用
    for(int i = 0; i < r; i++) {
        if(need[i] > forwork[i]) {
            return false;
        }
    }
    return true;
}

bool safe(int allocation[p][r], int need[p][r], int available[r]) {
    // 安全性检查
    int finish[p]; // finish数组，用来记录进程是可以否执行完成
    int forwork[r]; // 可用资源数组
    int list[p]; // 安全队列
    int count = 0;
    for(int i = 0; i < r; i++)
        forwork[i] = available[i]; // 初始时等于available

    for(int x = 0; x < p; x++) {
        for(int i = 0; i < p; i++) {
            if(finish[i] == 1)
                continue; // 跳过已经判断过的进程
            else {
                if(compare(need[i], forwork)) {
                    for(int j = 0; j < r; j++) {
                        forwork[j] += allocation[i][j];
                    }
                    finish[i] = 1;
                    list[count++] = i; // 进程进入安全列中
                    break;
                }
            }
        }
    }

    if(count != p) {
        cout << "Will not be safe!" << endl;
        return false;
    }
    cout << "Safe! working list: ";
    for(int i = 0; i < p; i++) {
        cout << list[i];
        if(i != p-1)
            cout << "->";
    }
    cout << endl;
    return true;
}

int bank(int maximum[p][r], int allocation[p][r], int need[p][r], int available[r], int request[r]) {
    cout << "Request Process id:" << endl;
    int num = 0;
    cin >> num;
    cout << "Request vector:" << endl;
    for(int i = 0; i < r; i++) {
        cin >> request[i];
    }
    if(!compare(request ,need[num])) {
        // 请求不能大于需求
        cout<<"Error: request > need"<<endl;
        return 0;
    }
    else {
        if(!compare(request, available)) {
            // 请求不能大于可用
            cout << "Error: request > available" << endl;
            return 0;
        }
        else {
            for(int j = 0; j < r;j ++) {
                available[j] -= request[j];
                allocation[num][j] += request[j];
                need[num][j] -= request[j];
            }
            if(safe(allocation, need, available)) {
                cout <<"Allocate success"<< endl;
            }
            else {
                cout << "Allocate fail" << endl;
                for(int j = 0; j < r; j++) {
                    need[num][j] += request[j];
                    allocation[num][j] -= request[j];
                    available[j] += request[j];
                } // 分配失败返回原来状态
            }
        }
    }
    output(maximum, allocation, need, available);
    return 0;
}

int main() {
    int maximum[p][r], allocation[p][r], need[p][r];
    int available[r], request[r];
    init(maximum, allocation, need, available, request);
    output(maximum, allocation, need, available);
    safe(allocation, need, available);
    char flag = 'c';
    while(flag == 'c' || flag == 'C') {
        bank(maximum, allocation, need, available, request);
        cout << "\nInput q to left / Input c to continue." << endl;
        cin >> flag;
        if(flag == 'q' || flag == 'Q')
            break;
    }
    return 0;
}