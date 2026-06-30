#ifndef _TABELA_CLASSIFICACAO_H
#define _TABELA_CLASSIFICACAO_H

#include "time.h"
#include "partida.h"
#include "bd_partida.h"

void calcular_resultados(BDPartida *bdp);

// Funcionalidade 3, para imprimir a tabela de classificação
void imprimir_tabela_classificacao();

#endif