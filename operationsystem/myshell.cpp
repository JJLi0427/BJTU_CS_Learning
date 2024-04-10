#include <iostream>  
#include <string>  
#include <vector>  
#include <sys/types.h>  
#include <sys/wait.h>  
using namespace std;  

int main() {  
    vector<string> cmds={"ls", "cd", "env", "ps", "date", "echo", "help", "exit"};  
    string fp;  
    while(1) {  
        string now = "ljj@shell:" + string(getcwd(nullptr, 0)) + "> ";  
        printf("%s", now.c_str());  
        string cmd;  
        cin >> cmd;  
        string p;  
        bool valid = false;  
        int index = -1;  
        for (int i = 0; i < cmds.size(); i++) {  
            if (cmd == cmds[i]) {  
                valid = true;  
                index = i;  
            }  
        }  
        if (!valid) {  
            printf("No command! Input -help for more information\n");  
            continue;  
        }  
        else {  
            if(index < 5) {  
                // 使用父子进程使得程序可以同时执行多个命令并防止阻塞  
                pid_t pid;  
                pid = fork();  
                if (pid < 0) {  
                    fprintf(stderr, "Fork Failed");  
                    return 1;  
                }  
                else if (pid == 0) {  
                    if(index == 0) { //ls  
                        execlp("/bin/ls", "ls", NULL);  
                    }  
                    else if(index == 1) { //cd  
                        cin >> p;  
                        chdir(p.c_str());  
                    }  
                    else if(index == 2) { //env  
                        execlp("env", "", NULL);  
                    }  
                    else if(index == 3) { //ps  
                        execlp("ps", "", NULL);  
                    }  
                    else if(index == 4) { //time  
                        execlp("date", "", NULL);  
                    }  
                }  
                else {  
                    waitpid(pid, NULL, 0);  
                }  
            }  
            else {  
                if(index == 5) { //echo  
                    cin >> p;  
                    cout << p << endl;  
                }  
                else if(index == 6) { //help  
                    printf("Shell Commands List:\n\  
                    ls -查看当前目录内容\n\  
                    cd [] -前往指定目录\n\  
                    env -查看环境变量\n\  
                    ps -查看当前进程\n\  
                    date -查看当前的时间\n\  
                    echo [] -显示指定的内容后换行\n\  
                    help -帮助\n\  
                    exit -退出\n");  
                }  
                else return 0; // exit  
            }  
        }  
    }  
    return 0;  
}  