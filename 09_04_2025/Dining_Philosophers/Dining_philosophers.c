#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5 

enum { THINKING, HUNGRY, EATING };

int state[N];
sem_t mutex;
sem_t sem[N];

void test(int i) {
    int left = (i + N - 1) % N;
    int right = (i + 1) % N;

    if (state[i] == HUNGRY &&
        state[left] != EATING &&
        state[right] != EATING) {
        state[i] = EATING;
        sem_post(&sem[i]);
    }
}

void take_forks(int i) {
    sem_wait(&mutex);
    state[i] = HUNGRY;
    printf("Philosopher %d is HUNGRY\n", i);
    test(i);
    sem_post(&mutex);
    sem_wait(&sem[i]); 
}

void put_forks(int i) {
    sem_wait(&mutex);
    state[i] = THINKING;
    printf("Philosopher %d is THINKING\n", i);
    test((i + N - 1) % N); 
    test((i + 1) % N); 
    sem_post(&mutex);
}

void* philosopher(void* num) {
    int id = *(int*)num;
    while (1) {
        sleep(rand() % 3 + 1); 
        take_forks(id);
        printf("Philosopher %d is EATING\n", id);
        sleep(rand() % 2 + 1); 
        put_forks(id);
    }
}

int main() {
    pthread_t tid[N];
    int ids[N];

    sem_init(&mutex, 0, 1);
    for (int i = 0; i < N; i++) {
        sem_init(&sem[i], 0, 0);
        state[i] = THINKING;
        ids[i] = i;
    }

    for (int i = 0; i < N; i++) {
        pthread_create(&tid[i], NULL, philosopher, &ids[i]);
    }

    sleep(20);

    for (int i = 0; i < N; i++) {
        pthread_cancel(tid[i]);
        sem_destroy(&sem[i]);
    }
    sem_destroy(&mutex);

    return 0;
}
