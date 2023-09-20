#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <pthread.h>
#include <string.h>

int vowelCount = 0;

char vowel[11] = {'a','e','i','o','u','A','E','I','O','U'};
typedef struct{
    int id;
    char* cuvant;
    sem_t *log;
}TH_STRUCT;
void * threadFcn(void *args){
    TH_STRUCT *s = (TH_STRUCT*)args;
    //printf("%s\n",s->cuvant);
    for(int i=0;i<strlen(s->cuvant);i++){
        if(strchr(vowel,s->cuvant[i])!=0){
            //printf("%c\n",s->cuvant[i]);
            sem_wait(s->log);
            vowelCount ++;
            sem_post(s->log);
        }
    }
    return NULL;
}
int main(int argc, char **argv){
    sem_t log;
    if(sem_init(&log,0,1)!=0){
        perror("COuld not create semaphore!");
        return 1;
    }
    int nrCuvinte = argc -1;
    pthread_t tid[nrCuvinte];
    TH_STRUCT params[nrCuvinte];
    for(int i=0;i<nrCuvinte;i++){
        params[i].id = i+1;
        params[i].cuvant = argv[i+1];
        params[i].log = &log;
        pthread_create(&tid[i],NULL,threadFcn,&params[i]);
    }
    for(int i=0;i<nrCuvinte;i++){
        pthread_join(tid[i],NULL);
    }
    printf("nr de vocale in total %d \n",vowelCount);
    return 0;
}