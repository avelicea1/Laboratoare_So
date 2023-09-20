#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int inverseazaFisier(int fd1, int fd2){
    char c = 0;
    int k=1;
    char s[100];
    int size = lseek(fd1,0,SEEK_END);
    lseek(fd1,-k,SEEK_CUR);
    
    for(int i = size; i>=0; i--){
        int citeste = read(fd1,&c,1);
        if(citeste == -1){
            perror("Eroare la citire!");
            return 3;
        }
        //printf("%c ",c);
        
        int scrie = write(fd2,&c,1);
        if(scrie == -1){
            perror("Eroare la scriere!");
            return 2;
        }
        lseek(fd1,-k,SEEK_END);
        k++;
    }
    return 0;

}

int main(){
    int fd1 = open("fisiersursa2.txt",O_RDONLY);
    if(fd1 == -1 ){
        perror("Eroare la deschidere fisier 1!");
        return 1;
    }
    int fd2 = open("fisierdestinatie2.txt",O_RDWR);
    if(fd2 == -1){
        perror("Eroare la deschidere fisier 2!");
    }
    int result = inverseazaFisier(fd1,fd2);
    if(result == 0){
        printf("S a inversat");
    }
    close(fd1);
    close(fd2);
    return 0;

}