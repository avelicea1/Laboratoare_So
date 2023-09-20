#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void){
    int shmFd;
    volatile int *sharedVector = NULL;

    shmFd = shm_open("/myshm", O_CREAT|O_RDWR,0600);
    if(shmFd < 0){
        perror("could not aquire shm");
        return 1;
    }
    ftruncate(shmFd,100*sizeof(int));
    sharedVector = (int*)mmap(NULL,100*sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,shmFd,0);
    if(sharedVector == (void*)-1){
        perror("could not map the file");
        return 1;
    }
    sharedVector[0] = 5;
    for(int i=1;i<=5;i++){
        sharedVector[i] = i;
        //printf("%d",sharedVector[i]);
    }
    sleep(5);
    for(int i=1;i<=sharedVector[0];i++){
        printf("%d ",sharedVector[i]);
    }
    munmap((void*)sharedVector,100*sizeof(int));
    sharedVector = NULL;
    close(shmFd);
    shm_unlink("/myshm");
    return 0;
}