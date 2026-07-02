#ifndef _AUXILIARES_GLOBAIS_H
#define _AUXILIARES_GLOBAIS_H

#include <string.h>
#include <stdio.h>

// Caminho dos arquivos de bd
#define CAMINHO_BD_PARTIDA "tabelas/partidas.csv"
#define CAMINHO_BD_TIME "tabelas/times.csv"

// Define o tamanho máximo da entrada do usuário
#define TAMANHO_MAX_ENTRADA 15

/**
 * Compara dois caracteres de forma case-insensitive.
 *
 * @param chr1 - Primeiro caractere.
 * @param chr2 - Segundo caractere.
 * @return     - 1 se chr1 > chr2, -1 se chr1 < chr2, 0 se iguais.
 */
int char_comp_insensitive(char chr1, char chr2);

/**
 * Compara duas strings de forma case-insensitive.
 *
 * @param str1 - Primeira string.
 * @param str2 - Segunda string.
 * @return     - Diferença do primeiro caractere distinto, ou 0 se iguais até o
 *               fim de uma delas.
 */
int string_comp_insensitive(const char *str1, const char *str2);

#endif
