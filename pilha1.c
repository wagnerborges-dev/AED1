#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int dado;
    struct No *proximo;
} No;

typedef struct Pilha {
    No *topo;
} Pilha;

void inicializar(Pilha *pilha);
int estaVazia(Pilha *pilha);
void push(Pilha *pilha, int valor);
int pop(Pilha *pilha);
int peek(Pilha *pilha, int *valor);
void imprimirPilha(Pilha *pilha);
int contarElementos(Pilha *pilha);
void liberarPilha(Pilha *pilha);

void inicializar(Pilha *pilha) {
    pilha->topo = NULL;
}

int estaVazia(Pilha *pilha) {
    return pilha->topo == NULL;
}

void push(Pilha *pilha, int valor) {
    No *novo = malloc(sizeof *novo);

    if (novo == NULL) {
        printf("Erro: nao foi possivel alocar memoria.\n");
        return;
    }

    novo->dado = valor;
    novo->proximo = pilha->topo;
    pilha->topo = novo;
}

int pop(Pilha *pilha) {
    No *removido;
    int valor;

    errno = 0;
    if (estaVazia(pilha)) {
        errno = ERANGE;
        return 0;
    }

    removido = pilha->topo;
    valor = removido->dado;
    pilha->topo = removido->proximo;
    free(removido);

    return valor;
}

int peek(Pilha *pilha, int *valor) {
    if (estaVazia(pilha)) {
        return 0;
    }

    *valor = pilha->topo->dado;
    return 1;
}

void imprimirPilha(Pilha *pilha) {
    No *atual = pilha->topo;

    if (atual == NULL) {
        printf("Pilha vazia.\n");
        return;
    }

    printf("TOPO\n");
    while (atual != NULL) {
        printf("%d\n", atual->dado);
        atual = atual->proximo;
    }
    printf("NULL\n");
}

int contarElementos(Pilha *pilha) {
    No *atual = pilha->topo;
    int quantidade = 0;

    while (atual != NULL) {
        quantidade++;
        atual = atual->proximo;
    }

    return quantidade;
}

void liberarPilha(Pilha *pilha) {
    No *atual = pilha->topo;

    while (atual != NULL) {
        No *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    pilha->topo = NULL;
}

int lerInteiro(const char *mensagem, int *valor) {
    int resultado;

    printf("%s", mensagem);
    resultado = scanf("%d", valor);

    if (resultado == 1) {
        return 1;
    }

    if (resultado == EOF) {
        return 0;
    }

    printf("Entrada invalida. Digite um numero inteiro.\n");
    while (getchar() != '\n') {
    }
    return -1;
}

int main(void) {
    Pilha pilha;
    int opcao;
    int valor;
    int leitura;

    inicializar(&pilha);

    do {
        printf("\n1 - Inserir elemento\n");
        printf("2 - Remover elemento do topo\n");
        printf("3 - Consultar elemento do topo\n");
        printf("4 - Verificar se a pilha esta vazia\n");
        printf("5 - Exibir todos os elementos\n");
        printf("6 - Consultar quantidade de elementos\n");
        printf("7 - Liberar a pilha\n");
        printf("0 - Sair\n");

        leitura = lerInteiro("Opcao: ", &opcao);
        if (leitura == 0) {
            break;
        }
        if (leitura == -1) {
            continue;
        }

        switch (opcao) {
            case 1:
                leitura = lerInteiro("Valor: ", &valor);
                if (leitura == 1) {
                    push(&pilha, valor);
                }
                break;

            case 2:
                valor = pop(&pilha);
                if (errno == ERANGE) {
                    printf("Nao foi possivel remover: a pilha esta vazia.\n");
                } else {
                    printf("Elemento removido: %d\n", valor);
                }
                break;

            case 3:
                if (peek(&pilha, &valor)) {
                    printf("Elemento do topo: %d\n", valor);
                } else {
                    printf("Nao ha elemento no topo: a pilha esta vazia.\n");
                }
                break;

            case 4:
                printf("%s\n", estaVazia(&pilha)
                    ? "A pilha esta vazia."
                    : "A pilha nao esta vazia.");
                break;

            case 5:
                imprimirPilha(&pilha);
                break;

            case 6:
                printf("Quantidade de elementos: %d\n",
                       contarElementos(&pilha));
                break;

            case 7:
                liberarPilha(&pilha);
                printf("Pilha liberada.\n");
                break;

            case 0:
                break;

            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    liberarPilha(&pilha);
    return 0;
}