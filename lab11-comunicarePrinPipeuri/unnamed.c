#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
int main(void)
{
    int fd[2];
    char s[20]= "andreea are mere";
    char t[20];
    int c;

    if(pipe(fd) != 0) {
        perror("Could not create pipe");
        return 1;
    }

    if(fork() != 0) {
        //parent
        close(fd[0]); //no use for read end
        
        c = strlen(s);
        write(fd[1],&c,1);
        write(fd[1], &s, c);
        printf("Parent: wrote %s to pipe\n", s);
        
        close(fd[1]);
        wait(NULL);
    } else {
        //child
        close(fd[1]); //no use for write end
        int m;
        read(fd[0],&m,1);
        read(fd[0],&t,m);
        printf("Child: read %s from pipe\n", t);
        close(fd[0]);
    }

    return 0;
}