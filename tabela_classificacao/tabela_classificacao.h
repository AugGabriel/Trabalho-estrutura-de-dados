#ifndef _TABELA_CLASSIFICACAO_H
#define _TABELA_CLASSIFICACAO_H

#include "time.h"
#include "partida.h"
#include "bd_partida.h"

void tabela_classificacao_carregar(BDPartida *bdp);

// Funcionalidade 3, para imprimir a tabela de classificação
void imprimir_tabela_classificacao(BDTime *bdt);

#endif