#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    pid_t pid2 = -1,pid3 = -1,pid4 = -1,pid5 = -1;
    int status1, status2;
    pid2 = fork();
    if(pid2 == -1){
        perror("could not create child 2");
        return -1;
    }else{
        if(pid2 == 0){
            printf("Child 2 pid = %d, Parent 1 pid = %d \n",getpid(),getppid());
            pid4 = fork();
            if(pid4 == -1){
                perror("could not create child 4");
                return -1;
            }else{
                if(pid4 == 0){
                    printf("Child 4 pid = %d , Parent 2  pid = %d \n",getpid(),getppid());
                }else{
                    waitpid(pid4,&status1,0);
                }
            }
        }else
        {
            pid3 = fork();
            if(pid3 == -1){
                perror("could not create child 3");
                return -1;
            }else{
                if(pid3 == 0){
                    printf("Child 3 pid = %d, Parent 1 pid = %d \n",getpid(),getppid());
                    pid5 = fork();
                    if(pid5 == -1){
                        perror("could not create child 5");
                        return -1;
                    }else{
                        if(pid5 == 0){
                            printf("Child 5 pid = %d , Parent 3 pid = %d \n", getpid(),getppid());
                        }else{
                            waitpid(pid5,&status2,0);
                        }
                    }
                }
            }
        }
    }
    sleep(60);
    return 0;
}
