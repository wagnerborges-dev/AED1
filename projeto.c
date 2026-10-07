#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

// --- EXIGÊNCIA: Enum para estados e controle da aplicação ---
typedef enum {
    ESTADO_MENU,
    ESTADO_BUSCANDO,
    ESTADO_PAUSADO,
    ESTADO_ENCONTRADO,
    ESTADO_NAO_ENCONTRADO
} EstadoExecucao;

// --- EXIGÊNCIA: Union para flexibilidade do tipo da chave de busca ---
typedef union {
    int i_val;
    float f_val;
} ValorChave;

// --- EXIGÊNCIA: Struct para representação dos dados e visualização gráfica ---
typedef struct {
    ValorChave chave;
    int status_visual; // 0: Normal, 1: No intervalo [ini, fim], 2: Posição calculada (mid), 3: Encontrado
} Elemento;

// --- Variáveis Globais para Gerenciamento e Ponteiros ---
Elemento *vetor = NULL;
int total_elementos = 0;
int alvo_busca = 0;

int ini_idx = 0;
int fim_idx = 0;
int mid_idx = -1;
EstadoExecucao estado_atual = ESTADO_MENU;

// --- Estatísticas exigidas pelo trabalho ---
int comparacoes = 0;
int passos = 0;

// --- EXIGÊNCIA: Leitura de dados a partir de arquivos externos ---
int carregar_dados_arquivo(const char *nome_arquivo) {
    FILE *file = fopen(nome_arquivo, "r");
    if (!file) return 0;

    int count = 0;
    int temp;
    while (fscanf(file, "%d", &temp) == 1) {
        count++;
    }
    rewind(file);

    if (vetor) free(vetor);
    
    // --- EXIGÊNCIA: Uso de Ponteiros e alocação dinâmica ---
    vetor = (Elemento *)malloc(count * sizeof(Elemento));
    if (!vetor) {
        fclose(file);
        return 0;
    }

    for (int i = 0; i < count; i++) {
        fscanf(file, "%d", &vetor[i].chave.i_val);
        vetor[i].status_visual = 0;
    }

    total_elementos = count;
    fim_idx = total_elementos - 1;
    fclose(file);
    return 1;
}

// Inicializa ou reinicia os parâmetros da busca
void iniciar_busca(int alvo) {
    if (total_elementos == 0) return;
    alvo_busca = alvo;
    ini_idx = 0;
    fim_idx = total_elementos - 1;
    mid_idx = -1;
    comparacoes = 0;
    passos = 0;

    for (int i = 0; i < total_elementos; i++) {
        vetor[i].status_visual = 0;
    }
    estado_atual = ESTADO_BUSCANDO;
}

// --- Lógica Principal da Busca por Interpolação (Executada passo a passo) ---
void executar_passo_interpolacao() {
    if (estado_atual != ESTADO_BUSCANDO) return;

    passos++;

    if (ini_idx <= fim_idx && alvo_busca >= vetor[ini_idx].chave.i_val && alvo_busca <= vetor[fim_idx].chave.i_val) {
        comparacoes++;

        // Tratamento para evitar divisão por zero se os extremos forem iguais
        if (vetor[ini_idx].chave.i_val == vetor[fim_idx].chave.i_val) {
            mid_idx = ini_idx;
        } else {
            // Fórmula da Busca por Interpolação
            mid_idx = ini_idx + (((double)(fim_idx - ini_idx) / (vetor[fim_idx].chave.i_val - vetor[ini_idx].chave.i_val)) * (alvo_busca - vetor[ini_idx].chave.i_val));
        }

        // Limites de segurança para o índice
        if (mid_idx < 0) mid_idx = 0;
        if (mid_idx >= total_elementos) mid_idx = total_elementos - 1;

        // Atualiza os status visuais para a Raylib
        for (int i = 0; i < total_elementos; i++) {
            if (i >= ini_idx && i <= fim_idx) vetor[i].status_visual = 1; // Intervalo atual
            else vetor[i].status_visual = 0;
        }
        vetor[mid_idx].status_visual = 2; // Posição testada (mid)

        // Verificações de resultado
        if (vetor[mid_idx].chave.i_val == alvo_busca) {
            vetor[mid_idx].status_visual = 3; // Encontrado
            estado_atual = ESTADO_ENCONTRADO;
        } else if (vetor[mid_idx].chave.i_val < alvo_busca) {
            ini_idx = mid_idx + 1;
        } else {
            fim_idx = mid_idx - 1;
        }
    } else {
        estado_atual = ESTADO_NAO_ENCONTRADO;
    }
}

int main(void) {
    const int largura_tela = 1000;
    const int altura_tela = 700;
    
    // --- EXIGÊNCIA: Visualização gráfica utilizando a biblioteca Raylib ---
    InitWindow(largura_tela, altura_tela, "Trabalho II - Busca por Interpolacao (Raylib)");
    SetTargetFPS(60);

    // Tenta carregar o arquivo de dados (ex: "dados.txt"). Caso não encontre, cria dados de teste automáticos.
    if (!carregar_dados_arquivo("dados.txt")) {
        total_elementos = 25;
        vetor = (Elemento *)malloc(total_elementos * sizeof(Elemento));
        for (int i = 0; i < total_elementos; i++) {
            vetor[i].chave.i_val = i * 4 + 3; // Dados ordenados para interpolação
            vetor[i].status_visual = 0;
        }
    }

    while (!WindowShouldClose()) {
        // --- Controles Interativos Exigidos pela Raylib (Iniciar, Pausar, Próximo Passo, Reiniciar) ---
        if (IsKeyPressed(KEY_I)) { // Iniciar/Reiniciar buscando um elemento válido do meio
            iniciar_busca(vetor[total_elementos / 2].chave.i_val);
        }
        if (IsKeyPressed(KEY_SPACE)) { // Pausar / Continuar
            if (estado_atual == ESTADO_BUSCANDO) estado_atual = ESTADO_PAUSADO;
            else if (estado_atual == ESTADO_PAUSADO) estado_atual = ESTADO_BUSCANDO;
        }
        if (IsKeyPressed(KEY_RIGHT)) { // Executar o próximo passo manualmente
            if (estado_atual == ESTADO_BUSCANDO || estado_atual == ESTADO_PAUSADO) {
                executar_passo_interpolacao();
            }
        }

        // Renderização Gráfica
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // --- EXIGÊNCIA: Painel de Estatísticas em Tempo Real ---
        DrawText("ALGORITMO: Busca por Interpolacao", 20, 20, 20, DARKGRAY);
        DrawText(TextFormat("Elementos: %d", total_elementos), 20, 50, 16, GRAY);
        DrawText(TextFormat("Comparacoes: %d", comparacoes), 200, 50, 16, GRAY);
        DrawText(TextFormat("Passo: %d", passos), 380, 50, 16, GRAY);
        DrawText(TextFormat("Alvo Buscado: %d", alvo_busca), 520, 50, 16, BLUE);

        // Mensagens de Estado do Algoritmo
        const char *msg_status = "";
        Color cor_status = DARKGRAY;
        if (estado_atual == ESTADO_MENU) {
            msg_status = "Pressione [I] para Iniciar a Busca";
            cor_status = BLUE;
        } else if (estado_atual == ESTADO_BUSCANDO) {
            msg_status = "Status: Rodando... [ESPACO] Pausa | [SETA DIREITA] Proximo Passo";
            cor_status = ORANGE;
        } else if (estado_atual == ESTADO_PAUSADO) {
            msg_status = "Status: PAUSADO. Pressione [ESPACO] para continuar ou [SETA DIREITA] para avancar";
            cor_status = DARKBLUE;
        } else if (estado_atual == ESTADO_ENCONTRADO) {
            msg_status = "Status: Sucesso! Elemento ENCONTRADO. Pressione [I] para reiniciar.";
            cor_status = GREEN;
        } else if (estado_atual == ESTADO_NAO_ENCONTRADO) {
            msg_status = "Status: Elemento NAO encontrado. Pressione [I] para reiniciar.";
            cor_status = RED;
        }
        DrawText(msg_status, 20, 80, 16, cor_status);

        // --- Desenho das Barras e Destaques Visuais (Intervalos e Alvo) ---
        if (total_elementos > 0) {
            float largura_barra = (float)(largura_tela - 100) / total_elementos;
            float altura_maxima = 400.0f;
            int max_val = vetor[total_elementos - 1].chave.i_val;
            if (max_val == 0) max_val = 1;

            for (int i = 0; i < total_elementos; i++) {
                float h = ((float)vetor[i].chave.i_val / max_val) * altura_maxima;
                float x = 50 + i * largura_barra;
                float y = 620 - h;

                Color cor_barra = LIGHTGRAY; // Padrão
                if (vetor[i].status_visual == 1) cor_barra = SKYBLUE; // Intervalo atual [ini, fim]
                else if (vetor[i].status_visual == 2) cor_barra = ORANGE; // Posição testada (mid)
                else if (vetor[i].status_visual == 3) cor_barra = GREEN; // Encontrado

                DrawRectangle(x, y, largura_barra - 2, h, cor_barra);
            }
        }

        EndDrawing();
    }

    // Liberação de memória alocada dinamicamente
    if (vetor) free(vetor);
    CloseWindow();
    return 0;
}