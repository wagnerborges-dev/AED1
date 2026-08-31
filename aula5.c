#include <stdlib.h>
#include <stdio.h>
#define MAX 3

typedef struct pessoa
{
    char nome[50];
    int idade;
    char cpf[20];
    char rg[20];
    char telefone[20] 
} Pessoa;

void preenche(Pessoa *p){

    printf(" Digite o nome: ");
    scanf(" %[^\n]", p->nome);

    printf(" Digite a idade: ");
    scanf("%d", &p->idade);

    printf(" Digite o cpf: ");
    scanf(" %[^\n]", p->cpf);

    printf(" Digite o rg: ");
    scanf(" %[^\n]", p->rg);

    printf(" Digite o telefone: ");
    scanf(" %[^\n]", p->telefone);

}

void imprime(Pessoa *p){
    printf(" Nome: %s", p->nome);
    printf(" idade: %d", p->idade);
    printf(" cpf: %s", p->cpf);
    printf(" rg: %s", p->rg);
    printf(" telefone: %s", p->telefone);
}

int main(){
    // Pessoa p[MAX];

    Pessoa *p = (Pessoa*) malloc(MAX*sizeof(Pessoa));
    if (p == NULL){
        printf(" Sem memoria");
        exit (1);
    } else{
        printf(" Alocacao realizada");
    }

    int contador;
    for (contador = 0; contador < MAX; contador++){
        preenche(&p[contador]);
    }

    p = (Pessoa*) realloc(p, 5*sizeof(Pessoa));
    for(contador = 3; contador < 5; contador++){
        preenche(&p[contador]);

    }


    for (contador = 0; contador < MAX; contador++){
        imprime(&p[contador]);
    }

    return 0;
}
