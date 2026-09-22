#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char nome[100];
    float salario;
} Funcionario;

int main() {
    FILE *arquivo;
    Funcionario func;
    char continuar;

    arquivo = fopen("funcionarios.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    do {
        printf("\n--- Cadastro de Funcionario ---\n");
        
        printf("ID: ");
        scanf("%d", &func.id);
        
        

        printf("Nome: ");
        
        int i = 0;
        char c;
        while ((c = getchar()) != '\n' && i < 99) {
            func.nome[i] = c;
            i++;
        }
        func.nome[i] = '\0'; 

        printf("Salario: R$ ");
        scanf("%f", &func.salario);

        
        fprintf(arquivo, "ID: %d | Nome: %s | Salario: %.2f\n", func.id, func.nome, func.salario);
        printf("Funcionario cadastrado com sucesso!\n");

        printf("\nDeseja cadastrar outro funcionario? (s/n): ");
        
        scanf("%c", &continuar);

    } while (continuar == 's' || continuar == 'S');

    
    fclose(arquivo);
    printf("\nDados salvos em 'funcionarios.txt'. Programa encerrado.\n");

    return 0;
}