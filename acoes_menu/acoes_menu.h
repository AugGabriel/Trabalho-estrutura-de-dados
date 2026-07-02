// Módulo para ações do menu escolhidas pelo usuário

#include <stdlib.h>

#include "bd_times.h"
#include "bd_partidas.h"

/**
 * Funcionalidade 1: consulta times pelo nome ou prefixo e imprime os encontrados.
 *
 * @param bdt - Banco de dados de times.
 */
void consultar_times(BDTimes *bdt);

/**
 * Funcionalidade 2: consulta e imprime as partidas de um time, filtradas por
 * mandante, visitante ou ambos. Também é reutilizada pelas funcionalidades 3 e 4
 * para o usuário escolher a partida.
 *
 * @param bdp - Banco de dados de partidas.
 * @param bdt - Banco de dados de times.
 * @return    - 1 se a consulta foi bem-sucedida, 0 caso contrário.
 */
int consultar_partidas(BDPartidas *bdp, BDTimes *bdt);

/**
 * Funcionalidade 3: atualiza os placares de uma partida escolhida.
 *
 * @param bdt - Banco de dados de times.
 * @param bdp - Banco de dados de partidas.
 */
void atualizar_partida(BDTimes *bdt, BDPartidas *bdp);

/**
 * Funcionalidade 4: remove uma partida escolhida, após confirmação.
 *
 * @param bdt - Banco de dados de times.
 * @param bdp - Banco de dados de partidas.
 */
void remover_partida(BDTimes *bdt, BDPartidas *bdp);

/**
 * Funcionalidade 5: insere uma nova partida a partir dos dados digitados.
 *
 * @param bdp - Banco de dados de partidas.
 * @param bdt - Banco de dados de times.
 */
void inserir_partida(BDPartidas *bdp, BDTimes *bdt);

/**
 * Funcionalidade 6: imprime a tabela de classificação dos times.
 *
 * @param bdt - Banco de dados de times.
 * @param bdp - Banco de dados de partidas.
 */
void imprimir_tabela_classificacao(BDTimes *bdt, BDPartidas *bdp);
