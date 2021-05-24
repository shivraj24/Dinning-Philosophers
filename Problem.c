#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include<unistd.h>
sem_t mutex;
sem_t chopsticks[5];

char status[6]= {'-','-','-','-','-'};


void printstatus()
{
    printf("\n");

    for(int i=0;i<5;i++)
    {
        printf("  %c   ",status[i]);
    }
}

void* Philosophers(void *arg)
{
    long int num =  (long int) arg;
    status[num] = 'H';

    printstatus();

    sem_wait(&mutex);
    sem_wait(&chopsticks[num]);
    sleep(1);
    sem_wait(&chopsticks[(num+1)%5]);

    status[num] = 'E';
    printstatus();
    
    sleep(1);

    sem_post(&chopsticks[(num+1)%5]);
    sem_post(&chopsticks[num]);
    

    sem_post(&mutex);
    status[num] = 'T';
    printstatus();
    
    pthread_exit(NULL);


}

int main()
{

    pthread_t philosophers[5];

    long int i, j;

    for (i = 0; i < 5; i++)
    {
        sem_init(&chopsticks[i], 0, 1);
        sem_init(&mutex,0,1);
    }

    for(i=0;i<5;i++)
    {
        printf("P[%ld]  ",i);
    }
    for (i = 0; i < 5; i++)
    {
        pthread_create(&philosophers[i], NULL, Philosophers,(void*) i);
    }

    for (j = 0; j < 5; j++)
    {
        pthread_join(philosophers[j], NULL);
    }
    return 0;
}