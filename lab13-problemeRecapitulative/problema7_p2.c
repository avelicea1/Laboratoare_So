#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>

#define FIFO_NAME "myPipe"

int main(){
    int fd = -1;
    fd  = open(FIFO_NAME,O_RDONLY);
    if(fd == -1){
        perror("Could not open read pipe");
        return 1;
    }
    char c;
    char numeFisier[512];
    int k=0;
    while(1){
        if(read(fd,&c,sizeof(char))==0)
            break;
        numeFisier[k]=c;
        k++;
        if(c == '\0'){
            k=0;
            if(numeFisier[0]>='0'&&numeFisier[0]<='9'){
                printf("%s\n",numeFisier);
            }
        }
    }
    close(fd);
}