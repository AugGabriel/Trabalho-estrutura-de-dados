#ifndef _PARTIDA_H
#define _PARTIDA_H

#include <stdlib.h>

#include "time.h"
#include "bd_time.h"

// Estrutura de partida
typedef struct partida Partida;

// Construtor de partida
Partida *criar_partida(
        const int id, 
        const int id_time1, const int id_time2, 
        const int gols_time1, const int gols_time2
);

// Função para liberar memória alocada para partida
void apagar_partida(Partida *partida);

#endif