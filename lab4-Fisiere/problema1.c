#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFF_SIZE 1024

int get_line(int fd, int lineNr, char*line, int maxLength,int *lungimeSir){
    char *buff = (char*)malloc(maxLength*sizeof(char));
    int nrLinii = 0;
    int buff_size = 0;
    off_t size=lseek(fd,0,SEEK_END);
    char c = 0;
    lseek(fd,0,SEEK_SET);
    for(int i=0;i<size;i++){
        if(read(fd,&c,1)!=1){
            perror("Reading error!");
            return -2;
        }
        if(c == '\n'){
            nrLinii++;
            if(nrLinii == lineNr){
                if(buff_size+1 <= maxLength){
                strcpy(line,buff);
                strcat(line,"\n");
                *lungimeSir = strlen(line);
                }else{
                    return -3;
                }
            }else{
                for(int j=0;j<buff_size;j++){
                    buff[j] = ' ';
                }
                buff_size = 0;

            }
        }else{
            buff[buff_size++] = c;
        }

    }
    if(nrLinii < lineNr){
        return -1;
    }

}

int main(int argc, char *argv[]){
    char *fname = argv[1];
    int lineNr = atoi(argv[2]);

    int fd = open(fname,O_RDONLY);
    if(fd == -1){
        perror("open");
        return 1;
    }
    char *line =(char*) malloc(20*sizeof(char));
    int lungimeSir = 0;
    int ret = get_line(fd,lineNr,line,BUFF_SIZE,&lungimeSir);
    printf("%d ",ret);
    printf("%s ", line);
    close(fd);
    free(line);
    return 0;
}