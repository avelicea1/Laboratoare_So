#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int inverseaza(int fd1, int fd2){
    char oneLine[255];
    int sizeLine = 0;
    char lines[255][255];
    int nrLinii=0;
    char c = 0;
    while(read(fd1,&c,1)>0){
        if(c != '\n'){
            oneLine[sizeLine++]=c;
        }else{
            nrLinii++;
            oneLine[sizeLine]= '\0';
            printf("%d ",nrLinii);
            strcpy(lines[nrLinii-1],oneLine);
            //lseek(fd2,0,SEEK_SET);
            for(int j=0;j<sizeLine;j++){
                    oneLine[j] = ' ';
            }
            sizeLine = 0;
        }
    }
    printf("%d ",nrLinii);
    for(int i = nrLinii;i>=0;i--){
        if(write(fd2,lines[i],strlen(lines[i]))<0){
            perror("eroare scriere!");
            return -1;
        }else{
            write(fd2,"\n",1);
        }
    }
}
int main(int argc, char* argv[]){
    char *fname1, *fname2;
    fname1 = argv[1];
    fname2 = argv[2];
    int fd1 = open (fname1,O_RDONLY);
    if(fd1 == -1){
        perror("fisier 1 eroare!");
        return 1;
    }
    int fd2 = open(fname2,O_RDWR);
    if(fd2 == -1 ){
        perror("fisier 2 eroare!");
        return 1;
    }
    inverseaza(fd1,fd2);
    return 0;
}