#include "bd_partidas.h"
#include <stdio.h>
#include <stdlib.h>

// Quantidade máxima de partidas permitida
#define MAX_PARTIDAS 100

// Banco de dados de partidas. Guarda todas as partidas em uma lista simplesmente encadeada
struct bdpartidas {
    LinkedList *lista_partidas;
};

BDPartidas *bdp_criar()
{
    BDPartidas *bdp = (BDPartidas *)malloc(sizeof(BDPartidas));
    bdp->lista_partidas = ll_create();                             
    return bdp; 
}

BDPartidas *bdp_criar_usando_arquivo(char nome_arquivo[], BDTimes *bdt) {
    BDPartidas *bdp = bdp_criar();
    
    FILE *arquivo = fopen(nome_arquivo, "r");

    // Validação do arquivo
    if (arquivo == NULL) {
        perror("Alocação de memória falhou");
        exit(EXIT_FAILURE);
    }

    // Cria uma Partida para cada linha do arquivo de texto
    for (int i = 0; i < MAX_PARTIDAS; i++) {
        int id;
        int id_mandante, id_visitante;
        int gols_mand, gols_visit;

        if (fscanf(
            arquivo, 
            " %d,%d,%d,%d,%d", 
            &id, 
            &id_mandante, 
            &id_visitante, 
            &gols_mand, 
            &gols_visit
        ) == EOF) {
            return bdp;
        }

        Partida *nova_partida = partida_criar(bdt, id, id_mandante, id_visitante, gols_mand, gols_visit);
        ll_append(bdp->lista_partidas, nova_partida, TYPE_PARTIDA);
        partida_aplicar_resultado(nova_partida, APLICAR_RESULTADO);
    }

    // Fecha o arquivo
    fclose(arquivo);

    // Retorno do bdp
    return bdp;
}

void bdp_adicionar_partida(BDPartidas *bdp, BDTimes *bdt, int id_time1, int id_time2, int placar1, int placar2) {
    // Gera o id da nova partida a partir do maior id já existente
    int maior_id = 0;
    for (int i = 0; i < bdp_quant_partidas(bdp); i++) {
        Partida *partida = bdp_obter_por_index(bdp, i);
        int id = partida_id(partida);
        if (partida_id(partida) > maior_id) {
            maior_id = id;
        }
    }
    Partida *nova_partida = partida_criar(bdt, maior_id+1, id_time1, id_time2, placar1, placar2);
    ll_append(bdp->lista_partidas, nova_partida, TYPE_PARTIDA);

    // Aplica o resultado da nova partida nas estatísticas dos times
    partida_aplicar_resultado(nova_partida, APLICAR_RESULTADO);
}

int bdp_quant_partidas(BDPartidas *bdp) {
    return ll_size(bdp->lista_partidas);
}

Partida *bdp_obter_por_index(BDPartidas *bdp, int i) {
    return ll_get(bdp->lista_partidas, i);
}

// Busca pela partida com o id informado
Partida *bdp_obter_por_id(BDPartidas *bdp, int id) {
    for (int i = 0; i < bdp_quant_partidas(bdp); i++) {
        Partida *partida = bdp_obter_por_index(bdp, i);
        if (partida_id(partida) == id) {
            return partida;
        }
    }
    return NULL;
}

// Função usada para montar lista de partidas, a partir do modo de pesquisa e dos times para consultar
// Para cada partida, para cada time, se o time tiver jogado na partida, e na posição solicitada (mandante ou visitante), ele será adicionado à lista
LinkedList *bdp_encontrar_partidas(BDPartidas *bdp, LinkedList *times, const int modo) {
    LinkedList *partidas = ll_create();

    for (int i = 0; i < bdp_quant_partidas(bdp); i++) {
        Partida *partida_atual = bdp_obter_por_index(bdp, i);
        
        for (int j = 0; j < ll_size(times); j++) { 
            Time *time_atual = ll_get(times, j);
            if (
                (modo != TIME_VISITANTE && partida_time(partida_atual, 1) == time_atual)    // Time mandante na partida
                || (modo != TIME_MANDANTE && partida_time(partida_atual, 2) == time_atual)  // Time visitante na partida
            ) {
                ll_append(partidas, partida_atual, TYPE_PARTIDA);
            }
        }
        
    }

    return partidas;
}

// Remove o elemento da lista a partir do id
void bdp_remover_por_id(BDPartidas *bdp, int id) {
    Partida *partida = bdp_obter_por_id(bdp, id);
    if (partida == NULL) {
        return;
    }

    // Reverte o resultado da partida nas estatísticas
    partida_aplicar_resultado(partida, REVERTER_RESULTADO);

    ll_remove(bdp->lista_partidas, partida);
    partida_limpar(partida);
}

// Função para desalocar a memória de todas as partidas
void bdp_encerrar(BDPartidas *bdp) {
    int apagar_informacoes = 1;
    ll_free(bdp->lista_partidas, apagar_informacoes);
    free(bdp);
}

// Função para aplicar as alterações de partida no arquivo bd de partida
void bdp_salvar_em_arquivo(BDPartidas *bdp, char nome_arquivo[]) {
    FILE *arquivo = fopen(nome_arquivo, "w");

    for (int i = 0; i < bdp_quant_partidas(bdp); i++) {
        Partida *partida = bdp_obter_por_index(bdp, i);

        fprintf(
            arquivo, 
            "%d,%d,%d,%d,%d\n", 
            partida_id(partida),
            time_id(partida_time(partida, 1)),
            time_id(partida_time(partida, 2)),
            partida_gols(partida, 1),
            partida_gols(partida, 2)
        );
    }

    fclose(arquivo);
}