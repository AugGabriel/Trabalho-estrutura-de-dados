#ifndef _BD_PARTIDA_H
#define _BD_PARTIDA_H

#include "time.h"
#include "partida.h"
#include "bd_time.h"

// Quantidade máxima de partidas permitida
#define MAX_PARTIDAS 100

// Função para acesso à lista de partidas, por parte dos outros módulos
Partida **lista_partidas();

// Função para carregar os dados do arquivo de texto para a lista de partidas
void carregar_dados_partidas();

// Função auxiliar usada para criar e inicializar lista vazia de partidas
Partida **_inicializa_lista_partidas();

// Função usada para montar lista de partidas, a partir do modo de pesquisa e dos times para consultar
// Para cada partida, para cada time, se o time tiver jogado na partida, e na posição solicitada (mandante ou visitante), ele será adicionado à lista
Partida **retornar_partidas(Time **times, const int modo);

// Funcionalidade 2, para consultar partidas a partir do nome de um time
void consultar_partidas();

// Função para desalocar a memória de todas as partidas
void apagar_partidas();

#endif