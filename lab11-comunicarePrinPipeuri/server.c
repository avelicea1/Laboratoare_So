#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_NAME "pipe1"
#define FIFO_NAME2 "pipe2"

int main(void)
{
    int fd = -1;
    if(mkfifo(FIFO_NAME2, 0600) != 0) {
        perror("Could not create pipe");
        return 1;
    }
    //open, read and close fifo
    fd = open(FIFO_NAME, O_RDONLY);
    if(fd == -1) {
        perror("Could not open FIFO for reading");
        return 1;
    }
    int x = 0;
    int y = 0;
    char operator;
    read(fd, &x, sizeof(x));
    read(fd, &y, sizeof(y));
    read(fd, &operator, sizeof(operator));
    int rezultat = 0;
    if(operator == '-'){
        rezultat = x-y;
    }else if(operator == '+'){
        rezultat = x+y;
    }
    close(fd);
    int fd1 = open(FIFO_NAME2, O_WRONLY);
    if(fd1 == -1) {
        perror("Could not open FIFO for reading");
        return 1;
    }
    write(fd1,&rezultat,sizeof(int));
    close(fd1);
    unlink(FIFO_NAME2);
    return 0;
}