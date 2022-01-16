/* Definicao de funcaes*/
#include <stdio.h>
#include <stdlib.h>


void printfArray(int array[], int fim){
    for(int atual = 0; atual < fim; atual++){
       printf("%d ", array[atual]);
    }
}

int getMenor(int array[],int inicio, int fim){
    int menor = inicio;
    for(int atual = inicio; atual < fim; atual++){
        if(array[atual] < array[menor] ) menor = atual;
    }
    return menor;
}

void selectSort(int inicio, int fim, int array[]){
    for(int atual = inicio; atual < fim; atual++){
        int menor = getMenor(array, atual, fim);
        int arrayAtual = array[atual];
        int arrayMenor = array[menor];

        array[atual] = arrayMenor;
        array[menor] = arrayAtual;
    }
}

void insertionSort(int array[], int fim){

    for(int atual = 1; atual < fim; atual++){
        int analise = atual;
        while(analise > 0 && array[analise] < array[analise-1]){
            int arrayAnalise = array[analise];
            int arrayAnterior = array[analise-1];
            array[analise] = arrayAnterior;
            array[analise-1] = arrayAnalise;

            analise--;
        }
    }

}