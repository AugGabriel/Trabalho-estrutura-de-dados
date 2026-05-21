#ifndef _TABELA_CLASSIFICACAO_H
#define _TABELA_CLASSIFICACAO_H

#include "time.h"
#include "partida.h"
#include "bd_partida.h"

void calcular_resultados() {
    for (int i = 0; i < _MAX_PARTIDAS && lista_partidas()[i] != NULL; i++) {
        Partida *partida = _partidas[i];

        Time *time1 = partida->time1;
        Time *time2 = partida->time2;

        // Gols marcados
        time1->gols_marcados += partida->gols_time1;
        time2->gols_marcados += partida->gols_time2;

        // Gols sofridos
        time1->gols_sofridos += partida->gols_time2;
        time2->gols_sofridos += partida->gols_time1;

        if (partida->gols_time1 == partida->gols_time2) {       // Empate
            time1->empates++;
            time2->empates++;
        }
        else if (partida->gols_time1 > partida->gols_time2) {   // Vitória do time 1
            time1->vitorias++;
            time2->derrotas++;
        }
        else {                                                  // Vitória do time 2
            time1->derrotas++;
            time2->vitorias++;
        }
    }
}

// Funcionalidade 3, para imprimir a tabela de classificação
void imprimir_tabela_classificacao() {
    printf("\nImprimindo classificação: \n");
    imprimir_times(_times);
}

#endif