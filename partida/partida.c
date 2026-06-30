#include "partida.h"
#include "time.h"
#include "bd_time.h"
#include <stdlib.h>
#include <stdio.h>

// Estrutura de partida
struct partida {
    int id;

    Time* time1;
    Time* time2;

    int gols_time1;
    int gols_time2;
};

int partida_id(Partida *p) {
    return p->id;
}

Time *partida_time(Partida *p, int numero_time) {
    if (numero_time == 1)
        return p->time1;
    if (numero_time == 2)
        return p->time2;
    else {
        perror("Opção inválida na obtenção de time da partida.");
        exit(EXIT_FAILURE);
    }
}

int partida_gols(Partida *p, int numero_time) {
    if (numero_time == 1)
        return p->gols_time1;
    if (numero_time == 2)
        return p->gols_time2;
    else {
        perror("Opção de time inválida na obtenção de gols da partida.");
        exit(EXIT_FAILURE);
    }
}

// Construtor de partida
Partida *partida_criar(
            const int id, 
            const int id_time1, const int id_time2, 
            const int gols_time1, const int gols_time2,
            BDTimes *bdt
    ) {

    // Alocação de memória
    Partida *partida = (Partida*)malloc(sizeof(Partida));

    // Validação da alocação de memória
    if (partida == NULL) {
        perror("Alocação de memória falhou");
        exit(EXIT_FAILURE);
    }

    // Inicialização
    partida->id = id;
    partida->time1 = bdt_obter_time(bdt, id_time1);
    partida->time2 = bdt_obter_time(bdt, id_time2);
    partida->gols_time1 = gols_time1;
    partida->gols_time2 = gols_time2;

    return partida;
}

// Impressão de partida
void imprimir_partida(Partida *partida) {
    printf(
        "%d\t%9s\t%d\tx\t%d\t%9s\n",
        partida->id,
        get_nome(partida->time1),
        partida->gols_time1,
        partida->gols_time2,
        get_nome(partida->time2)
    );
}

// Função para liberar memória alocada para partida
void partida_limpar(Partida *partida) {
    free(partida);
}