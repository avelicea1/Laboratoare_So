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

typedef struct {
    int value;
    sem_t current;
    sem_t next;
} TH_STRUCT;
void *thread_func(void *p){
    TH_STRUCT *s = (TH_STRUCT*)p;
    while(1){
        sem_wait(&s->current);
        printf("%d ",s->value);
        fflush(stdout);
        usleep((rand()%5+1));
        sem_post(&s->next);
    }
    return NULL;
}
int main(){
    pthread_t tids[NR_THREADS];
    TH_STRUCT params[NR_THREADS];
    
    srand(time(NULL));
    for(int i=0;i<NR_THREADS;i++){
        params[i].value = i+1;
        sem_init(&params[i].current,0,1);
        sem_init(&params[i].next,0,1);
        pthread_create(&tids[i],NULL,thread_func,&params[i]);
    }
    //wait for the threads to finish
    for(int i=0; i<NR_THREADS; i++) {
        pthread_join(tids[i], NULL);
    }
    //destroy the semaphore
    for(int i=0;i<NR_THREADS;i++){
        sem_destroy(&params[i].current);
        sem_destroy(&params[i].next);
    }

}