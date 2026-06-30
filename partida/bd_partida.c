#include "bd_partida.h"
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

// Função interna para cálculo dos resultados a partir dos dados carregados
void _calcular_resultados(BDPartidas *bdp, BDTimes *bdt) {
    for (int i = 0; i < bdp_quant_partidas(bdp); i++) {
        Partida *partida = bdp_obter_partida(bdp, i);

        Time *time1 = partida_time(partida, 1);
        Time *time2 = partida_time(partida, 2);

        int gols_time1 = partida_gols(partida, 1);
        int gols_time2 = partida_gols(partida, 2);

        // Gols marcados
        time_alterar_gols_marcados(time1, gols_time1);
        time_alterar_gols_marcados(time2, gols_time2);
        
        // Gols sofridos
        time_alterar_gols_sofridos(time1, gols_time2);
        time_alterar_gols_sofridos(time2, gols_time1);
        
        if (gols_time1 == gols_time2) {       // Empate
            time_alterar_empates(time1, 1);
            time_alterar_empates(time2, 1);
        }
        else if (gols_time1 > gols_time2) {   // Vitória do time 1
            time_alterar_vitorias(time1, 1);
            time_alterar_derrotas(time2, 1);
        }
        else {                                // Vitória do time 2
            time_alterar_vitorias(time2, 1);
            time_alterar_derrotas(time1, 1);                                
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
            _calcular_resultados(bdp, bdt);
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

// Função para aplicar as alterações de partida no arquivo bd de partida
void aplicar_alteracoes_partida(BDPartidas *bdp) {
    for (int i = 0; i < bdp_size(bdp); i++) {
        Partida *partida = bdp_get(bdp, i);
        FILE *bd = fopen(CAMINHO_BD_PARTIDA, 'w');

        fprintf(
            "%d,%d,%d,%d,%d\n", 
            partida_id(partida),
            partida_time(partida, 1),
            partida_time(partida, 2),
            partida_gols(partida, 1),
            partida_gols(partida, 2)
        );
    }
}