#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5 

sem_t chopsticks[N]; 


void *philosopher(void *arg);
void eat(int philosopher_number);

int main() {
    pthread_t tid[N];
    int i;

    
    for (i = 0; i < N; i++) {
        sem_init(&chopsticks[i], 0, 1);
    }

    
    for (i = 0; i < N; i++) {
        pthread_create(&tid[i], NULL, philosopher, (void *)(intptr_t)i);
    }

    
    for (i = 0; i < N; i++) {
        pthread_join(tid[i], NULL);
    }

    
    for (i = 0; i < N; i++) {
        sem_destroy(&chopsticks[i]);
    }

    return 0;
}

void *philosopher(void *arg) {
    int philosopher_number = (intptr_t)arg;
    int left = philosopher_number;
    int right = (philosopher_number + 1) % N;

    while (1) {
        
        printf("Philosopher %d is thinking.\n", philosopher_number);

        
        sem_wait(&chopsticks[left]);
        sem_wait(&chopsticks[right]);

        
        eat(philosopher_number);

        
        sem_post(&chopsticks[right]);
        sem_post(&chopsticks[left]);

        
    }
}

void eat(int philosopher_number) {
    printf("Philosopher %d is eating.\n", philosopher_number);
    usleep(rand() % 500000 + 500000); 
}
