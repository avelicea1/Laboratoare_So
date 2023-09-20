#include <stdio.h>
#include <stdlib.h>
unsigned int inverseaza(unsigned int number){
    unsigned int variabila1 = (0x000000ff & number);
    unsigned int variabila2 = (0xff000000 & number);
    unsigned int variabila3 = (0x00ff0000 & number); 
    unsigned int variabile4 = (0x0000ff00 & number);
    variabila1= variabila1<<24;
    variabila2=variabila2>>24;
    variabila3=variabila3>>8;
    variabile4=variabile4<<8;
    unsigned int rezultat = variabila1|variabila2|variabila3|variabile4;
    return rezultat;
}
int main(int argc, char **argv){
    unsigned int number = atoi(argv[1]);
    printf("%d",inverseaza(number));
}