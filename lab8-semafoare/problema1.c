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

#define NR_THREADS 4
// valoarea asteptate este M*N = 4000
// valoarea care apare este 1023
// pentru rezolvarea problemei am folosit un semafor ca in laborator in sectiunea 8.2.3.4
long count = 0;
sem_t logSem;
void *thread_function(void *unused)
{
    int i;
    long aux;
    for (i = 0; i < 1000; i++)
    {
        sem_wait(&logSem);
        aux = count;
        aux++;
        usleep(random()%10);
        count = aux;
        sem_post(&logSem);
    }
    return NULL;
}
int main(){
    pthread_t tid[NR_THREADS];
    
    int i;
    if(sem_init(&logSem, 0, 1) != 0) {
        perror("Could not init the semaphore");
        return -1;
    }
    for(i=0;i<NR_THREADS;i++){
        pthread_create(&tid[i],NULL,thread_function,NULL);
    }
    for(i=0;i<NR_THREADS;i++){
        pthread_join(tid[i],NULL);
    }
    sem_destroy(&logSem);
    printf("count = %ld",count);
}