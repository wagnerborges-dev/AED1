#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct entrevista
{
    char nome[70];
    int cpf;
    int telefone;
    int idade;
    char endereco[70];

}Entrevista;

// Testando a struct para ver se está funcionando

void impressao (Entrevista *e){

    printf(" Nome: %s \n", e->nome);
    printf(" cpf: %d \n", &e->cpf);
    printf(" telefone: %d \n", &e->telefone);
    printf(" idade: %d \n", &e->idade);
    printf(" endereco: %s \n", e->endereco);
}

// inciando o programa 

int main(){
    Entrevista e[MAX]; // definindo a variavel struct
    impressao(e); // chamando os dados acima 
    int i; // declarando a variavel para o nosso loop

    printf(" || -- Entrevista de emprego para 10 vagas -- || \n"); // informando o que o progrma ira fazer 

    for(i = 0; i < MAX; i++){ // iniciando nosso loop para analisar 10 candidatos a vaga de emprego
       printf(" || -- Candidado %d -- || \n", i +1);

    printf(" Informe seu nome completo:  ");
    scanf(" %[^\n]", e[i].nome);

    printf(" Informe seu cpf:  ");
    scanf("%d", &e[i].cpf);

    printf(" Informe a sua idade: ");
    scanf("%d", &e[i].idade);

    printf(" Informe seu telefone:  ");
    scanf("%d", &e[i].telefone);

    printf(" Informe seu endereco:  ");
    scanf(" %[^\n]", e[i].endereco);

    if(e[i].idade >= 18){ // verificando se o condidato e maior de idade, para disputar a vaga 
        printf(" Voce ira disputar a vaga!! \n");
    }
    else{
        printf(" Voce nao esta apto para concorrer a vaga, lamento \n");
    }
    }
    return 0;
}
