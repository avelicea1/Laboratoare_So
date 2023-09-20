#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define FIFO_NAME "pipe_cu_nume"
int main(){
    
    int fd=open(FIFO_NAME,O_WRONLY);
    if(fd ==-1){
        perror("eroare la deschidere");
        return 1;
    }
    char a[20] = "ana are mere";
    write(fd,a,13);
    write(fd,a,13);
    close(fd);
    return 0;
}