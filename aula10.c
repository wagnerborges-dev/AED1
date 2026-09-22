#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nome[100];
    float nota1;
    float nota2;
    float media;
} Aluno;

int main() {
    FILE *arquivo;
    int N;

    
    printf("Digite a quantidade de alunos (N): ");
    scanf("%d", &N);

    if (N <= 0) {
        printf("Quantidade de alunos invalida.\n");
        return 1;
    }

    
    arquivo = fopen("alunos.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir/criar o arquivo!\n");
        return 1;
    }

    
    fprintf(arquivo, "--- REGISTRO DE ALUNOS E NOTAS ---\n\n");

    
    for (int i = 0; i < N; i++) {
        Aluno a;

        printf("\n--- Aluno %d de %d ---\n", i + 1, N);


        printf("Nome: ");
        int j = 0;
        char c;
        
        while ((c = getchar()) != '\n' && j < 99) {
            a.nome[j] = c;
            j++;
        }
        a.nome[j] = '\0'; 

        printf("Nota 1: ");
        scanf("%f", &a.nota1);

        printf("Nota 2: ");
        scanf("%f", &a.nota2);

        
        a.media = (a.nota1 + a.nota2) / 2.0;

        
        fprintf(arquivo, "Aluno: %s\n", a.nome);
        fprintf(arquivo, "Nota 1: %.2f | Nota 2: %.2f | Media: %.2f\n", a.nota1, a.nota2, a.media);
        
    }

    
    fclose(arquivo);

    printf("\nDados de %d aluno(s) salvos com sucesso no arquivo 'alunos.txt'.\n", N);

    return 0;
}