#include "Lab3_fun.h"

int getnum(int max, int min) {
    printf("请输入数据条数n:(%d<=n<=%d)\n", min, max);
    char c[16];
    int amt;
    scanf("%d", &amt);
    while(amt < min || amt > max) {
        printf("输入的数据条数不合法\n");
        printf("请输入数据条数n:(%d<=n<=%d),输入r可以随机指定数据条数\n", min, max);
        scanf("%s", c);
        if(strlen(c) == 1 && c[0] == 'r'){//用字符来判断是否用户选择了随机
            srand(time(0));
            amt = rand() % (max-min+1) + min;
            return amt;
        }
        else amt = atoi(c);
    }
    //判断输入是否在限制范围内
    return amt;
}//获取数据条数

void opentxt(char *name) {
    char cmd[100];
    sprintf(cmd, "start %s", name);
    system(cmd);
}//把写好的txt文件打开展示

int random(int max, int min){
    return rand() % (max-min+1)+min;
}//生成指定范围内随机数

void OP1(CONF conf, char *where){
    int **arr;//创建二维指针
    arr = new int *[conf.number];
    for (int i = 0; i < conf.number; i++) {
        arr[i] = new int[3];
        if (NULL == arr[i]) {
            printf("数组空间创建失败\n");
            exit(0);
        }
    }//动态申请空间
    srand(time(0));//加入随机数种子
    for (int i = 0; i < conf.number; i++) {
        arr[i][0] = random(conf.maxvalue1, conf.minvalue1);
        arr[i][1] = random(conf.maxvalue1, conf.minvalue1);
        arr[i][2] = random(conf.maxvalue2, conf.minvalue2);
    }//随机数存储到二维数组
    FILE *fp = fopen(where, "w+");
    if (NULL == fp) {
        printf("打开文件失败\n");
        exit(0);
    }
    fprintf(fp,"%d\n", conf.number);//打开文件并且写入 
    for (int i = 0; i < conf.number; i++) {
        fprintf(fp, "%d,%d,%d\n", arr[i][0], arr[i][1], arr[i][2]);//写入数据到txt
        printf("%d,%d,%d\n", arr[i][0], arr[i][1], arr[i][2]);//输出数据到屏幕
    }
    fclose(fp);
    opentxt(where);
}
//模式1运行，二维数组的方式

void OP2(CONF conf, char *where){
    DATAITEM *data;
    data = new DATAITEM[conf.number];
    srand(time(0));//加入随机数种子
    for (int i = 0; i < conf.number; i++) {
        data[i].item1 = random(conf.maxvalue1, conf.minvalue1);
        data[i].item2 = random(conf.maxvalue1, conf.minvalue1);
        data[i].item3 = random(conf.maxvalue2, conf.minvalue2);
    }//把随机数存入结构体数组
    FILE *fp = fopen(where, "w+");
    if (NULL == fp) {
        printf("打开文件失败\n");
        exit(0);
    }
    fprintf(fp,"%d\n", conf.number);//打开文件并且写入 
    for (int i = 0; i < conf.number; i++) {
        fprintf(fp, "%d,%d,%d\n", data[i].item1, data[i].item2, data[i].item3);//写入数据到txt
        printf("%d,%d,%d\n", data[i].item1, data[i].item2, data[i].item3);//输出数据到屏幕
    }
    fclose(fp);
    opentxt(where);
}//模式2运行，结构体的方式
