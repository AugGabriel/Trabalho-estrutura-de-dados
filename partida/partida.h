#ifndef PARTIDA_H
#define PARTIDA_H

#include "time.h"
#include "bd_times.h"

// Estrutura de partida
typedef struct partida Partida;

// Construtor de partida
Partida *partida_criar(
        BDTimes *bdt,
        const int id, 
        const int id_time1, const int id_time2, 
        const int gols_time1, const int gols_time2
);

// Getters
int partida_id(Partida *p);
Time *partida_time(Partida *p, int numero_time);
int partida_gols(Partida *p, int numero_time);

// Setters
void partida_definir_gols(Partida *p, int numero_time, int gols);

typedef enum {
    APLICAR_RESULTADO,
    REVERTER_RESULTADO,
} ModoResultado;

// Aplica ou reverte a contribuição da partida nas estatísticas dos dois times
void partida_aplicar_resultado(Partida *p, ModoResultado modo);

void partida_imprimir(Partida *partida);

// Função para liberar memória alocada para partida
void partida_limpar(Partida *partida);

#endif