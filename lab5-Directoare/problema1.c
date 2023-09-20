#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>


off_t dirSize (const char* dirPath)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char fullPath[512];
    struct stat statbuf;
    dir = opendir(dirPath);
    off_t size = 0 ;
    int visited[512]={0};
    int i=0,k=0;
    if(dir == NULL){
        perror("Could not open directory");
        return -1;
    }
    while((entry = readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0){
            snprintf(fullPath,512,"%s/%s",dirPath,entry->d_name);
            if(lstat(fullPath,&statbuf)==0){
                printf("%s\n",fullPath);
                printf("%ld\n",statbuf.st_size);
                printf("%ld\n",statbuf.st_ino);
                for(int j = 0; j<i;j++){
                    if(visited[j] == statbuf.st_ino)k++;
                }
                if(k==0){
                    visited[i++]=statbuf.st_ino;
                }
                if(S_ISLNK(statbuf.st_mode)&&k==0){
                    size+=0;
                }else if(S_ISDIR(statbuf.st_mode)){
                    off_t sizeSubDir = dirSize(fullPath);
                    size+=sizeSubDir;
                }
                else if(S_ISREG(statbuf.st_mode)&&k==0){
                    size += statbuf.st_size;
                }else if(k==0){
                    size +=1;
                }
            }
        }
    }
    closedir(dir);
    return size;
}

int main(int argc, char **argv){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <dir_name>\n",argv[0]);
        return 1;
    }
    printf("%ld ",dirSize(argv[1]));
    return 0;
}