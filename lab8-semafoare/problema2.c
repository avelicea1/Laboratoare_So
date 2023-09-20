#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

int nrThreads = 0;
int maxThreads;
sem_t limita;
sem_t oprire;
void *limited_area(void *unused)
{
    sem_wait(&limita);
    sem_wait(&oprire);
    nrThreads++;
    sem_post(&oprire);
    usleep(100);
    printf("The number of threads in the limited area is: %d \n", nrThreads);
    sem_wait(&oprire);
    nrThreads--;
    sem_post(&oprire);
    sem_post(&limita);
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 1;
    }
    int maxThreads;
    maxThreads = atoi(argv[1]);
    pthread_t tid[16];

    int i;
    if (sem_init(&limita, 0, maxThreads) != 0)
    {
        perror("Could not init the semaphore");
        return -1;
    }
    if (sem_init(&oprire, 0, 1) != 0)
    {
        perror("Could not init the semaphore");
        return -1;
    }
    for (i = 0; i < 16; i++)
    {
        pthread_create(&tid[i], NULL, limited_area, NULL);
    }
    for (i = 0; i < 16; i++)
    {
        pthread_join(tid[i], NULL);
    }
    sem_destroy(&oprire);
    sem_destroy(&limita);
}
