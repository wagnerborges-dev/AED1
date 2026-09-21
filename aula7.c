#include <stdio.h>
#include <stdlib.h>

int main(){

    // Função para abrir arquivo

  FILE * arq;
  arq = fopen("arquivo.txt", "w");

  if(arq == NULL){
    printf(" Nao e possivel criar o arquivo");
    exit(1);
  }
  else{
    printf(" Arquivo criado");
  }

return 0;

}