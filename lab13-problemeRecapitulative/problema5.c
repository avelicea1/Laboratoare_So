#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(int argc,char **argv){
    if(argc !=3){
        perror("nu sunt transmise suficiente elemente");
        return 1;
    }
    int fd1 = -1, fd2 = -1;
    fd1 = open(argv[1],O_RDWR);
    if(fd1 == -1){
        perror("COuld not open first file!");
        return 1;
    }
    fd2 = open(argv[2],O_RDWR);
    if(fd2 == -1){
        perror("Could not open second file!");
        return 1;
    }
    char c1,c2;
    int size = lseek(fd1,0,SEEK_END);
    lseek(fd1,0,SEEK_SET);
    for(int i=0;i<size;i++){
        read(fd1,&c1,sizeof(char));
        read(fd2,&c2,sizeof(char));
        lseek(fd1,-1,SEEK_CUR);
        lseek(fd2,-1,SEEK_CUR);
        write(fd1,&c2,sizeof(char));
        write(fd2,&c1,sizeof(char));
    }
    close(fd1);
    close(fd2);
    return 0;
}