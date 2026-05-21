#ifndef _PARTIDA_H
#define _PARTIDA_H

#include <stdlib.h>

#include "time.h"
#include "bd_time.h"

// Estrutura de partida
typedef struct partida {
    int id;

    Time* time1;
    Time* time2;

    int gols_time1;
    int gols_time2;
} Partida;

// Construtor de partida
Partida *criar_partida(
            const int id, 
            const int id_time1, const int id_time2, 
            const int gols_time1, const int gols_time2
    ) {
    static int cont = 0;

    Partida *partida = (Partida*)malloc(sizeof(Partida));

    partida->id = id;
    partida->time1 = lista_times()[id_time1];
    partida->time2 = lista_times()[id_time2];
    partida->gols_time1 = gols_time1;
    partida->gols_time2 = gols_time2;

    return partida;
}

// Função para liberar memória alocada para partida
void apagar_partida(Partida *partida) {
    free(partida);
}

#endif