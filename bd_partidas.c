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

        Partida *nova_partida = partida_criar(id, id_mandante, id_visitante, gols_mand, gols_visit, bdt);
        ll_insert(bdp->lista_partidas, nova_partida, TYPE_PARTIDA);
    }

    // Fecha o arquivo
    fclose(arquivo);
}

int bdp_quant_partidas(BDPartidas *bdp) {
    return ll_size(bdp->lista_partidas);
}

Partida *bdp_obter_partida(BDPartidas *bdp, int i) {
    return ll_get(bdp->lista_partidas, i);
}

// TODO:
//void TODO_USE_AS_REFERENCE_THEN_DELETE_calcular_resultados(BDPartidas *bdp) {
//    for (int i = 0; i < bdp_quant_partidas(bdp); i++) {
//        Partida *partida = bdp_obter_partida(bdp, i);
//
//        Time *time1 = partida->time1;
//        Time *time2 = partida->time2;
//
//        // Gols marcados
//        time1->gols_marcados += partida->gols_time1;
//        time2->gols_marcados += partida->gols_time2;
//
//        // Gols sofridos
//        time1->gols_sofridos += partida->gols_time2;
//        time2->gols_sofridos += partida->gols_time1;
//
//        if (partida->gols_time1 == partida->gols_time2) {       // Empate
//            time1->empates++;
//            time2->empates++;
//        }
//        else if (partida->gols_time1 > partida->gols_time2) {   // Vitória do time 1
//            time1->vitorias++;
//            time2->derrotas++;
//        }
//        else {                                                  // Vitória do time 2
//            time1->derrotas++;
//            time2->vitorias++;
//        }
//    }
//}

// Função usada para montar lista de partidas, a partir do modo de pesquisa e dos times para consultar
// Para cada partida, para cada time, se o time tiver jogado na partida, e na posição solicitada (mandante ou visitante), ele será adicionado à lista
LinkedList *bdp_encontrar_partidas(BDPartidas *bdp, LinkedList *times, const int modo) {
    LinkedList *partidas = ll_create();

    for (int i = 0; i < bdp_quant_partidas(bdp); i++) {       // Aqui considera que _partidas[] passa a ter valores nulos a partir de certo ponto, não funciona se não for assim
        Partida *partida_atual = bdp_obter_partida(bdp, i);
        
        for (int j = 0; j < ll_size(times); j++) {        // Mesma ideia aqui, considera que passa a ser nulo
            Time *time_atual = ll_get(times, j);
            if (
                (modo != TIME_VISITANTE && partida_time(partida_atual, 1) == time_atual)    // Time mandante na partida
                || (modo != TIME_MANDANTE && partida_time(partida_atual, 2) == time_atual)  // Time visitante na partida
            ) {
                ll_insert(partidas, partida_atual, TYPE_PARTIDA);
            }
        }
        
    }

    return partidas;
}

// Função para desalocar a memória de todas as partidas
void bdp_limpar(BDPartidas *bdp) {
    ll_free(bdp->lista_partidas);
    free(bdp);
}