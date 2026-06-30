#ifndef _BD_PARTIDA_H
#define _BD_PARTIDA_H

#include "time.h"
#include "partida.h"
#include "bd_time.h"

// Quantidade máxima de partidas permitida
#define MAX_PARTIDAS 100

// Definição de BDPartidaNode
typedef struct bd_partida_node BDPartidaNode;

// Definição de BDPartida
typedef struct bd_partida BDPartida;

// Criação de BDPartida
BDPartida *bdp_create();

// Obtenção do tamanho de BDPartida
int bdp_size(BDPartida *bdp);

// Adição de elemento ao final de BDPartida. Retorna o index aonde o elemento foi adicionado
int bdp_append(BDPartida *bdp, Partida *info);

// Obtenção de elemento de BDPartida. Se index for fora de BDPartida, retorno é NULL
Partida *bdp_get(BDPartida *bdp, int index);

// Apagar BDPartida, seus nós e as partidas dentro
void bdp_free(BDPartida *bdp);

// Apagar BDPartida, seus nós e as partidas dentro
void bdt_end(BDTime *bdt);

// Função para carregar os dados do arquivo de texto para a lista de partidas
BDPartida *bdp_carregar_dados(BDPartida *bdp, BDTime *bdt);

// Função usada para montar lista de partidas, a partir do modo de pesquisa e dos times para consultar
// Para cada partida, para cada time, se o time tiver jogado na partida, e na posição solicitada (mandante ou visitante), ele será adicionado à lista
BDPartida *retornar_partidas(BDPartida *bdp, BDTime *bdt, const int modo);

// Funcionalidade 2, para consultar partidas a partir do nome de um time
void consultar_partidas(BDTime *bdt, BDPartida *bdp);

#endif