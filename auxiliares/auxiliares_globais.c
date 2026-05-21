#include "auxiliares_globais.h"

// Inicializa string com caracteres de final, para garantir que ela termine em algum momento
// O ideal seria que a entrada com o %s encerrasse a string com \0, porém o comportamento pareceu variar entre compiladores
void inicializa_string(char *string, const int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        string[i] = '\0';
    }
}