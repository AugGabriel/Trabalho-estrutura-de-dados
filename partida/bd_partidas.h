#ifndef _BD_PARTIDA_H
#define _BD_PARTIDA_H

#include <stdio.h>

#include "time.h"
#include "partida.h"
#include "bd_times.h"
#include "auxiliares_globais.h"

// Quantidade máxima de partidas permitida
#define MAX_PARTIDAS 100

// Modos de filtro da consulta de partidas (funcionalidade 2): considerar o time como mandante, como visitante, ou em qualquer das duas posições
typedef enum filtro_pesquisa_partida {
    TIME_MANDANTE,
    TIME_VISITANTE,
    AMBOS,
} FILTRO_PESQUISA_PARTIDA;

// Banco de dados de partidas: guarda todas as partidas em uma lista simplesmente encadeada
typedef struct bdpartidas BDPartidas;

/**
 * Cria um banco de dados de partidas vazio.
 *
 * @return - Ponteiro para o BDPartidas criado.
 */
BDPartidas *bdp_criar();

/**
 * Cria um banco de dados de partidas a partir de um arquivo) e aplica o resultado de cada partida lida nas estatísticas dos times.
 *
 * @param nome_arquivo - Caminho do arquivo de partidas.
 * @param bdt          - Banco de dados de times (para resolver os times e
 *                       acumular as estatísticas).
 * @return             - Ponteiro para o BDPartidas preenchido.
 */
BDPartidas *bdp_criar_usando_arquivo(char nome_arquivo[], BDTimes *bdt);

/**
 * Cria uma nova partida (com id gerado automaticamente), adiciona ao banco e
 * aplica o seu resultado nas estatísticas dos times.
 *
 * @param bdp      - Banco de dados de partidas.
 * @param bdt      - Banco de dados de times.
 * @param id_time1 - Id do time 1 (mandante).
 * @param id_time2 - Id do time 2 (visitante).
 * @param placar1  - Gols do time 1.
 * @param placar2  - Gols do time 2.
 */
void bdp_adicionar_partida(BDPartidas *bdp, BDTimes *bdt, int id_time1, int id_time2, int placar1, int placar2);

/**
 * Retorna a quantidade de partidas cadastradas.
 *
 * @param bdp - Banco de dados de partidas.
 * @return    - Número de partidas.
 */
int bdp_quant_partidas(BDPartidas *bdp);

/**
 * Obtém uma partida pela sua posição na lista.
 *
 * @param bdp - Banco de dados de partidas.
 * @param i   - Índice (posição) da partida.
 * @return    - Ponteiro para a partida na posição indicada.
 */
Partida *bdp_obter_por_index(BDPartidas *bdp, int i);

/**
 * Obtém uma partida pelo seu id.
 *
 * @param bdp - Banco de dados de partidas.
 * @param id  - Id da partida procurada.
 * @return    - Ponteiro para a partida, ou NULL se não existir.
 */
Partida *bdp_obter_por_id(BDPartidas *bdp, int id);

/**
 * Monta uma lista com as partidas em que algum dos times informados jogou, na
 * posição pedida pelo modo. Para cada partida, para cada time, se o time tiver
 * jogado na partida e na posição solicitada (mandante ou visitante), ela é
 * adicionada à lista.
 *
 * @param bdp   - Banco de dados de partidas.
 * @param times - Lista de times de interesse.
 * @param modo  - Filtro de posição (TIME_MANDANTE, TIME_VISITANTE ou AMBOS).
 * @return      - Lista (possivelmente vazia) com as partidas encontradas.
 */
LinkedList *bdp_encontrar_partidas(BDPartidas *bdp, LinkedList *times, const int modo);

/**
 * Remove a partida de id informado, revertendo o seu resultado das estatísticas dos times e liberando a sua memória.
 *
 * @param bdp - Banco de dados de partidas.
 * @param id  - Id da partida a remover.
 */
void bdp_remover_por_id(BDPartidas *bdp, int id);

/**
 * Libera a memória de todas as partidas e do próprio banco de dados.
 *
 * @param bdp - Banco de dados de partidas.
 */
void bdp_encerrar(BDPartidas *bdp);

/**
 * Grava todas as partidas de volta no arquivo, aplicando as alterações feitas
 * durante a execução.
 *
 * @param bdp          - Banco de dados de partidas.
 * @param nome_arquivo - Caminho do arquivo de destino.
 */
void bdp_salvar_em_arquivo(BDPartidas *bdp, char nome_arquivo[]);

#endif
