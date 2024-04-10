#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

sem_t space, full, mutex; //space是缓冲区的信号量，full是已使用的缓冲区，mutex访问缓冲区信号量
typedef struct ThreadData {
    int id;
    int setup;
    int exe;
} tdata; //线程的数据结构

void* producer(void* p) {
    int id = ((tdata*)p)->id;
    int setup = ((tdata*)p)->setup;
    int exe = ((tdata*)p)->exe;

    sleep(setup);
    printf("thread %d: wait to produce\n", id);

    sem_wait(&space); //等待缓冲区有空位
    sem_wait(&mutex); //访问缓冲区

    printf("thread %d: start producing\n", id);
    sleep(exe);
    printf("thread %d: end producing\n", id);

    sem_post(&mutex);
    sem_post(&full);

    pthread_exit(0);
    return NULL;
}

void* consumer(void* p) {
    int id = ((tdata*)p)->id;
    int setup = ((tdata*)p)->setup;
    int exe = ((tdata*)p)->exe;

    sleep(setup);
    printf("thread %d: wait to consume\n", id);

    sem_wait(&full);
    sem_wait(&mutex);

    printf("thread %d: start consuming\n", id);
    sleep(exe);
    printf("thread %d: end consuming\n", id);

    sem_post(&mutex);
    sem_post(&space);

    pthread_exit(0);
    return NULL;
}

int main() {
    int num = 6; //设置生产者和消费者的数量
    pthread_t tid[num]; //线程号初始化
    pthread_attr_t attr;
    pthread_attr_init(&attr); //线程属性初始化  
    sem_init(&mutex, 0, 1);
    sem_init(&space, 0, 3);
    sem_init(&full, 0, 0);

    char worklist[num] = "ccpcpp";
    int setuplist[num] = {2, 3, 4, 3, 7, 5};
    int exelist[num] = {1, 3, 2, 8, 6, 1}; //设置不同的生产者和消费者的等待时间和执行时间
    for(int id = 0; id < num; id++) {
        tdata* d = new tdata;
        d->id = id;
        d->setup = setuplist[id];
        d->exe = exelist[id];

        if(worklist[id] == 'c') {
            printf("create thread %d: consumer\n", id);
            pthread_create(&tid[id], &attr, consumer, d); //创建消费者线程
        }
        else if(worklist[id] == 'p') {
            printf("create thread %d: producer\n", id);
            pthread_create(&tid[id], &attr, producer, d); //创建生产者线程
        }
    }
    for(int i = 0; i < num; i++) {
        pthread_join(tid[i], NULL);
    }

    sem_destroy(&mutex); //销毁信号量
    sem_destroy(&space);
    sem_destroy(&full);
    return 0;
}
