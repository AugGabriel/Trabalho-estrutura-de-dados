#ifndef BDTIMES_H
#define BDTIMES_H

#include "linkedlist.h"
#include "time.h"

// Banco de dados de times
typedef struct bdtimes BDTimes;

/**
 * Cria um banco de dados de times vazio.
 *
 * @return - Ponteiro para o BDTimes criado.
 */
BDTimes *bdt_criar();

/**
 * Cria um banco de dados de times a partir de um arquivo.
 *
 * @param nome_arquivo - Caminho do arquivo de times.
 * @return             - Ponteiro para o BDTimes preenchido.
 */
BDTimes *bdt_criar_usando_arquivo(char nome_arquivo[]);

/**
 * Retorna a quantidade de times cadastrados.
 *
 * @param bdt - Ponteiro para o banco de dados de times.
 * @return    - Número de times.
 */
int bdt_quant_times(BDTimes *bdt);

/**
 * Obtém um time pela sua posição na lista.
 *
 * @param bdt - Ponteiro para o banco de dados de times.
 * @param i   - Índice (posição) do time.
 * @return    - Ponteiro para o time na posição indicada.
 */
Time *bdt_obter_por_index(BDTimes *bdt, int i);

/**
 * Obtém um time pelo seu id.
 *
 * @param bdt - Ponteiro para o banco de dados de times.
 * @param id  - Id do time procurado.
 * @return    - Ponteiro para o time, ou NULL se não existir.
 */
Time *bdt_obter_por_id(BDTimes *bdt, int id);

char *_monta_prefixo(char *nome, const int tamanho);

/**
 * Monta uma lista com os times cujo nome ou prefixo corresponde à busca
 * (case-insensitive).
 *
 * @param bdt  - Ponteiro para o banco de dados de times.
 * @param nome - Nome ou prefixo a procurar.
 * @return     - Lista (possivelmente vazia) com os times encontrados.
 */
LinkedList *bdt_encontrar_times(BDTimes *bdt, const char *nome);

/**
 * Imprime a tabela de classificação (cabeçalho e lista de todos os times).
 *
 * @param bdt - Ponteiro para o banco de dados de times.
 */
void bdt_imprimir_times(BDTimes *bdt);

/**
 * Libera a memória de todos os times e do próprio banco de dados.
 *
 * @param bdt - Ponteiro para o banco de dados de times.
 */
void bdt_encerrar(BDTimes *bdt);

#endif
