#include "bd_partidas.h"
#include <stdio.h>
#include <stdlib.h>

// Quantidade máxima de partidas permitida
#define MAX_PARTIDAS 100

struct bdpartidas {
    LinkedList *lista_partidas;
};

BDPartidas *bdp_criar()
{
    BDPartidas *bdp = (BDPartidas *)malloc(sizeof(BDPartidas));
    bdp->lista_partidas = ll_create();                             
    return bdp; 
}

// Função para cálculo dos resultados a partir dos dados das partidas
void bdp_calcular_resultados(BDPartidas *bdp, BDTimes *bdt) {
    // Primeiro, zera os times, para que os valores sejam recalculados
    bdt_zerar_times(bdt);
    
    for (int i = 0; i < bdp_quant_partidas(bdp); i++) {
        Partida *partida = bdp_obter_por_index(bdp, i);

        Time *time1 = partida_time(partida, 1);
        Time *time2 = partida_time(partida, 2);

        int gols_time1 = partida_gols(partida, 1);
        int gols_time2 = partida_gols(partida, 2);

        // Gols marcados
        time_definir_gols_marcados(time1, time_gols_marcados(time1) + gols_time1);
        time_definir_gols_marcados(time2, time_gols_marcados(time2) + gols_time2);
        
        // Gols sofridos
        time_definir_gols_sofridos(time1, time_gols_sofridos(time1) + gols_time2);
        time_definir_gols_sofridos(time2, time_gols_sofridos(time2) + gols_time1);
        
        if (gols_time1 == gols_time2) {       // Empate
            time_definir_empates(time1, time_empates(time1) + 1);
            time_definir_empates(time2, time_empates(time2) + 1);
        }
        else if (gols_time1 > gols_time2) {   // Vitória do time 1
            time_definir_vitorias(time1, time_vitorias(time1) + 1);
            time_definir_derrotas(time2, time_derrotas(time2) + 1);
        }
        else {                                // Vitória do time 2
            time_definir_vitorias(time2, time_vitorias(time2) + 1);
            time_definir_derrotas(time1, time_derrotas(time1) + 1);                              
        }
    }
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
            bdp_calcular_resultados(bdp, bdt);
            return bdp;
        }

        Partida *nova_partida = partida_criar(bdt, id, id_mandante, id_visitante, gols_mand, gols_visit);
        ll_append(bdp->lista_partidas, nova_partida, TYPE_PARTIDA);
    }

    // Fecha o arquivo
    fclose(arquivo);

    // Retorno do bdp
    return bdp;
}

void bdp_adicionar_partida(BDPartidas *bdp, BDTimes *bdt, int id_time1, int id_time2, int placar1, int placar2) {
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
}

int bdp_quant_partidas(BDPartidas *bdp) {
    return ll_size(bdp->lista_partidas);
}

Partida *bdp_obter_por_index(BDPartidas *bdp, int i) {
    return ll_get(bdp->lista_partidas, i);
}

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
    ll_remove(bdp->lista_partidas, bdp_obter_por_id(bdp, id));
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