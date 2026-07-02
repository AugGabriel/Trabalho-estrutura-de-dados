#include "auxiliares_globais.h"

// Compara caracteres case-insensitive
int char_comp_insensitive(char chr1, char chr2) {
    // Converte maiúsculas ('A'..'Z' = 65..90) para minúsculas somando 32,
    // para que a comparação ignore a diferença de caixa
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

    // Percorre em paralelo até o fim de uma das strings e para no primeiro
    // caractere diferente. Se chegar ao fim de alguma sem diferença, retorna 0
    // (dessa forma, strings iguais até o fim da menor são consideradas iguais)
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