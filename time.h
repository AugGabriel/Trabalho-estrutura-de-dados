#ifndef _TIME_H
#define _TIME_H

#include <stdlib.h>
#include <stdio.h>

// Estrutura de time
typedef struct time {
    int id;
    char *nome;

    int vitorias;
    int empates;
    int derrotas;

    int gols_marcados;
    int gols_sofridos;
} Time;

// Propriedade de time, que determina os pontos ganhos
int pontos_ganhos(Time *time) {
    int VALOR_VITORIA = 3, VALOR_EMPATE = 1;    // Não tenho certeza dos valores
    return time->vitorias * VALOR_VITORIA + time->empates * VALOR_EMPATE;
}

// Propriedade de time, que determina o saldo de gols
int saldo_de_gols(Time *time) {
    return time->gols_marcados - time->gols_sofridos;
}

// Construtor de time
Time *criar_time(int id, char *nome) {
    Time *time = (Time*)malloc(sizeof(Time));

    if (time == NULL) {
        printf("Não foi possível alocar memória para o time\n");
        return NULL;
    }

    time->id = id;
    time->nome = nome;

    time->vitorias = 0;
    time->empates = 0;
    time->derrotas = 0;
    time->gols_marcados = 0;
    time->gols_sofridos = 0;

    return time;
}

// Função para liberar memória alocada para time
void apagar_time(Time *time) {
    free(time);
}

#endif