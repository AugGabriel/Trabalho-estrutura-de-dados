#include "time.h"
#include <stdio.h>
#include <stdlib.h>

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

// Construtor de time
Time *time_criar(const int id, char *nome) {
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

void time_imprimir(Time *time) {
    printf(
        "%d\t%9s\t\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", 
        time->id, 
        time->nome, 
        time->vitorias,
        time->empates, 
        time->derrotas, 
        time->gols_marcados, 
        time->gols_sofridos, 
        time_saldo_de_gols(time), 
        time_pontos_ganhos(time)
    );
}

// Propriedade de time, que determina os pontos ganhos
int time_pontos_ganhos(const Time *time) {
    // Regra de pontuação: 3 pontos por vitória, 1 por empate, 0 por derrota
    int VALOR_VITORIA = 3, VALOR_EMPATE = 1;
    return time->vitorias * VALOR_VITORIA + time->empates * VALOR_EMPATE;
}

// Propriedade de time, que determina o saldo de gols
int time_saldo_de_gols(const Time *time) {
    return time->gols_marcados - time->gols_sofridos;
}

// Getters
int time_id(Time *t) {
    return t->id;
}
char *time_nome(Time *t) {
    return t->nome;
}
int time_gols_marcados(Time *t) {
    return t->gols_marcados;
}
int time_gols_sofridos(Time *t) {
    return t->gols_sofridos;  
}
int time_vitorias(Time *t) {
    return t->vitorias;
}
int time_derrotas(Time *t) {
    return t->derrotas;
}
int time_empates(Time *t) {
    return t->empates;
}

// Setters
void time_definir_gols_marcados(Time *t, int valor) {
    t->gols_marcados = valor;
}
void time_definir_gols_sofridos(Time *t, int valor) {
    t->gols_sofridos = valor;  
}
void time_definir_vitorias(Time *t, int valor) {
    t->vitorias = valor;
}
void time_definir_derrotas(Time *t, int valor) {
    t->derrotas = valor;
}
void time_definir_empates(Time *t, int valor) {
    t->empates = valor;
}

// Função para liberar memória alocada para time
void time_limpar(Time *time) {
    free(time);
}
