#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd;
    off_t size, i;
    char *data = NULL;
    

    fd = open("problema3_fisier.txt", O_RDWR);
    if(fd == -1) {
        perror("Could not open input file");
        return 1;
    }
    size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    data = (char*)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(data == (void*)-1) {
        perror("Could not map file");
        close(fd);
        return 1;
    }
    char vocale [10] = {'a','e','i','o','u','A','E','I','O','U'}; 
    //printf("%d",strchr(vocale,'m'));
    for(i=0;i<size;i++){
        if(strchr(vocale,data[i])!=0){
            for(int j = i;j<size;j++){
                data[j]=data[j+1];
            }
            i--;
            data[size-1]=' ';
            size--;
        }
    }
    munmap(data, size);
    close(fd);

    return 0;
}