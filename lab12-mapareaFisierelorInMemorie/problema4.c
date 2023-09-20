#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv){
    int shmFd;
    volatile int*sharedVector = NULL;
    if(argc !=3){
        fprintf(stderr, "Usage: %s <interval>\n", argv[0]);
        return 1;
    }
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    shmFd = shm_open("/myshm",O_RDWR,0);
    if(shmFd < 0){
        perror("Could not aquire shm");
        return 1;
    }
    sharedVector = (volatile int*) mmap(0,100*sizeof(int),PROT_WRITE|PROT_READ,MAP_SHARED,shmFd,0);
    if(sharedVector == (void*)-1){
        perror("Could not map shared memory");
        return 1;
    }
    int lungime = sharedVector[0];
    for(int i=a;i<=b;i++){
        if(i%2 == 1){
            sharedVector[++lungime]=i;
            sharedVector[0]++;
        }
    }
    return 0;
}