#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define NR_THREADS 7
int fd1=-1;
typedef struct{
    int id;
    pthread_mutex_t *lock;
}TH_STRUCT;

void open_once(int *fd){
    if(*fd == -1){
        *fd = open("file.txt",O_RDONLY);
    }
}
void *thread_function(void*args){
    TH_STRUCT *s = (TH_STRUCT *)args;
    usleep(1000*s->id);
    open_once(&fd1);
    pthread_mutex_lock(s->lock);
    usleep(1000*s->id);
    char c;
    printf("%d",fd1);
    read(fd1,&c,1);
    printf("%c",c);
    pthread_mutex_unlock(s->lock);
    return NULL;
}
int main(){
    int i;
    TH_STRUCT params[NR_THREADS];
    pthread_t tids[NR_THREADS];
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    for (i = 0; i < NR_THREADS; i++)
    {
        params[i].id = i;
        params[i].lock = &lock;
        pthread_create(&tids[i],NULL,thread_function,&params[i]);
    }
    return 0;
}