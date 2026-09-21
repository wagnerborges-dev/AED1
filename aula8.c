#include <stdio.h>
#include <stdlib.h>

typedef struct aluno{
    int matricula;
    char nome[50];
    float nota_final;
    
}Aluno ;


int main(){

 
  struct aluno Aluno;
  FILE * arq;
  int i;

  arq = fopen("alunos.txt", "w");

  if(arq == NULL){
    printf(" Nao e possivel criar o arquivo");
    exit(1);
  }
  else{
    printf(" Arquivo criado \n");
  } 

  printf(" ---  Cadastro dos alunos --- \n");

  for(i = 0; i < 5; i++){
    printf(" Alunos %d \n", i + 1);

    printf(" Informe sua matricula: ");
    scanf("%d", &Aluno.matricula);

    printf(" Informe o seu nome: ");
    scanf(" %[^\n]", Aluno.nome);

    printf(" Informe a sua nota final: ");
    scanf("%f", &Aluno.nota_final);

    fprintf(arq, "%d %s %f\n", Aluno.matricula, Aluno.nome, Aluno.nota_final);

  }

fclose(arq);

  arq = fopen("alunos.txt", "r");

  if(arq == NULL){
    printf(" Nao e possivel criar o arquivo");
    exit(1);
  }
  else{
    printf(" Arquivo criado \n");
  } 

  printf("matricula\tnome\t\tnota_final");

  while(fscanf(arq, "%d %s %f", &Aluno.matricula, Aluno.nome, &Aluno.nota_final) == 3){
    printf("%d %s %f\n", &Aluno.matricula, Aluno.nome, &Aluno.nota_final);
  }

  fclose(arq);

return 0;

}