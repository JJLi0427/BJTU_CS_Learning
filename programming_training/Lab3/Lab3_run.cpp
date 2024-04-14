#include "Lab3_run.h"

void run(int n, char *argv[]) {
    CONF conf;
    FILE *fp = fopen("conf.ini", "r");
    fscanf(fp, "%s", conf.filesavepath);
    fscanf(fp, "%s", conf.filename);
    fscanf(fp, "%d", &conf.maxvalue1);
    fscanf(fp, "%d", &conf.minvalue1);
    fscanf(fp, "%d", &conf.maxvalue2);
    fscanf(fp, "%d", &conf.minvalue2);
    fscanf(fp, "%d", &conf.recordcount1);
    fscanf(fp, "%d", &conf.recordcount2);
    fclose(fp);
    //把ini文件数据读入结构体

    char *name = NULL;//指向生成文件路径
    int amt;//生成数据的条数

    if (n == 1) amt = getnum(conf.recordcount1, conf.recordcount2);//当命令行参数只有一个时

    if (n == 2) {
        if(strspn(argv[1], "0123456789") == strlen(argv[1])){//第一种情况是第二个参数是数字
            amt = atoi(argv[1]);
            if(amt >= conf.recordcount1 || amt <= conf.recordcount2){
                printf("输入的数据条数不合法\n");
                amt = getnum(conf.recordcount1, conf.recordcount2);
            }
        }
        else{//另外一种情况是没有输入数据，输入了文件名或者是地址
            name = argv[1];
            amt = getnum(conf.recordcount1, conf.recordcount2);
        }
    }//当命令行参数有两个

    if (n == 3) {
        amt = atoi(argv[1]);//获取生成数据条数
        if(amt >= conf.recordcount1 || amt <= conf.recordcount2){
            printf("输入的数据条数不合法\n");
            amt = getnum(conf.recordcount1, conf.recordcount2);
        }
        name = argv[2];//获取生成文件名和位置
    }//当传入三个命令行参数

    if(n > 3){
        printf("输入参数过多，程序结束\n");
        exit;
    }
    //输入参数过多程序报错结束

    if(name == NULL){
        printf("请输入生成文件路径或文件名\n");
        char na[MAX_STR_LEN];
        scanf("%s", na);
        name = na;
    }
    //name为空时获取用户输入的地址

    int flag = 0;//flag用来判断输入的合法性
    int i = 0;
    int check = 0;//check表示是否使用默认存储位置

    while(flag == 0){

        int n = strlen(name);

        for(i = 0; i < n; i++) if((name[i]==':' && i != 1) ||name[i]=='*'||name[i]=='\"'||name[i]=='<'||name[i]=='>'||name[i]=='|') break;
        //检查非法字符
        if(name[n-1]!='t'||name[n-2]!='x'||name[n-3]!='t'||name[n-4]!='.') i = 0;
        //检查是不是txt结尾
        if(i >= n){
            flag = 1;
            break;
        }
        printf("输入不合法\n");
        printf("请输入生成文件路径或文件名,输入r可以使用默认路径和文件名\n");
        char na1[MAX_STR_LEN];
        scanf("%s", na1);
        if(na1[0] == 'r' && strlen(na1) == 1){//判断字符来确认用户是否选择了随机
            check = 1;
            break;
        }
        name = na1;     
    }
    //循环直到获取到合法输入

    if(check == 1) conf.number = amt;//使用默认位置
    else{
        conf.number = amt;//写入数据条数
        for(i = strlen(name)-4; i > 0; i--) if(name[i] == '/') break;//判断用户输入是文件名还是路径
        if(i == 0){
            for(int j = 0; j < strlen(name); j++) conf.filename[j] = name[j];
            conf.filename[strlen(name)] = '\0';
            exit;
        }
        //只是输入文件名时
        else{
            for(int j = 0; j < i; j++) conf.filesavepath[j] = name[j];
            conf.filesavepath[i] = '\0';
            for(int j = i+1; j < strlen(name); j++) conf.filename[j-i-1]=name[j];
            conf.filename[strlen(name)-i-1] = '\0';
        }
    }

    char *where = conf.filesavepath;
    strcat(where, "/");
    strcat(where, conf.filename);
    //where表示完整路径

    int mode;
    printf("李佳骏的实验3程序:\n1.生成数据记录文件(使用二维数组存储)\n2.生成数据记录文件(使用结构体数组存储)\n请输入您要执行的序号:\n");
    //运行菜单界面

    scanf("%d", &mode);
    if(mode == 1) OP1(conf, where);//用二维数组
    else if(mode == 2) OP2(conf, where);//使用结构体
    else printf("输入错误,程序结束\n");
}