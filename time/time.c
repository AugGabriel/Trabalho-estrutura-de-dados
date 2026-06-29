#include <stdlib.h>
#include <stdio.h>
#include "time.h"

// Estrutura de time
struct time {
   int id;
   char *nome;

   int vitorias;
   int empates;
   int derrotas;

   int gols_marcados;
   int gols_sofridos;
};

// Atributos de time
int get_time_id(Time *time) { return time->id; }
char *get_nome(Time *time) { return time->nome; }
int get_vitorias(Time *time) { return time->vitorias; }
int get_empates(Time *time) { return time->empates; }
int get_derrotas(Time *time) { return time->derrotas; }
int get_gols_marcados(Time *time) { return time->gols_marcados; }
int get_gols_sofridos(Time *time) { return time->gols_sofridos; }
int get_id(Time *time) { return time->id; }

void set_time_id(Time *time, int id) { time->id = id; }
void set_nome(Time *time, char *nome) { time->nome = nome; }
void set_vitorias(Time *time, int vitorias) { time->vitorias = vitorias; }
void set_empates(Time *time, int empates) { time->empates = empates; }
void set_derrotas(Time *time, int derrotas) { time->derrotas = derrotas; }
void set_gols_marcados(Time *time, int gols) { time->gols_marcados = gols; }
void set_gols_sofridos(Time *time, int gols) { time->gols_sofridos = gols; }

// Propriedade de time, que determina os pontos ganhos
int pontos_ganhos(const Time *time) {
    int VALOR_VITORIA = 3, VALOR_EMPATE = 1;    // Não tenho certeza dos valores
    return time->vitorias * VALOR_VITORIA + time->empates * VALOR_EMPATE;
}

// Propriedade de time, que determina o saldo de gols
int saldo_de_gols(const Time *time) {
    return time->gols_marcados - time->gols_sofridos;
}

// Construtor de time
Time *criar_time(const int id, char *nome) {
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

// Impressão de time
void imprimir_time(Time *time) {
    printf(
        "%d\t%9s\t\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", time->id, time->nome, time->vitorias,
        time->empates, time->derrotas, time->gols_marcados, time->gols_sofridos, 
        saldo_de_gols(time), pontos_ganhos(time)
    );
}

// Função para liberar memória alocada para time
void apagar_time(Time *time) {
    free(time);
}