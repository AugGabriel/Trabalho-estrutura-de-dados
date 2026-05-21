#ifndef _AUXILIARES_GLOBAIS_H
#define _AUXILIARES_GLOBAIS_H

#include <string.h>
#include <stdio.h>

// Define o tamanho máximo da entrada do usuário
#define TAMANHO_MAX_ENTRADA 15

// Inicializa string com caracteres de final, para garantir que ela termine em algum momento
// O ideal seria que a entrada com o %s encerrasse a string com \0, porém o comportamento pareceu variar entre compiladores
void inicializa_string(char *string, const int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        string[i] = '\0';
    }
}

#endif