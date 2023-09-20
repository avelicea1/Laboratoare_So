#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define FIFO_NAME "pipe_cu_nume"
int main(){
    if(mkfifo(FIFO_NAME,0644)!=0){
        perror("eroare la creare pipe");
        return 1;
    }
    int fd=open(FIFO_NAME,O_RDONLY);
    if(fd ==-1){
        perror("eroare la deschidere");
        return 1;
    }
    char a_read[20];

    int bytes_read = read(fd,a_read,20);

    printf("am citit %d bytes si erau: %s\n",bytes_read,a_read);

    close(fd);
    unlink(FIFO_NAME);
    return 0;
}