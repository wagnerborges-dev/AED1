#include <stdio.h>
#include <stdlib.h>

int main(){

    // Função para abrir arquivo

  FILE * arq;
  char linha[100];

  arq = fopen("arquivo.txt", "r");

  if(arq == NULL){
    printf(" Nao e possivel criar o arquivo");
    exit(1);
  }
  else{
    printf(" Arquivo criado");
  }

   // fputc('C', arq);
   // fputs(" Boa noite! \n ", arq);
   // fprintf(arq, "Hellow word!!!"); 

   // fgets(linha, 100, arq);
   // printf("%s", linha);

   // fscanf(arq, "%s", linha);
   // printf("%s", linha);

   while(!feof(arq)){
      fscanf(arq, "%s", linha);
      printf("%s", linha);
   }

fclose(arq);

return 0;

}
