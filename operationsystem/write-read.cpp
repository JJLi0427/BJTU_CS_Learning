#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

sem_t rw, rmutex, wmutex, use; //rw访问文件信号量，rmutex/wmutex是实现rcount/wcount互斥访问信号量，use是写者优先的信号量
int rcount = 0, wcount = 0; //分别记录读者和写者数量
typedef struct ThreadData {
    int id;
    int setup;
    int exe;
} tdata; //线程的数据结构

void* reader(void* p) {
    int id = ((tdata*)p)->id;
    int setup = ((tdata*)p)->setup;
    int exe = ((tdata*)p)->exe;

    sleep(setup);    
    printf("thread %d: wait to read\n", id);

    sem_wait(&use); //等待写者优先信号量
    sem_wait(&rmutex); //实现rcount互斥访问
	if(rcount == 0) 
        sem_wait(&rw); //rcount为0时操作使用文件信号
    rcount++;
    sem_post(&rmutex);
    sem_post(&use);
	
    printf("thread %d: start reading\n", id);
    sleep(exe);
    printf("thread %d: end reading\n", id);
	
	sem_wait(&rmutex);
    rcount--;
    if(rcount == 0) 
        sem_post(&rw);
    sem_post(&rmutex);
    
    pthread_exit(0);
    return NULL;
}

void* writer(void* p) {
    int id = ((tdata*)p)->id;
    int setup = ((tdata*)p)->setup;
    int exe = ((tdata*)p)->exe;

    sleep(setup);
    printf("thread %d: wait to write\n", id);
    
    sem_wait(&wmutex); //实现wcount互斥访问
    if(wcount == 0)
        sem_wait(&use); //写者优先
    wcount++;
    sem_post(&wmutex);
    sem_wait(&rw); //实现读者和写者对文件互斥访问

    printf("thread %d: start writing\n", id);
    sleep(exe);
    printf("thread %d: end writing\n", id);
    
    sem_post(&rw);
    sem_wait(&wmutex);
    wcount--;
    if(wcount == 0)
        sem_post(&use);
    sem_post(&wmutex);
    
    pthread_exit(0);
    return NULL;
}

int main() {
    int num = 5; //设置读者和写者的人数
    pthread_t tid[num]; //线程号初始化
    pthread_attr_t attr;
    pthread_attr_init(&attr); //线程属性初始化
    sem_init(&rmutex, 0, 1);
    sem_init(&wmutex, 0, 1);
    sem_init(&rw, 0, 1);
    sem_init(&use, 0, 1);

    char worklist[num] = "rwrrw";
    int setuplist[num] = {2, 3, 1, 5, 1};
    int exelist[num] = {1, 5, 2, 3, 1}; //设置不同的读者和写者的等待时间和执行时间
    for(int id = 0; id < num; id++) {
        tdata* d = new tdata;
        d->id = id;
        d->setup = setuplist[id];
        d->exe = exelist[id];

        if(worklist[id] == 'r') {
            printf("create thread %d: reader\n", id);
            pthread_create(&tid[id], &attr, reader, d); //创建读者线程
        }
        else if(worklist[id] == 'w') {
            printf("create thread %d: writer\n", id);
            pthread_create(&tid[id], &attr, writer, d); //创建写者线程
        }
        
    }
    for(int i = 0; i < num; i++) {
        pthread_join(tid[i], NULL); //等待所有线程结束
    }
    
    sem_destroy(&rmutex); //销毁信号量
    sem_destroy(&wmutex);
    sem_destroy(&rw);
    sem_destroy(&use);
    return 0;
}