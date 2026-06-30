#ifndef _BD_TIME_H
#define _BD_TIME_H

#include <string.h>

#include "time.h"
#include "auxiliares_globais.h"

// Macro para definir a quantidade de times
#define QUANT_TIMES 10

// Definição de BDTimeNode
typedef struct bd_time_node BDTimeNode;

// Definição de BDTime
typedef struct bd_time BDTime;

// Criação de BDTime
BDTime *bdt_create();

// Adição de elemento ao final de BDTime. Retorna o index aonde o elemento foi adicionado
int bdt_append(BDTime *bdt, Time *info);

// Obtenção de elemento de BDTime. Se index for fora de BDTime, retorno é NULL
Time *bdt_get(BDTime *bdt, int index);

// Apagar BDTime, seus nós e as partidas dentro
void bdt_free(BDTime *bdp);

// Função que traz os dados do arquivo de texto para a lista de times
BDTime *carregar_dados_times();

// Função usada para montar lista de times a partir do nome ou do prefixo
BDTime *retornar_times(BDTime *bdt, const char *nome);

// Função para imprimir vários times em sequência, com cabeçalho
void imprimir_times(BDTime *bdt);

// Funcionalidade 1, para consultar e imprimir os times a partir do nome ou prefixo
void consultar_times(BDTime *bdt);

#endif