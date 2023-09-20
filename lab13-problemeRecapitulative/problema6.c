#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int *vectorFinal;
int lungime = 0;
typedef struct{
    int start;
    int end;
    sem_t *log;
    int increment;
    int id;
}TH_STRUCT;
void *threadFcn(void*args){
    TH_STRUCT *s = (TH_STRUCT*)args;
    // for(int i=s->start;i <= s->end;i++){
    //     //printf("start = %d end = %d\n",s->start,s->end);
    //     int sum = 0;
    //     for(int d=1;d<=i/2;d++){
    //         if(i%d == 0){
    //             sum+=d;
    //         }
    //     }
    //     if(sum == i){
    //         sem_wait(s->log);
    //         vectorFinal[lungime] = i;
    //         lungime++;
    //         sem_post(s->log);
    //     }
    // }
    for(int i=s->start;i<=s->end;i+=s->increment){
        //printf("start = %d end = %d\n",s->start,s->end);
        int sum = 0;
        for(int d=1;d<=i/2;d++){
            if(i%d == 0){
                sum+=d;
            }
        }
        if(sum == i){
            sem_wait(s->log);
            vectorFinal[lungime] = i;
            lungime++;
            sem_post(s->log);
        }
    }
    return NULL;
}
int main(int argc, char**argv){
    if(argc!=3){
        perror("Not enought elements!");
        return 1;
    }
    int NR_THREADS= atoi(argv[1]);
    int N = atoi(argv[2]);
    vectorFinal = (int*)malloc(N*sizeof(int));
    // sscanf(argv[1],"%d",NR_THREADS);
    // sscanf(argv[2],"%d",N);
    sem_t log;
    if(sem_init(&log,0,1)!=0){
        perror("Could not create semaphore!");
        return 1;
    }
    printf("nr threads = %d, N = %d\n",NR_THREADS,N);
    pthread_t tids[NR_THREADS];
    TH_STRUCT params[NR_THREADS];
    for(int i=0;i<NR_THREADS;i++){
        // if(i==0){
        //     params[i].start = 1;
        // }else{
        //     params[i].start = params[i-1].end+1;
        // }
        // params[i].end = params[i].start + N/NR_THREADS-1;
        // if( i< N%NR_THREADS){
        //     params[i].end ++;
        // }
        params[i].start=i+1;
        params[i].end=N;
        params[i].log = &log;
        params[i].id = i;
        params[i].increment = NR_THREADS;
        //printf("start = %d end = %d\n",params[i].start,params[i].end);
        pthread_create(&tids[i],NULL,threadFcn,&params[i]);
    }
    for(int i=0;i<NR_THREADS;i++){
        pthread_join(tids[i],NULL);
    }
    for(int i=0;i<lungime;i++){
        printf("%d ",vectorFinal[i]);
    }
    sem_close(&log);
    return 0;
}