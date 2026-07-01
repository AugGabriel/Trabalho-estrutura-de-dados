#ifndef _BD_PARTIDA_H
#define _BD_PARTIDA_H

#include <stdio.h>

#include "time.h"
#include "partida.h"
#include "bd_times.h"
#include "auxiliares_globais.h"

// Quantidade máxima de partidas permitida
#define MAX_PARTIDAS 100

// Enumerate para modos de pesquisa de time, na funcionalidade 2
typedef enum filtro_pesquisa_partida {
    TIME_MANDANTE,
    TIME_VISITANTE,
    AMBOS,
} FILTRO_PESQUISA_PARTIDA;

typedef struct bdpartidas BDPartidas;

BDPartidas *bdp_criar();

BDPartidas *bdp_criar_usando_arquivo(char nome_arquivo[], BDTimes *bdt);

void bdp_calcular_resultados(BDPartidas *bdp, BDTimes *bdt);

int bdp_quant_partidas(BDPartidas *bdp);

Partida *bdp_obter_por_index(BDPartidas *bdp, int i);

void *bdp_obter_por_id(BDPartidas *bdp, int id);

// Função usada para montar lista de partidas, a partir do modo de pesquisa e dos times para consultar
// Para cada partida, para cada time, se o time tiver jogado na partida, e na posição solicitada (mandante ou visitante), ele será adicionado à lista
LinkedList *bdp_encontrar_partidas(BDPartidas *bdp, LinkedList *times, const int modo);

// Remove o elemento da lista a partir do id
void bdp_remover_por_id(BDPartidas *bdp, int id);

// Função para desalocar a memória de todas as partidas
void bdp_encerrar(BDPartidas *bdp);

// Função para aplicar as alterações de partida no arquivo bd de partida
void bdp_salvar_em_arquivo(BDPartidas *bdp, char nome_arquivo[]);

#endif