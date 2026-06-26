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

// TODO:
//void TODO_USE_AS_REFERENCE_THEN_DELETE_calcular_resultados(BDPartidas *bdp) {
//    for (int i = 0; i < bdp_quant_partidas(bdp); i++) {
//        Partida *partida = bdp_obter_partida(bdp, i);
//
//        Time *time1 = partida->time1;
//        Time *time2 = partida->time2;
//
//        // Gols marcados
//        time1->gols_marcados += partida->gols_time1;
//        time2->gols_marcados += partida->gols_time2;
//
//        // Gols sofridos
//        time1->gols_sofridos += partida->gols_time2;
//        time2->gols_sofridos += partida->gols_time1;
//
//        if (partida->gols_time1 == partida->gols_time2) {       // Empate
//            time1->empates++;
//            time2->empates++;
//        }
//        else if (partida->gols_time1 > partida->gols_time2) {   // Vitória do time 1
//            time1->vitorias++;
//            time2->derrotas++;
//        }
//        else {                                                  // Vitória do time 2
//            time1->derrotas++;
//            time2->vitorias++;
//        }
//    }
//}

// Função usada para montar lista de partidas, a partir do modo de pesquisa e dos times para consultar
// Para cada partida, para cada time, se o time tiver jogado na partida, e na posição solicitada (mandante ou visitante), ele será adicionado à lista
LinkedList *bdp_encontrar_partidas(BDPartidas *bdp, LinkedList *times, const int modo);

// Função para desalocar a memória de todas as partidas
void bdp_limpar(BDPartidas *bdp);

#endif