#ifndef _BD_TIME_H
#define _BD_TIME_H

#include <string.h>

#include "time.h"
#include "auxiliares_globais.h"

// Macro para definir a quantidade de times
#define _QUANT_TIMES 10

// Lista interna com os times carregados do arquivo de texto
static Time *_times[_QUANT_TIMES];

// Função para acessar valores da lista privada
Time **lista_times() { return _times; }

// Função que traz os dados do arquivo de texto para a lista _times
void carregar_dados_times() {
    FILE *arquivo = fopen("times.csv", "r");
    
    if (arquivo == NULL) {
        // Implementação de erro, baseada em perror()
    }

    for (int i = 0; i < _QUANT_TIMES; i++) {
        int id;
        char *nome = (char*)malloc(sizeof(15 * sizeof(char)));
        inicializa_string(nome, 15);

        fscanf(arquivo, " %d,%s", &id, nome);

        _times[i] = criar_time(id, nome);
    }

    fclose(arquivo);
}

// Função auxiliar usada para criar e inicializar lista vazia de times
Time **_inicializa_lista_times() {
    Time **times = (Time**)malloc(_QUANT_TIMES * sizeof(Time*));
    for (int i = 0; i < _QUANT_TIMES; i++) {
        times[i] = NULL;
    }
    return times;
}

// Função auxiliar para montar prefixo, para consulta de time
char *_monta_prefixo(char *nome, const int tamanho) {
    char *prefixo = (char*)malloc((tamanho + 1) * sizeof(char));

    for (int i = 0; i < tamanho; i++) {
        prefixo[i] = nome[i];
    }
    prefixo[tamanho] = '\0';

    return prefixo;
}

// Função usada para montar lista de times a partir do nome ou do prefixo
Time **retornar_times(const char *nome) {
    Time **times = _inicializa_lista_times();
    int j = 0;

    for (int i = 0; i < _QUANT_TIMES; i++) {
        char *prefixo = _monta_prefixo(_times[i]->nome, strlen(nome));

        if (
            strcmp(_times[i]->nome, nome) == 0          // Entrada bate com o nome
            || strcmp(prefixo, nome) == 0               // Entrada bate com o prefixo
        ) {
            times[j++] = _times[i];
        }

        free(prefixo);
    }

    return times;
}

// Função para imprimir vários times em sequência, com cabeçalho
void imprimir_times(Time **times) {
    printf("ID\tTime\t\tV\tE\tD\tGM\tGS\tS\tPG\n");
    
    for (int i = 0; times[i] != NULL && i < _QUANT_TIMES; i++) {
        Time *time = times[i];
        printf(
            "%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", time->id, time->nome, time->vitorias,
            time->empates, time->derrotas, time->gols_marcados, time->gols_sofridos, 
            saldo_de_gols(time), pontos_ganhos(time)
        );
    }

    printf("\n");
}

// Funcionalidade 1, para consultar e imprimir os times a partir do nome ou prefixo
void consultar_times() {

    // Entrada do usuário
    char nome[TAMANHO_MAX_ENTRADA];
    inicializa_string(nome, TAMANHO_MAX_ENTRADA);

    printf("Digite o nome ou o apelido do time: ");
    scanf(" %s", nome);
    nome[TAMANHO_MAX_ENTRADA - 1] = '\0';
    
    // Retorno da lista de ponteiros para times
    Time **times = retornar_times(nome);

    // Validação da lista
    if (times[0] == NULL) {
        printf("\nNenhum time encontrado\n\n");
        return;
    }

    // Impressão da lista
    imprimir_times(times);

    // Liberação de memória da lista alocada dinamicamente
    free(times);
}

// Funcionalidade para desalocar todos os times
void apagar_times() {
    for (int i = 0; i < _QUANT_TIMES; i++) {
        apagar_time(_times[i]);
    }
}

#endif