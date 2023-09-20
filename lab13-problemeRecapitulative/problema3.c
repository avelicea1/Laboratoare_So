#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(){
    pid_t p2 = -1,p3 = -1,p4 = -1;
    printf("Procesul 1 a inceput\n");
    p2 = fork();
    if(p2 == -1){
        perror("Could not create process 2\n");
        return 1;
    }else if(p2 == 0){
        printf("Procesul 2 a inceput\n");
        p4 = fork();
        if(p4 == -1){
            perror("Could not create process 4\n");
            return 1;
        }else if (p4 == 0){
            printf("Procesul 4 a inceput\n");
            printf("Procesul 4 s a terminat\n");
        }else{
            wait(NULL);
            p3 = fork();
            if(p3 == -1){
                perror("Could not create process 3\n");
                return 1;
            }else if (p3 == 0){
                printf("Procesul 3 a inceput\n");
                printf("Procesul 3 s a terminat\n");
            }else{
                wait(NULL);
                printf("Procesul 2 s a terminat\n");
            }
        }
    }else{
        wait(NULL);
        printf("Procesul 1 s a terminat\n");
    }
    return 0;
}