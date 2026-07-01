#ifndef _AUXILIARES_GLOBAIS_H
#define _AUXILIARES_GLOBAIS_H

#include <string.h>
#include <stdio.h>

// Caminho dos arquivos de bd
#define CAMINHO_BD_PARTIDA "tabelas/partidas.csv"
#define CAMINHO_BD_TIME "tabelas/times.csv"

// Define o tamanho máximo da entrada do usuário
#define TAMANHO_MAX_ENTRADA 15

// Inicializa string com caracteres de final, para garantir que ela termine em algum momento
// O ideal seria que a entrada com o %s encerrasse a string com \0, porém o comportamento pareceu variar entre compiladores
void inicializa_string(char *string, const int tamanho);

// Compara caracteres case-insensitive
int char_comp_insensitive(char chr1, char chr2);

// Compara strings case-insensitive
int string_comp_insensitive(const char *str1, const char *str2);

// Compara caracteres case-insensitive
int char_comp_insensitive(char chr1, char chr2);

// Compara strings case-insensitive
int string_comp_insensitive(const char *str1, const char *str2);

// Compara caracteres case-insensitive
int char_comp_insensitive(char chr1, char chr2);

// Compara strings case-insensitive
int string_comp_insensitive(const char *str1, const char *str2);

#endif