#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

void *threadFcn (void * param){
    int threadNr = *(int *)param;
    for(;;){
        sleep(rand()%5 +1);
        printf("thread nr = %d\n",threadNr);
    }
}
int main(){
    pthread_t tid[9];
    int params[9];
    int nrcreate = 0;
    int nrsterse = 0;
    srand(time(NULL));
    for(int i=0;i<9;i++){
        params[i]=i+1;
        pthread_create(&tid[i],NULL,threadFcn, &params[i]);
        nrcreate++;
    }
    int id= 0;
    for(;;){
        scanf("%d",&id);
        if(id >=1 && id <=9){
            pthread_cancel(tid[id - 1]);
            nrsterse++;
        }
        if(nrcreate == nrsterse){
            return 0;
        }
    }
    for(int i=0;i<9;i++){
        pthread_join(tid[i],NULL);
    }
    return 0;
}