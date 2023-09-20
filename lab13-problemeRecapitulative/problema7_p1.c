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
#include <dirent.h>

#define FIFO_NAME "myPipe"
#define path "folder"
int main(){
    int fd = -1;
    if(mkfifo(FIFO_NAME,0644)==-1){
        perror("error creating fifo!");
        return 1;
    }
    fd = open(FIFO_NAME,O_WRONLY);
    if(fd == -1){
        perror("could not open fifo!");
        return 1;
    }
    DIR *dir =NULL;
    struct dirent *entry = NULL;
    dir = opendir(path);
    char fullPath[500];
    struct stat statbuf;
    if(dir == NULL){
        perror("Could not open directory!");
        return 1;
    }
    while((entry = readdir(dir))!=NULL){
        snprintf(fullPath,512,"%s/%s",path,entry->d_name);
        //printf("%s\n",fullPath);
        if(lstat(fullPath,&statbuf)==0){
            if(S_ISREG(statbuf.st_mode)){
                write(fd,&entry->d_name,strlen(entry->d_name)+1);
                //printf("%s %ld",entry->d_name,strlen(entry->d_name)+1);
            }
        }
    }
    closedir(dir);
    close(fd);
    unlink(FIFO_NAME);
    return 0;
}