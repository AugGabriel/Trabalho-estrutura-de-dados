#ifndef _TIME_H
#define _TIME_H

#include <stdlib.h>
#include <stdio.h>

// Estrutura de time
typedef struct time Time;

// Propriedade de time, que determina os pontos ganhos
int pontos_ganhos(const Time *time);

// Propriedade de time, que determina o saldo de gols
int saldo_de_gols(const Time *time);

// Construtor de time
Time *criar_time(const int id, char *nome);

// Função para liberar memória alocada para time
void apagar_time(Time *time);

#endif