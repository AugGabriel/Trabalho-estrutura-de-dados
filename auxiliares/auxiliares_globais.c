#include "auxiliares_globais.h"

// Inicializa string com caracteres de final, para garantir que ela termine em algum momento
// O ideal seria que a entrada com o %s encerrasse a string com \0, porém o comportamento pareceu variar entre compiladores
void inicializa_string(char *string, const int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        string[i] = '\0';
    }
}

// Compara caracteres case-insensitive
int char_comp_insensitive(char chr1, char chr2) {
    if ((int)chr1 >= 65 && (int)chr1 <= 90) {
        chr1 += 32;
    }
    if ((int)chr2 >= 65 && (int)chr2 <= 90) {
        chr2 += 32;
    }

    if (chr1 > chr2) { 
        // Maior
        return 1;
    }
    else if (chr1 < chr2) {
        // Menor
        return -1;
    }
    // Igual
    return 0;
}

// Compara strings case-insensitive
int string_comp_insensitive(const char *str1, const char *str2) {
    int i = 0, j = 0;

    while (str1[i] != '\0' && str2[j] != '\0') {
        int cmp = char_comp_insensitive(str1[i], str2[j]);
        if (cmp > 0 || cmp < 0) {
            return cmp;
        }
        i++;
        j++;
    }
    return 0;
}