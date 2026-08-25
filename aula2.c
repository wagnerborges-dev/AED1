#include <stdio.h>
#include <stdlib.h>

int main(){

    int i, tamanho = 10;
    int * vetor = (int*) malloc(tamanho * sizeof(int*));

    if ( vetor == NULL){
        printf(" Erro na alocação ");
        exit (1);
    }
    else{
        printf(" vetor alocado ");
    }

    for (i = 0; i< tamanho; i++){
        vetor[i] = i;
        printf(" %d \t", vetor [i]);

    }
    
    //Alocação Dinamica na Linguagem C, questão 1
}