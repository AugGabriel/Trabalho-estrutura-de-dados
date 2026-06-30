#include "partida.h"

// Estrutura de partida
struct partida {
    int id;

    Time* time1;
    Time* time2;

    int gols_time1;
    int gols_time2;
};

// Atributos de partida
int get_partida_id(Partida *partida) { return partida->id; }
Time *get_time1(Partida *partida) { return partida->time1; }
Time *get_time2(Partida *partida) { return partida->time2; }
int get_gols_time1(Partida *partida) { return partida->gols_time1; }
int get_gols_time2(Partida *partida) { return partida->gols_time2; }

void set_partida_id(Partida *partida, int id) { partida->id = id; }
void set_time1(Partida *partida, Time *time) { partida->time1 = time; }
void set_time2(Partida *partida, Time *time) { partida->time1 = time; }
void set_gols_time1(Partida *partida, int gols) { partida->gols_time1 = gols; }
void set_gols_time2(Partida *partida, int gols) { partida->gols_time2 = gols; }

// Construtor de partida
Partida *criar_partida(
            BDTime *bdt, const int id, 
            const int id_time1, const int id_time2, 
            const int gols_time1, const int gols_time2
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
    partida->time1 = bdt_get(bdt, id_time1);
    partida->time2 = bdt_get(bdt, id_time2);
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
void apagar_partida(Partida *partida) {
    free(partida);
}