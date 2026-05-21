#ifndef _AUXILIARES_GLOBAIS_H
#define _AUXILIARES_GLOBAIS_H

#define TAMANHO_MAX_ENTRADA 15

void inicializa_string(char *string, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        string[i] = '\0';
    }
}

#endif