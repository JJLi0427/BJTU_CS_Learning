#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

const int num = 5; //设置哲学家的人数
sem_t chopstick[num], eatman; //创建筷子信号量和就餐人数上限信号量
typedef struct ThreadData {
    int id;
    int think;
    int eat;
} tdata; //线程的数据结构

void* philosopher(void* p) {
    int id = ((tdata*)p)->id;
    int think = ((tdata*)p)->think;
    int eat = ((tdata*)p)->eat;

    sleep(think);
    printf("philosopher %d: is thinking\n", id);

    sem_wait(&eatman);
    sem_wait(&chopstick[id]); //拿起左边的筷子
    sem_wait(&chopstick[(id + 1) % num]); //拿起右边的筷子
    sem_post(&eatman);

    printf("philosopher %d: start eating\n", id);
    sleep(eat); 
    printf("philosopher %d: end eating\n", id);

    sem_post(&chopstick[id]); //放下左边的筷子
    sem_post(&chopstick[(id + 1) % 5]); //放下右边的筷子
    pthread_exit(0);
    return NULL;
}

int main() {
    pthread_t tid[num]; //线程号初始化
    pthread_attr_t attr;
    pthread_attr_init(&attr); //线程属性初始化
    sem_init(&eatman, 0, num-1);
    for(int i = 0; i < num; i++) {
        sem_init(&chopstick[i], 0, 1); //初始化所有的筷子，信号量都为1
    }

    int thinklist[num] = {2, 6, 5, 3, 1};
    int eatlist[num] = {8, 3, 4, 5, 2}; //设置哲学家的思考时间和吃饭时间
    for(int id = 0; id < num; id++) {
        tdata* d = new tdata;
        d->id = id;
        d->think = thinklist[id];
        d->eat = eatlist[id];
        printf("create philosopher %d\n", id);
        pthread_create(&tid[id], &attr, philosopher, d); //创建哲学家线程
    }
    for(int i = 0; i < num; i++) {
        pthread_join(tid[i], NULL); //等待所有哲学家线程结束
    }

    sem_destroy(&eatman); //销毁信号量
    for(int i = 0; i < num; i++) {
        sem_destroy(&chopstick[i]); 
    }
    return 0;
}