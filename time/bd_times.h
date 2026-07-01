#ifndef BDTIMES_H
#define BDTIMES_H

#include "linkedlist.h"
#include "time.h"

typedef struct bdtimes BDTimes;

BDTimes *bdt_criar();

BDTimes *bdt_criar_usando_arquivo(char nome_arquivo[]);

int bdt_quant_times(BDTimes *bdt);

Time *bdt_obter_por_index(BDTimes *bdt, int i);

// Obtém um time pelo seu id (independe da ordem de inserção na lista)
Time *bdt_obter_por_id(BDTimes *bdt, int id);

// Função auxiliar para montar prefixo, para consulta de time
char *_monta_prefixo(char *nome, const int tamanho);

// Função usada para montar lista de times a partir do nome ou do prefixo
LinkedList *bdt_encontrar_times(BDTimes *bdt, const char *nome);

void bdt_imprimir_times(BDTimes *bdt);

// Funcionalidade para desalocar todos os times
void bdt_encerrar(BDTimes *bdt);

#endif
