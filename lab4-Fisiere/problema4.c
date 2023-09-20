#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFF_SIZE 11

int inserareString(int fd, char string[] ,int pozitie,int lungimeSir){
    unsigned char buff1[20],buff2[20];
    int buff1_size=0, buff2_size=0,i;
    char c =0 ;
    off_t sizefisier = lseek(fd,0,SEEK_END);
    printf("%ld",sizefisier);
    lseek(fd,0,SEEK_SET);
    for(int i=0;i<sizefisier;i++){
        if(read(fd, &c, 1)!=1){
            perror("eroare!");
            break;
        }
        if(i<pozitie){
            buff1[buff1_size++]=c;
        }else{
            buff2[buff2_size++]=c;
        }
    }
    printf("%d",buff1_size);
    printf("%d",buff2_size);
    
    unsigned char final[20];
    int final_size=0;
    for(i=0;i<buff1_size;i++){
        final[final_size++] = buff1[i];
    }
    for(i=0;i<lungimeSir;i++){
        final[final_size++]=string[i];
    }
    for(i=0;i<buff2_size;i++){
        final[final_size++] = buff2[i];
    }
    final[final_size+1]='\0';
    printf("%d",final_size);
    lseek(fd,0,SEEK_SET);
    sizefisier= write(fd,final,final_size);
    if(sizefisier<=0){
        perror("eroare scriere!");
        return 1;
    }
    return 0;
}

int main(){

    int fd1 = -1;
    off_t size = 0,crtPos;
    unsigned char buff[BUFF_SIZE];
    fd1 = open("problema4input.txt",O_RDWR);
    if(fd1 ==  -1){
        perror("Could not open input file");
        return 1;
    }
    inserareString(fd1,"xyz",4,3);
    close(fd1);
}