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
    int x = 3;
    int y = 4;
    char operator = '+';
    
    //create fifo
    if(mkfifo(FIFO_NAME, 0600) != 0) {
        perror("Could not create pipe");
        return 1;
    }

    //open, write and close fifo
    fd = open(FIFO_NAME, O_WRONLY);
    if(fd == -1) {
        perror("Could not open FIFO for writing");
        return 1;
    }
    //printf("Writing value %d to FIFO\n", x);
    //while(1){
        //scanf("%d",&x);
        //scanf("%d",&y);
        //scanf("%c",&operator);
        //if(operator == 'x'){
        //    close(fd);
        //    break;
        //}
        write(fd, &x, sizeof(x));
        write(fd, &y, sizeof(y));
        write(fd, &operator, sizeof(operator));
        //close(fd);
        //break;
    //}  
    close(fd);
    int fd1 = open(FIFO_NAME2, O_RDONLY);
    int rezultat = 0;
    read(fd1,&rezultat,sizeof(int));
    printf("%d",rezultat);
    close(fd1);
    //delete fifo
    unlink(FIFO_NAME);

    return 0;
}