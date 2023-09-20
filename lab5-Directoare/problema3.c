#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
void deleteDir(const char *path){
    DIR *dir =NULL;
    struct dirent *entry =NULL;
    char fullPath[512];
    struct stat statbuf;
    dir = opendir(path);
    if(dir == NULL){
        perror("Cannot open directory.");
        return;
    }
    while((entry = readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0){
            snprintf(fullPath,512,"%s/%s",path,entry->d_name);
            if(lstat(fullPath,&statbuf)==0){
                printf("%s\n",fullPath);
                if(S_ISDIR(statbuf.st_mode)){
                    deleteDir(fullPath);
                }else{
                    if(unlink(fullPath)!=0){
                        perror("unlink");
                        return;
                    }
                }
            }
        }
        
    }
    if(rmdir(path)!=0){
            perror("rmdir");
            return;
        }
    closedir(dir);
}
int main(int argc,char **argv){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <dir_name>\n",argv[0]);
        return 1;
    }
    deleteDir(argv[1]);
    return 0;
}