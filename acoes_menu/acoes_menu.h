// Módulo para ações do menu escolhidas pelo usuário

#include "bd_time.h"
#include "bd_partida.h"

// Funcionalidade 1, para consultar e imprimir os times a partir do nome ou prefixo
void consultar_times(BDTime *bdt);

// Funcionalidade 2, para consultar partidas a partir do nome de um time
void consultar_partidas(BDTime *bdt, BDPartida *bdp);

// Funcionalidade 3, para atualizar uma partida
void atualizar_partida();

// Funcionalidade 4, para remoção de partida
void remover_partida(BDTime *bdt, BDPartida *bdp);

// Funcionalidade 5, para inserção de partida
void inserir_partida();

// Funcionalidade 6, para imprimir a tabela de classificação
void imprimir_tabela_classificacao(BDTime *bdt);