// Módulo para ações do menu escolhidas pelo usuário

#include <stdlib.h>

#include "bd_times.h"
#include "bd_partidas.h"

// Funcionalidade 1, para consultar e imprimir os times a partir do nome ou prefixo
void consultar_times(BDTimes *bdt);

// Funcionalidade 2, para consultar partidas a partir do nome de um time
int consultar_partidas(BDPartidas *bdp, BDTimes *bdt);

// Funcionalidade 3, para atualizar uma partida
void atualizar_partida(BDTimes *bdt, BDPartidas *bdp);

// Funcionalidade 4, para remoção de partida
void remover_partida(BDTimes *bdt, BDPartidas *bdp);

// Funcionalidade 5, para inserção de partida
void inserir_partida();

// Funcionalidade 6, para imprimir a tabela de classificação
void imprimir_tabela_classificacao(BDTimes *bdt);