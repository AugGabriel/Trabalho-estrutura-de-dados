#ifndef _PARTIDA_H
#define _PARTIDA_H

#include <stdlib.h>
#include "time.h"
#include "bd_time.h"

// Estrutura de partida
typedef struct partida Partida;

// Atributos de partida
int get_partida_id(Partida *partida);
Time *get_time1(Partida *partida);
Time *get_time2(Partida *partida);
int get_gols_time1(Partida *partida);
int get_gols_time2(Partida *partida);

void set_partida_id(Partida *partida, int id);
void set_time1(Partida *partida, Time *time);
void set_time2(Partida *partida, Time *time);
void set_gols_time1(Partida *partida, int gols);
void set_gols_time2(Partida *partida, int gols);

// Construtor de partida
Partida *criar_partida(
    BDTime *bdt, const int id, 
    const int id_time1, const int id_time2, 
    const int gols_time1, const int gols_time2
);

// Impressão de partida
void imprimir_partida(Partida *partida);

// Função para liberar memória alocada para partida
void apagar_partida(Partida *partida);

#endif