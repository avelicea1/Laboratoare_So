#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

typedef struct{
    int start;
    int end;
    int increment;
}ThreadArgs;

void *threadFunc (void *args){
    ThreadArgs *s = (ThreadArgs*)args;
    int nr_1=0;
    for(int i=s->start;i<s->end;i+=s->increment){
        //printf("%d %d\n",s->start,i);
        int copie_nr = i;
        while(copie_nr !=0){
            if(copie_nr%10 == 1){
                nr_1 ++;
            }
            copie_nr = copie_nr/10;
        }
    }
    return(void*)(long) nr_1;
}

#define NrThread 2
int main(){
    
    pthread_t t_id[NrThread];
    void *result; 
    int sum=0;
    int n;
    printf("n este = ");
    scanf("%d",&n);
    ThreadArgs th_args[n];
    for(int i=0;i<NrThread ;i++){
        th_args[i].start= i;
        th_args[i].end = n;
        th_args[i].increment = NrThread;
        pthread_create(&t_id[i],NULL,threadFunc,&th_args[i]);
    }
    for(int i=0;i<NrThread;i++){
        pthread_join(t_id[i],&result);
        sum+=(int)(long)result;
    }
    printf("nr de 1 %d",sum);
}