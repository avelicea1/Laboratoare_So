#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    int i,n=7;
    int contor = 0;
    for(i=0;i<n;i++){
        pid_t a = fork();
        if(a==0){
            exit(contor);
        }

    }

}