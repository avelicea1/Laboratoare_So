#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int *v;
int dimensiune;
int *nrDiv;
int i;

typedef struct{
    int id;
    pthread_mutex_t *lock;
}TH_STRUCT;

void* thread_function(void *unused){
    TH_STRUCT *s = (TH_STRUCT*)unused;
    usleep(1000*s->id);
    while(i<dimensiune){
        int cnt = 0;
        int n=v[i];
        for (int i = 1; i <= n; i++) {
            if (n % i == 0) 
                cnt++;
        }
        nrDiv[i]=cnt;
        pthread_mutex_lock(s->lock);
        usleep(1000*s->id);
        i++;
        pthread_mutex_unlock(s->lock);
    }
    return NULL;
}

int main(int argc,char **argv){
    int nrThreads=0;
    dimensiune = 10;
    v = (int*)malloc(dimensiune*sizeof(int));
    nrDiv = (int*)malloc(dimensiune*sizeof(int));
    for(int i=0;i<dimensiune;i++){
        v[i] = i+1;
    }
    for(int i=0;i<dimensiune;i++){
        nrDiv[i] = 0;
    }
    if(argc<2){
        perror("not enough elements");
        return 1;
    }
    nrThreads = atoi(argv[1]);
    pthread_t tids[nrThreads];
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    TH_STRUCT params[nrThreads];
    for(int i=0;i<nrThreads;i++){
        params[i].id = i;
        params[i].lock = &lock;
        pthread_create(&tids[i],NULL,thread_function,&params[i]);
    }
    for(int i = 0; i<nrThreads; i++){
        pthread_join(tids[i],NULL);
    }
    for(int i=0;i<dimensiune;i++){
        printf("%d ",nrDiv[i]);
    }
    pthread_mutex_destroy(&lock);
    free(v);
    free(nrDiv);
    return 0;
}