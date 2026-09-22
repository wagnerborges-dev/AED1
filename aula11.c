#include <stdio.h>
#include <stdlib.h>


typedef struct {
    char nome[100];
    float preco;
} Fruta;

int main() {
    FILE *arquivo;
    Fruta f;
    char continuar;

    
    arquivo = fopen("frutas.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir ou criar o arquivo 'frutas.txt'.\n");
        return 1;
    }

    printf("=== CADASTRO DE FRUTAS ===\n");

    do {
        printf("\nDigite o nome da fruta: ");

        
        int i = 0;
        char c;
        while ((c = getchar()) != '\n' && i < 99) {
            f.nome[i] = c;
            i++;
        }
        f.nome[i] = '\0'; 

        printf("Digite o preco da fruta (R$): ");
        scanf("%f", &f.preco);

        
        fprintf(arquivo, "%s,%.2f\n", f.nome, f.preco);
        printf("Fruta '%s' cadastrada com sucesso!\n", f.nome);

        
        printf("\nDeseja cadastrar outra fruta? (s/n): ");
        scanf("%c", &continuar);
        
        

    } while (continuar == 's' || continuar == 'S');

    
    fclose(arquivo);

    printf("\nCadastro finalizado. O arquivo 'frutas.txt' foi atualizado e fechado com sucesso!\n");

    return 0;
}