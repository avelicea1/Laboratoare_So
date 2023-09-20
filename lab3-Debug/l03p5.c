#include <stdio.h>
#include <stdlib.h>
#define TRUE 0
#define FALSE -1
int insert(int *v1, int n1, int c1, int *v2, int n2, int pos){
    if(c1>=n1+n2){
        for(int i=n1-1;i>=pos;i--){
            v1[i+pos]=v1[i];
        }
        for(int i=pos;i<pos+n2;i++){
            v1[i]=v2[i-pos];
        }
        return TRUE;
        
    } else{
        return FALSE;
    }
}
int readArray(int *size, int *array)
{
    int i, sz,cp;

    printf("Size: \n");
    if(scanf("%d",&sz) != 1) { 
        printf("Error reading size!\n");
        return FALSE;
    }


    printf("Array:\n");
    for(i=0;i<sz;i++) {
        if(scanf("%d",&array[i]) != 1) {
            printf("Error reading element %d!\n",i);
            return  FALSE;
        }
    }

    *size = sz;
    return TRUE;
}
int main(){
    int *v1, n1, c1, *v2,n2, pos;
    printf("capacitate v1: \n");
    scanf("%d",&c1);
    printf("pozitie v2: \n");
    scanf("%d ",&pos);
    v1 = (int*)malloc(sizeof(int)*c1); 
    v2 = (int*)malloc(sizeof(int)*150); 
    if(readArray(&n1,v1)==TRUE){
        if(readArray(&n2,v2)==TRUE){
            printf("%d",insert(v1,n1,c1,v2,n2,pos));
        }
    }
    free(v1);
    free(v2);
}