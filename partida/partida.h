#ifndef PARTIDA_H
#define PARTIDA_H

#include "time.h"
#include "bd_times.h"

// Estrutura de partida
typedef struct partida Partida;

/**
 * Cria uma partida, determinando os times pelos seus ids no banco de dados.
 *
 * @param bdt        - Banco de dados de times (para localizar os times pelo id).
 * @param id         - Identificador da partida.
 * @param id_time1   - Id do time 1 (mandante).
 * @param id_time2   - Id do time 2 (visitante).
 * @param gols_time1 - Gols do time 1.
 * @param gols_time2 - Gols do time 2.
 * @return           - Ponteiro para a partida criada.
 */
Partida *partida_criar(
        BDTimes *bdt,
        const int id,
        const int id_time1, const int id_time2,
        const int gols_time1, const int gols_time2
);

// Getters
int partida_id(Partida *p);
Time *partida_time(Partida *p, int numero_time);   // numero_time: 1 (mandante) ou 2 (visitante)
int partida_gols(Partida *p, int numero_time);     // numero_time: 1 (mandante) ou 2 (visitante)

// Setters
void partida_definir_gols(Partida *p, int numero_time, int gols);

// Modo de operação de partida_aplicar_resultado: somar ou subtrair a contribuição da partida nas estatísticas dos times
typedef enum {
    APLICAR_RESULTADO,
    REVERTER_RESULTADO,
} ModoResultado;

/**
 * Aplica ou reverte a contribuição da partida nas estatísticas dos dois times.
 *
 * @param p    - Ponteiro para a partida.
 * @param modo - APLICAR_RESULTADO para somar, REVERTER_RESULTADO para subtrair.
 */
void partida_aplicar_resultado(Partida *p, ModoResultado modo);

/**
 * Imprime uma linha com os dados da partida.
 *
 * @param partida - Ponteiro para a partida a ser impressa.
 */
void partida_imprimir(Partida *partida);

/**
 * Libera a memória alocada para a partida.
 *
 * @param partida - Ponteiro para a partida a ser liberada.
 */
void partida_limpar(Partida *partida);

#endif
