#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

void *func (void * arg){
    return NULL;
}
int main(){
    pthread_t thread;
    int numara=0;
    while(pthread_create(&thread,NULL,func,NULL)==0){
        numara ++;
        
    }
    printf("%d",numara);
}