#include "partida.h"
#include "time.h"
#include "bd_times.h"
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

// Construtor de partida
Partida *partida_criar(
        BDTimes *bdt,
        const int id, 
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
    partida->time1 = bdt_obter_por_id(bdt, id_time1);
    partida->time2 = bdt_obter_por_id(bdt, id_time2);
    partida->gols_time1 = gols_time1;
    partida->gols_time2 = gols_time2;

    return partida;
}


// Getters
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

// Setters
void partida_definir_gols(Partida *p, int numero_time, int gols) {
    if (numero_time == 1) {
        p->gols_time1 = gols;
    }
    else if (numero_time == 2) {
        p->gols_time2 = gols;
    }
    else {
        perror("Opção de time inválida na definição de gols da partida.");
        exit(EXIT_FAILURE);
    }
}

// Aplica ou reverte a contribuição da partida nas estatísticas dos dois times
void partida_aplicar_resultado(Partida *p, ModoResultado modo) {
    // Obter os times da partida
    Time *time1 = p->time1;
    Time *time2 = p->time2;
    
    // Obter os gols de cada time nessa partida
    int gols_time1 = p->gols_time1;
    int gols_time2 = p->gols_time2;
    
    // Determina se o resultado da partida deve ser aplicado ou revertido das estatísticas
    int sinal;
    if (modo == APLICAR_RESULTADO) {
        sinal = +1;
    } else if (modo == REVERTER_RESULTADO) {
        sinal = -1;
    }    

    // Gols marcados e sofridos
    time_definir_gols_marcados(time1, time_gols_marcados(time1) + sinal * gols_time1);
    time_definir_gols_marcados(time2, time_gols_marcados(time2) + sinal * gols_time2);
    time_definir_gols_sofridos(time1, time_gols_sofridos(time1) + sinal * gols_time2);
    time_definir_gols_sofridos(time2, time_gols_sofridos(time2) + sinal * gols_time1);

    // Empate, vitória ou derrota
    if (gols_time1 == gols_time2) {           // Empate
        time_definir_empates(time1, time_empates(time1) + sinal);
        time_definir_empates(time2, time_empates(time2) + sinal);
    }
    else if (gols_time1 > gols_time2) {       // Vitória do time 1
        time_definir_vitorias(time1, time_vitorias(time1) + sinal);
        time_definir_derrotas(time2, time_derrotas(time2) + sinal);
    }
    else {                                    // Vitória do time 2
        time_definir_vitorias(time2, time_vitorias(time2) + sinal);
        time_definir_derrotas(time1, time_derrotas(time1) + sinal);
    }
}

// Impressão de partida
void partida_imprimir(Partida *partida) {
    printf(
        "%d\t%9s\t%d\tx\t%d\t%9s\n",
        partida->id,
        time_nome(partida->time1),
        partida->gols_time1,
        partida->gols_time2,
        time_nome(partida->time2)
    );
}

// Função para liberar memória alocada para partida
void partida_limpar(Partida *partida) {
    free(partida);
}