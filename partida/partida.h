#ifndef PARTIDA_H
#define PARTIDA_H

#include "time.h"
#include "bd_time.h"

// Estrutura de partida
typedef struct partida Partida;

int partida_id(Partida *p);

Time *partida_time(Partida *p, int numero_time);

int partida_gols(Partida *p, int numero_time);

// Construtor de partida
Partida *partida_criar(
            const int id, 
            const int id_time1, const int id_time2, 
            const int gols_time1, const int gols_time2,
            BDTimes *bdt
    );

void imprimir_partida(Partida *partida);

// Função para liberar memória alocada para partida
void partida_limpar(Partida *partida);

#endif