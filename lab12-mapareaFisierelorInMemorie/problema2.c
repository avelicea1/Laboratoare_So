#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int shmFd;
    volatile int* sharedInt = 0;

    shmFd = shm_open("/l12_myshm", O_CREAT | O_RDWR, 0600);
    if(shmFd < 0) {
        perror("Could not aquire shm");
        return 1;
    }
    ftruncate(shmFd, sizeof(int));
    sharedInt = (volatile int*)mmap(0, sizeof(int), PROT_READ | PROT_WRITE, 
        MAP_SHARED, shmFd, 0);
    if(sharedInt == (void*) -1) {
        perror("Could not map the shared memory");
        return 1;
    }

    *sharedInt = 1;
    while(*sharedInt !=50) {
        //if(*sharedInt ==1) sleep(1);
        printf("found sharedInt: %d\n", *sharedInt);
        *sharedInt = *sharedInt + 1;
        //printf("sharedInt : %d\n",*sharedInt);
        sleep(1);
    }
    munmap((void*)sharedInt, sizeof(int));
    sharedInt = NULL;
    close(shmFd);
    shm_unlink("/l12_myshm");
    return 0;
}