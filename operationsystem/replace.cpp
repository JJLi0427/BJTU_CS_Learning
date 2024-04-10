#include <iostream>
#include <thread>
#include <time.h>
using namespace std;

const int MAXLEN = 1024; // 最大页面数
const int epoch = 100; // 测试次数
int lossnum; // 缺页次数统计
int now; // 当前访问的页面
int replace; // 页面替换指针
int lossflag; // 是否缺页
int full; // 已使用的页框数
int rate[5][epoch];
int times[5][epoch];

struct PAGE {
    int  pages[MAXLEN];
    int  usenum; // 分配的最大页框数
    int  visitlen; // 访问序列长度
} pinfo;
struct MEM {
    int time; // 访问记录
    int r; // 访问位
    int rw; // 修改位
    int pages; // 页号
} minfo;
MEM pagelist[MAXLEN]; // 分配页框

void pageinit() { // 初始化页面数据
    pinfo.usenum = 3;
    pinfo.visitlen = 256;
    for (int i = 0; i < MAXLEN; i++)
        pinfo.pages[i] = -1;
}

void visitlist(int epoch) { // 随机生成访问序列
    int v = 16, w = 64, s = 128; // v为每个页面访问次数，w为每个页面访问的范围，s为页面访问的起始位置
    pageinit();
    srand(epoch); // 随机种子
    int t= rand() % 11; // 生成t
    for(int i = 0, j =0; i < 10; i++) {
        for(j = i * v; j < (i + 1) * v; j++) { // 生成v个[s, s+w]的随机数
            if(j > pinfo.visitlen) // 生成数量不能超序列长度
                break;
            pinfo.pages[j]= (s + (rand() % w)) % MAXLEN; // 随机数存储到访问序列中
        }
        if(rand() % 11 < t) // 如果r < t，则为p生成一个新值
            s = rand() % MAXLEN;
        else
            s = (s + 1) % MAXLEN;
    }
}

bool randBool() { // 读写随机数生成函数
    if(rand() % 11 > 7) return true;
    else return false;
}

bool inram(int page) { // 查找是否在内存
    for(int i = 0; i < pinfo.usenum; i++) {
        pagelist[i].time++;  // 访问记录++
    }
    for(int i = 0; i < pinfo.usenum; i++) {
        if(pagelist[i].pages == page) {
            lossflag = 0; // 不缺页置为0
            pagelist[i].time = 0; // 访问记录置0
            if(randBool()) {
                pagelist[i].r = 1;
                pagelist[i].rw = 1;
            }
            else
                pagelist[i].r = 1;
            return true;
        }
    }
    lossflag = 1; // 缺页置为1
    return false;
}

void OPT() {// 最佳淘汰算法
    replace = 0, lossnum = 0, full = 0, lossflag = 0;
    for(int i = 0; i < pinfo.usenum; i++) // 刷新页框
        pagelist[i].pages = -1;
    for(now = 0; now < pinfo.visitlen; now++) {
        if(full < pinfo.usenum) {
            if(!inram(pinfo.pages[now])) { // 不在内存则装入页面
                pagelist[replace].pages = pinfo.pages[now];
                replace = (replace + 1) % pinfo.usenum;
                full++, lossnum++; 
            }
        }
        else {
            if(!inram(pinfo.pages[now])) { // 不在内存则需置换
                int min, max = 0 ; // min为最近访问，max为最远访问
                for(int m = 0; m < pinfo.usenum ; m++) {
                    min = MAXLEN;
                    for(int n = now; n < pinfo.visitlen; n++) {
                        if (pinfo.pages[n] == pagelist[m].pages) {
                            min = n;
                            break;
                        }
                    }
                    if(max < min) {
                        max = min;
                        replace = m;
                    }
                }
                pagelist[replace].pages = pinfo.pages[now];
                replace = (replace + 1) % pinfo.usenum;
                lossnum++;
            }
        }
        std::this_thread::sleep_for(10ms);
    }
}

void FIFO(void) { // 先进先出淘汰算法
    replace = 0, lossnum = 0, full = 0, lossflag = 0;
    for(int i = 0; i < pinfo.usenum; i++)
        pagelist[i].pages = -1;
    for(now = 0; now < pinfo.visitlen; now++) {
        if(full < pinfo.usenum) { 
            if(!inram(pinfo.pages[now])) {
                pagelist[replace].pages = pinfo.pages[now];
                replace = (replace + 1) % pinfo.usenum;
                full++, lossnum++;
            }
        }
        else {
            if(!inram(pinfo.pages[now])) {
                pagelist[replace].pages = pinfo.pages[now];
                replace = (replace + 1) % pinfo.usenum;
                lossnum++;
            }
        }
        std::this_thread::sleep_for(10ms);
    }
}

void LRU(void) { // 最近最久未使用淘汰算法
    replace = 0, lossnum = 0, full = 0, lossflag = 0;
    for(int i = 0; i < pinfo.usenum; i++) {
        pagelist[i].pages = -1;
        pagelist[i].time = 0;
    } // 刷新页框
    for(now = 0; now < pinfo.visitlen; now++) {
        if(full < pinfo.usenum) {
            if(!inram(pinfo.pages[now])) {
                pagelist[replace].pages = pinfo.pages[now];
                replace = (replace + 1) % pinfo.usenum;
                full++, lossnum++;
            }
        }
        else {
            if(!inram(pinfo.pages[now])) {
                int max = 0; // 最久的访问记录
                for(int i = 1; i < pinfo.usenum; i++) {
                    if(pagelist[i].time > pagelist[max].time) {
                        max = i;
                    }
                }
                replace = max;
                pagelist[replace].pages = pinfo.pages[now];
                pagelist[replace].time = 0;
                lossnum++;
            }
        }
        std::this_thread::sleep_for(10ms);
    }
}

int replace0(int num) { // 简单Clock置换
    for(int i = 0; i < pinfo.usenum; i++) {
        if(pagelist[(i + num) % pinfo.usenum].r == 0 ) // 找到第一个访问位为0的页面
            return (i + num) % pinfo.usenum;
        pagelist[(i + num) % pinfo.usenum].r = 0; // 未找到则将所有访问位置0
    }
    for(int i = 0; i < pinfo.usenum; i++) {
        if(pagelist[(i + num) % pinfo.usenum].r == 0 )
            return (i + num) % pinfo.usenum;
    }
    return 0;
}

int replace1(int num) { // 改进的clock置换
    for(int i = 0; i < pinfo.usenum; i++) {
        if (pagelist[(i + num) % pinfo.usenum].r == 0 && pagelist[(i + num) % pinfo.usenum].rw == 0) // 先找访问位和修改位都为0的页面
            return (i + num) % pinfo.usenum;
    }
    for(int i = 0; i < pinfo.usenum; i++) {
        if (pagelist[(i + num) % pinfo.usenum].r == 0 && pagelist[(i + num) % pinfo.usenum].rw == 1) // 再找访问位为0，修改位为1的页面
            return (i + num) % pinfo.usenum;
        pagelist[(i + num) % pinfo.usenum].r = 0; // 未找到则将所有访问位置0
    }
    for(int i = 0; i < pinfo.usenum; i++) {
        if (pagelist[(i + num) % pinfo.usenum].r == 0 && pagelist[(i + num) % pinfo.usenum].rw == 0) // 再找访问位和修改位都为0的页面
            return (i + num) % pinfo.usenum;
    }
    for(int i = 0; i < pinfo.usenum; i++) {
        if (pagelist[(i + num) % pinfo.usenum].r == 0 && pagelist[(i + num) % pinfo.usenum].rw == 1) // 最后找访问位为0，修改位为1的页面
            return (i + num) % pinfo.usenum;
    }
    return 0;
}

void CLOCK(int choose) {
    int num = 0;
    replace = 0, lossnum = 0, full = 0, lossflag = 0;
    for(int i = 0; i < pinfo.usenum; i++) {
        pagelist[i].pages = -1;
        pagelist[i].rw = 0;
        pagelist[i].r = 0;
        pagelist[i].time = 0;
    }
    for(now = 0; now < pinfo.visitlen; now++) {
        if(full < pinfo.usenum) {
            if(!inram(pinfo.pages[now])) {
                pagelist[replace].pages = pinfo.pages[now];
                replace = (replace + 1) % pinfo.usenum;
                pagelist[replace].r = 1;
                full++, lossnum++;
            }
        }
        else {
            if(!inram(pinfo.pages[now])) {
                    if(choose == 1)
                        replace = replace1(num++); // choose=1,改进clock算法
                    else if(choose == 0) // choose=0,简单clock算法
                        replace = replace0(num++); 
                    pagelist[replace].pages = pinfo.pages[now];
                    pagelist[replace].r = 1;
                    lossnum++;
                }
        }
        std::this_thread::sleep_for(10ms);
    }
}

void calculate(int i, int j, clock_t start) { // 计算缺页率和运行时间
    rate[i][j] = (double)(lossnum) * 100 / now;
    times[i][j] = (double)(clock() - start) / 1000;
}

int main() {
    clock_t start;
    for(int i = 0; i < epoch; i++) {
        visitlist(i);
        start = clock();
        OPT();
        calculate(0, i, start);
        start = clock();
        FIFO();
        calculate(1, i, start);
        start = clock();
        LRU();
        calculate(2, i, start);
        start = clock();
        CLOCK(0);
        calculate(3, i, start);
        start = clock();
        CLOCK(1);
        calculate(4, i, start);
    }
    for(int i = 0; i < 5; i++) {
        if(i == 0) printf("OPT:    ");
        if(i == 1) printf("FIFO:   ");
        if(i == 2) printf("LRU:    ");
        if(i == 3) printf("CLOCK:  ");
        if(i == 4) printf("CLOCK+: ");
        int avrate = 0, avtime = 0;
        for(int j = 0; j < epoch; j++) {
            avrate += rate[i][j];
            avtime += times[i][j];
        }
        printf("Average replace rate = %.3lf%%  ", (double)(avrate) / epoch);
        printf("Average spend time: %.3lfs\n", (double)(avtime) / epoch);
    }
    return 0;
}

