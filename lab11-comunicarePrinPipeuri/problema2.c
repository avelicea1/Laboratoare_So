#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
int main(void)
{
    int fd[2];
    int c =0;
    
    if(pipe(fd) != 0) {
        perror("Could not create pipe");
        return 1;
    }

    if(fork() != 0) {
        //parent
        close(fd[0]); //no use for read end
        while(1){
            write(fd[1], &c, sizeof(c));
            c++;
            printf("Dimensiune pipe = %ld \n", c*sizeof(c));
        }
        close(fd[1]);
        wait(NULL);
    } else {
        
        //child
        close(fd[1]); //no use for write end
        //read(fd[0], &c, sizeof(c));
        sleep(10);
        //printf("Child: read %d from pipe\n", c);
        close(fd[0]);
    }
    
    return 0;
}