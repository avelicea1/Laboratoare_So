#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PERSOANE_LA_MASA 5
typedef struct{
    int value;
}TH_STRUCT;
pthread_mutex_t barrier;
sem_t lock;
pthread_cond_t cond;
sem_t lock;
int persoane_la_masa = 0;
int locuri_libere = 0;

void* thread_function(void*args){
    TH_STRUCT *s = (TH_STRUCT*)args;
    sem_wait(&lock);
    if(persoane_la_masa == PERSOANE_LA_MASA){
        locuri_libere = 0;
    }else if(persoane_la_masa< PERSOANE_LA_MASA && locuri_libere>0){
        persoane_la_masa++; 
        locuri_libere --;
        printf("persoana %d se aseaza la masa",s->value);
        usleep(rand()%1000);
        printf("persoana %d se ridica de la masa",s->value);
    }
    sem_post(&lock);
    return NULL;
}

int main(){
    sem_init(&lock,0,5);
    TH_STRUCT params[15];
    pthread_t tids[15];
    for(int i=0;i<15;i++){
        pthread_create(&tids[i],NULL,thread_function,&params[i]);
    }
    for(int i=0;i<15;i++){
        pthread_join(tids[i],NULL);
    }
    sem_destroy(&lock);
    return 0;
}