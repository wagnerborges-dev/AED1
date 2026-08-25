#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char id;     
    float preco;
} Fruta;

int main() {
    int total_frutas;
    Fruta *frutas = NULL;

    printf("Quantas frutas deseja cadastrar inicialmente? ");
    if (scanf("%d", &total_frutas) != 1 || total_frutas <= 0) {
        printf("Quantidade invalida.\n");
        return 1;
    }

    
    frutas = (Fruta *) malloc(total_frutas * sizeof(Fruta));
    if (frutas == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    
    for (int i = 0; i < total_frutas; i++) {
        printf(" Fruta %d ", i + 1);
        printf("ID/Letra da fruta (ex: A, B, C): ");
        scanf(" %c", &frutas[i].id);
        printf("Preco: R$ ");
        scanf("%f", &frutas[i].preco);
    }

    
    char opcao;
    printf("\nDeseja adicionar mais uma fruta? (s/n): ");
    scanf(" %c", &opcao);

    if (opcao == 's' || opcao == 'S') {
        total_frutas++;

        
        Fruta *temp = (Fruta *) realloc(frutas, total_frutas * sizeof(Fruta));
        if (temp == NULL) {
            printf("Erro ao realocar memoria!\n");
            free(frutas);
            return 1;
        }
        frutas = temp;

        printf(" Fruta %d ", total_frutas);
        printf("ID/Letra da fruta (ex: D): ");
        scanf(" %c", &frutas[total_frutas - 1].id);
        printf("Preco: R$ ");
        scanf("%f", &frutas[total_frutas - 1].preco);
    }

    
    printf(" Lista de Frutas Cadastradas ");
    for (int i = 0; i < total_frutas; i++) {
        printf("%d. Fruta '%c' - R$ %.2f\n", i + 1, frutas[i].id, frutas[i].preco);
    }

    
    free(frutas);
    frutas = NULL;

    return 0;

    // // Alocação Dinamica na Linguagem C, questão 3
}