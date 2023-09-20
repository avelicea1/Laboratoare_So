#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(){

    int fdPipe[2];
    if(pipe(fdPipe)!=0){
        perror("Could not create pipe file!");
        return 1;
    }
    pid_t procesCopil = -1;
    int fd = -1;
    procesCopil = fork();
    if(procesCopil == -1){
        perror("Could not create child process");
        return 1;
    }else if (procesCopil == 0){
        close(fdPipe[1]);
        char c=1;
        while(c!=0){
            if(read(fdPipe[0],&c,sizeof(char))!=1){
                perror("Could not read from pipe!");
                return 1;
            }
            if(c%2 == 0){
                printf("%c\n",c);
            }
        }
        exit(0);
        close(fdPipe[0]);
    }else{
        close(fdPipe[0]);
        fd = open("fisierBinar",O_RDONLY);
        if(fd == -1){
            perror("Could not open the binary file!");
            return 1;
        }
        char c;
        int size = lseek(fd,0,SEEK_END);
        lseek(fd,0,SEEK_SET);
        for(int i=0;i<size;i++){
            if(read(fd,&c,1)!=1){
                perror("Could not read character!");
                return 1;
            }
            if(c>='0'&&c<='9'){
                write(fdPipe[1],&c,sizeof(char));
            }
        }
        char x = 0;
        write(fdPipe[1],&x,sizeof(char));
        close(fdPipe[1]);
        wait(NULL);
    }
    return 0;
}