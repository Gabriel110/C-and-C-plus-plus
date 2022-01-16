#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#define TAM 5

int main(void){
    int array[] = {3,0,1,2,-1};

    //selectSort(0, TAM, array);

    insertionSort(array, TAM);
    
    printfArray(array, TAM);
    return 0;
}

