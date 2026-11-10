#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int dado;
    struct No *proximo;
} No;

typedef struct Pilha {
    No *topo;
} Pilha;

// Inicializar a pilha
void inicializar(Pilha *pilha);

// Verificar se esta vazia
int estaVazia(Pilha *pilha);

// Inserir elemento (PUSH)
void push(Pilha *pilha, int valor);

// Remover elemento (POP)
int pop(Pilha *pilha);

// Consultar topo (PEEK)
int peek(Pilha pilha, int *valor);

// Exibir elementos
void imprimirPilha(Pilha *pilha);

// Contar elementos
int contarElementos(Pilha pilha);

// Liberar memoria
void liberarPilha(Pilha *pilha);

int main() {
    Pilha pilha;
    int opcao, valor;

    inicializar(&pilha);

    do {
        printf("\n================ MENU PILHA ================\n");
        printf("1. Inserir elemento (PUSH)\n");
        printf("2. Remover elemento (POP)\n");
        printf("3. Consultar topo (PEEK)\n");
        printf("4. Verificar se esta vazia\n");
        printf("5. Exibir todos os elementos\n");
        printf("6. Consultar quantidade de elementos\n");
        printf("7. Liberar toda a memoria\n");
        printf("0. Sair\n");
        printf("Escolha sua opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Erro na leitura da opcao.\n");
            break;
        }

        switch (opcao) {
            case 1:
                printf("Digite o valor inteiro a ser inserido: ");
                scanf("%d", &valor);
                push(&pilha, valor);
                break;
            case 2:
                valor = pop(&pilha);
                // Estratégia adotada: se retornar -999999 e a pilha estiver vazia, tratamos o erro.
                // Como -999999 pode ser um valor válido teórica, a validação de pilha vazia interna protege a operação.
                break;
            case 3:
                if (peek(pilha, &valor)) {
                    printf("Elemento no topo: %d\n", valor);
                } else {
                    printf("A pilha esta vazia. Nao ha elemento no topo.\n");
                }
                break;
            case 4:
                if (estaVazia(&pilha)) {
                    printf("A pilha esta vazia.\n");
                } else {
                    printf("A pilha NAO esta vazia.\n");
                }
                break;
            case 5:
                imprimirPilha(&pilha);
                break;
            case 6:
                printf("Quantidade de elementos na pilha: %d\n", contarElementos(pilha));
                break;
            case 7:
                liberarPilha(&pilha);
                printf("Memoria da pilha liberada.\n");
                break;
            case 0:
                liberarPilha(&pilha);
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

void inicializar(Pilha *pilha) {
    pilha->topo = NULL;
}

int estaVazia(Pilha *pilha) {
    return (pilha->topo == NULL);
}

void push(Pilha *pilha, int valor) {
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro: falha na alocacao de memoria.\n");
        return;
    }
    novoNo->dado = valor;
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;
}

int pop(Pilha *pilha) {
    if (estaVazia(pilha)) {
        printf("Erro: tentativa de desempilhar em pilha vazia.\n");
        return -1; // Valor indicativo de erro tratado
    }
    No *removido = pilha->topo;
    int valor = removido->dado;
    pilha->topo = removido->proximo;
    free(removido);
    return valor;
}

int peek(Pilha pilha, int *valor) {
    if (pilha.topo == NULL) {
        return 0;
    }
    *valor = pilha.topo->dado;
    return 1;
}

void imprimirPilha(Pilha *pilha) {
    No *atual = pilha->topo;
    printf("\nTOPO\n");
    while (atual != NULL) {
        printf("%d\n", atual->dado);
        atual = atual->proximo;
    }
    printf("NULL\n");
}

int contarElementos(Pilha pilha) {
    int contador = 0;
    No *atual = pilha.topo;
    while (atual != NULL) {
        contador++;
        atual = atual->proximo;
    }
    return contador;
}

liberarPilha(Pilha *pilha) {
    No *atual = pilha->topo;
    No *proximoNo;
    while (atual != NULL) {
        proximoNo = atual->proximo;
        free(atual);
        atual = proximoNo;
    }
    pilha->topo = NULL;
}