#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int findFile(const char *path, const char *file, const char *string,int *count){
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char fullPath[512];
    struct stat statbuf;
    dir = opendir(path);
    if(dir == NULL){
        perror("Could not open directory");
        return -1;
    }
    while((entry = readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0){
            snprintf(fullPath,512,"%s/%s",path,entry->d_name);
            if(lstat(fullPath,&statbuf)==0){
                printf("%s\n",fullPath);
                if(S_ISDIR(statbuf.st_mode)){
                    findFile(fullPath,file,string,count);
                }else{
                
                    if(S_ISREG(statbuf.st_mode)){
                        if(strcmp(entry->d_name,file)==0){
                            char fileLink[512];
                            
                            snprintf(fileLink,512,"%s.%d",entry->d_name,(*count)++);
                            
                            if(symlink(fullPath,fileLink)==-1){
                                printf("%s\n",fileLink);
                
                                perror("symlink");printf("%s\n",fullPath);
                                return -1;
                            }
                        }
                        if(string != NULL){
                            int fd1 = open(fullPath,O_RDONLY);
                            if(fd1 == -1){
                                perror("open file");
                                return -1;
                            }
                            int size = lseek(fd1,0,SEEK_END);
                            lseek(fd1,0,SEEK_SET);
                            char buff[1024];
                            char c;
                            for(int i=0;i<size;i++){
                                int citeste = read(fd1,&c,1);
                                if(citeste == -1){
                                    perror("Eroare la citire!");
                                    return -1;
                                }
                                
                            }
                            if(strstr(buff,string)!=NULL){
                                    printf("Am gasit un fisier care contine string ul!");
                                    return 0;
                            }
                            close(fd1);
                        }
                    }
                }
            }
        }
    }
    closedir(dir);
    return 0;
}
int main(int argc,char **argv){
    if(argc!=4){
        fprintf(stderr, "Usage: %s <dir_name>\n",argv[0]);
        return 1;
    }
    int count = 1;
    printf("%d ",findFile(argv[1],argv[2],argv[3],&count));
    return 0;
}