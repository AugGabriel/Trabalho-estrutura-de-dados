#ifndef BDPARTIDAS_H
#define BDPARTIDAS_H

#include "linkedlist.h"
#include "partida.h"

// Enumerate para modos de pesquisa de time, na funcionalidade 2
typedef enum filtro_pesquisa_partida {
    TIME_MANDANTE = 0,
    TIME_VISITANTE = 1,
    AMBOS = 2,
} FILTRO_PESQUISA_PARTIDA;

typedef struct bdpartidas BDPartidas;

BDPartidas *bdp_criar();

BDPartidas *bdp_criar_usando_arquivo(char nome_arquivo[], BDTimes *bdt);

int bdp_quant_partidas(BDPartidas *bdp);

Partida *bdp_obter_partida(BDPartidas *bdp, int i);

// Função usada para montar lista de partidas, a partir do modo de pesquisa e dos times para consultar
// Para cada partida, para cada time, se o time tiver jogado na partida, e na posição solicitada (mandante ou visitante), ele será adicionado à lista
LinkedList *bdp_encontrar_partidas(BDPartidas *bdp, LinkedList *times, const int modo);

// Função para desalocar a memória de todas as partidas
void bdp_limpar(BDPartidas *bdp);

#endif