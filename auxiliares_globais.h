#ifndef _AUXILIARES_GLOBAIS_H
#define _AUXILIARES_GLOBAIS_H

#include <string.h>
#include <stdio.h>

#define TAMANHO_MAX_ENTRADA 15

void inicializa_string(char *string, const int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        string[i] = '\0';
    }
}

#endif