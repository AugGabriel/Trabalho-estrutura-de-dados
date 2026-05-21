#ifndef _BD_PARTIDA_H
#define _BD_PARTIDA_H

#include "partida.h"

#define _MAX_PARTIDAS 100

Partida *_partidas[_MAX_PARTIDAS];

Partida **lista_partidas() { return _partidas; }

enum filtro_pesquisa_partida {
    TIME_MANDANTE = 0,
    TIME_VISITANTE = 1,
    AMBOS = 2,
} FILTRO_PESQUISA_PARTIDA;

void carregar_dados_partidas() {
    // FILE *arquivo = fopen("partidas.csv", "r");
    FILE *arquivo = fopen("partidas_completo.csv", "r");

    if (arquivo == NULL) {
        // Implementação de erro, baseada em perror()
    }

    for (int i = 0; i < _MAX_PARTIDAS; i++) {
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
            return;
        }

        _partidas[i] = criar_partida(id, id_mandante, id_visitante, gols_mand, gols_visit);
    }

    fclose(arquivo);
}

// Função auxiliar usada para criar e inicializar lista vazia de partidas
Partida **_inicializa_lista_partidas() {
    Partida **partidas = (Partida**)malloc(_MAX_PARTIDAS * sizeof(Partida*));
    for (int i = 0; i < _MAX_PARTIDAS; i++) {
        partidas[i] = NULL;
    }
    return partidas;
}

// Função usada para montar lista de partidas, a partir do modo de pesquisa e dos times para consultar
// Para cada partida, para cada time, se o time tiver jogado na partida, e na posição solicitada (mandante ou visitante), ele será adicionado à lista
Partida **retornar_partidas(Time **times, int modo) {
    Partida **partidas = _inicializa_lista_partidas();
    int k = 0;

    for (int i = 0; i < _MAX_PARTIDAS && _partidas[i] != NULL; i++) {       // Aqui considera que _partidas[] passa a ter valores nulos a partir de certo ponto, não funciona se não for assim
        for (int j = 0; j < _QUANT_TIMES && times[j] != NULL; j++) {        // Mesma ideia aqui, considera que passa a ser nulo
            if (
                (modo != TIME_VISITANTE && _partidas[i]->time1 == times[j])    // Time mandante na partida
                || (modo != TIME_MANDANTE && _partidas[i]->time2 == times[j])  // Time visitante na partida
            ) {
                partidas[k++] = _partidas[i];
            }
        }
    }

    return partidas;
}

// Funcionalidade 2, para consultar partidas a partir do nome de um time
void consultar_partidas() {

    // Entrada do usuário
    char nome[TAMANHO_MAX_ENTRADA];
    inicializa_string(nome, TAMANHO_MAX_ENTRADA);

    printf("Digite o nome ou o apelido do time: ");
    scanf(" %s", nome);

    Time **times = retornar_times(nome);

    if (times[0] == NULL) { 
        printf("\nTime não encontrado\n\n");
        return;
    }

    int escolha;
    printf("Escolha o modo de consulta: \
        \n\t1) Por time mandante \
        \n\t2) Por time visitante \
        \n\t3) Por time mandante ou visitante \
        \n\t4) Retornar ao menu principal\n");
    scanf(" %d", &escolha);

    int modo;
    switch(escolha) {
        case 1:
            modo = TIME_MANDANTE;
            break;
        case 2:
            modo = TIME_VISITANTE;
            break;
        case 3:
            modo = AMBOS;
            break;
        case 4: 
            return;
        default:
            printf("Opção inválida\n");
            return;
    }

    Partida **partidas = retornar_partidas(times, modo);
    free(times);

    printf("ID\tTime1\t\t\tTime2\n");
    for (int i = 0; i < _MAX_PARTIDAS; i++) {
        Partida *partida = partidas[i];
        printf(
            "%d\t%s\t%d\tx\t%d\t%s\n",
            partida->id,
            partida->time1->nome,
            partida->gols_time1,
            partida->gols_time2,
            partida->time2->nome
        );
    }
    printf("\n");
}

// Função para desalocar a memória de todas as partidas
void apagar_partidas() {
    for (int i = 0; i < _MAX_PARTIDAS; i++) {
        apagar_partida(_partidas[i]);
    }
}

#endif