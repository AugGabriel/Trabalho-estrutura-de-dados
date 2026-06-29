#ifndef _TIME_MODULE_H
#define _TIME_MODULE_H

#include <stdlib.h>
#include <stdio.h>

// Estrutura de time
typedef struct time Time;

// Propriedades de time
int get_time_id(Time *time);
char *get_nome(Time *time);
int get_vitorias(Time *time);
int get_empates(Time *time);
int get_derrotas(Time *time);
int get_gols_marcados(Time *time);
int get_gols_sofridos(Time *time);

void set_time_id(Time *time, int id);
void set_nome(Time *time, char *nome);
void set_vitorias(Time *time, int vitorias);
void set_empates(Time *time, int empates);
void set_derrotas(Time *time, int derrotas);
void set_gols_marcados(Time *time, int gols);
void set_gols_sofridos(Time *time, int gols);

// Propriedade de time, que determina os pontos ganhos
int pontos_ganhos(const Time *time);

// Propriedade de time, que determina o saldo de gols
int saldo_de_gols(const Time *time);

// Construtor de time
Time *criar_time(const int id, char *nome);

// Impressão de time
void imprimir_time(Time *time);

// Função para liberar memória alocada para time
void apagar_time(Time *time);

#endif