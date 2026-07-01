#include "bd_times.h"
#include "auxiliares_globais.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Macro para definir a quantidade de times
#define QUANT_TIMES 10

struct bdtimes {
    LinkedList *lista_times;
};

BDTimes *bdt_criar()
{
    BDTimes *bdt = (BDTimes *)malloc(sizeof(BDTimes));
    bdt->lista_times = ll_create();                             
    return bdt; 
}

BDTimes *bdt_criar_usando_arquivo(char nome_arquivo[]) {
    BDTimes *bdt = bdt_criar();
    
    FILE *arquivo = fopen(nome_arquivo, "r");
    
    // Validação do arquivo
    if (arquivo == NULL) {
        perror("Alocação de memória falhou");
        exit(EXIT_FAILURE);
    }

    // Cria um Time para cada linha do arquivo de texto
    for (int i = 0; i < QUANT_TIMES; i++) {
        int id;
        char *nome = (char*)malloc(15 * sizeof(char));
        inicializa_string(nome, 15);

        fscanf(arquivo, " %d,%s", &id, nome);

        ll_insert(bdt->lista_times, time_criar(id, nome), TYPE_TIME);
    }

    // Fecha o arquivo
    fclose(arquivo);
    
    return bdt;
}

int bdt_quant_times(BDTimes *bdt) {
    return ll_size(bdt->lista_times);
}

Time *bdt_obter_time(BDTimes *bdt, int i) {
    return ll_get(bdt->lista_times, i);
}

// Função auxiliar para montar prefixo, para consulta de time
char *_monta_prefixo(char *nome, const int tamanho) {
    char *prefixo = (char*)malloc((tamanho + 1) * sizeof(char));

    for (int i = 0; i < tamanho; i++) {
        prefixo[i] = nome[i];
    }
    prefixo[tamanho] = '\0';

    return prefixo;
}

// Função usada para montar lista de times a partir do nome ou do prefixo
LinkedList *bdt_encontrar_times(BDTimes *bdt, const char *nome) {
    LinkedList *resultados = ll_create();

    for (int i = 0; i < bdt_quant_times(bdt); i++) {
        Time *time_atual = bdt_obter_time(bdt, i);
        char *time_atual_nome = time_nome(time_atual);
        
        char *prefixo = _monta_prefixo(time_atual_nome, strlen(nome));
        
        if (
            string_comp_insensitive(time_nome(bdt_obter_time(bdt, i)), nome) == 0         // Entrada bate com o nome
            || string_comp_insensitive(prefixo, nome) == 0                        // Entrada bate com o prefixo
        ) {
            ll_insert(resultados, time_atual, TYPE_TIME);
        }

        free(prefixo);
    }

    return resultados;
}

void bdt_imprimir_times(BDTimes *bdt) {
    // Imprime o cabeçalho
    printf("%s\t%9s\t\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG");
    // Imprime a lista de times
    ll_print(bdt->lista_times);
}

// Funcionalidade para desalocar todos os times
void bdt_limpar(BDTimes *bdt) {
    ll_free(bdt->lista_times);
    free(bdt);
}
