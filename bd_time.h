#ifndef _BD_TIME_H
#define _BD_TIME_H

#include <string.h>

#include "time.h"
#include "auxiliares_globais.h"

// Macro para definir a quantidade de times
#define QUANT_TIMES 10

// Função para acessar valores da lista privada
Time **lista_times();

// Função que traz os dados do arquivo de texto para a lista _times
void carregar_dados_times();

// Função usada para montar lista de times a partir do nome ou do prefixo
Time **retornar_times(const char *nome);

// Função para imprimir vários times em sequência, com cabeçalho
void imprimir_times(Time **times);

// Funcionalidade 1, para consultar e imprimir os times a partir do nome ou prefixo
void consultar_times();

// Funcionalidade para desalocar todos os times
void apagar_times();

#endif