#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "auxiliares_globais.h"
#include "time.h"
#include "bd_times.h"
#include "partida.h"
#include "bd_partidas.h"

#define TAMANHO_MAX_ENTRADA 15


// Funcionalidade 1, para consultar e imprimir os times a partir do nome ou prefixo
void consultar_times(BDTimes *bdt) {

    // Entrada do usuário
    char nome[TAMANHO_MAX_ENTRADA];
    inicializa_string(nome, TAMANHO_MAX_ENTRADA);

    printf("Digite o nome ou o apelido do time: ");
    scanf(" %s", nome);
    nome[TAMANHO_MAX_ENTRADA - 1] = '\0';
    
    // Validação da entrada
    if (nome[0] == '\0') {
        printf("Você não digitou nada...\n");
        return;
    }

    // Retorno da lista de ponteiros para times
    LinkedList *times = bdt_encontrar_times(bdt, nome);

    // Validação da lista
    if (ll_is_empty(times)) {
        printf("\nNenhum time encontrado\n\n");
        return;
    }

    // Impressão da lista
    ll_print(times);

    // Liberação de memória da lista alocada dinamicamente
    free(times);
}


// Funcionalidade 2, para consultar partidas a partir do nome de um time
void consultar_partidas(BDPartidas *bdp, BDTimes *bdt) {

    // Entrada do usuário
    char nome[TAMANHO_MAX_ENTRADA];
    inicializa_string(nome, TAMANHO_MAX_ENTRADA);

    printf("Digite o nome ou o apelido do time: ");
    scanf(" %s", nome);
    nome[TAMANHO_MAX_ENTRADA - 1] = '\0';

    // Validação da entrada
    if (nome[0] == '\0') {
        printf("Você não digitou nada...\n");
        return;
    }

    LinkedList *times = bdt_encontrar_times(bdt, nome);

    // Validação da lista de times
    if (ll_is_empty(times)) { 
        printf("\nTime não encontrado\n\n");
        return;
    }

    // Nova entrada do usuário
    int escolha;
    printf("Escolha o modo de consulta: \
        \n\t1) Por time mandante \
        \n\t2) Por time visitante \
        \n\t3) Por time mandante ou visitante \
        \n\t4) Retornar ao menu principal\n");
    scanf(" %d", &escolha);

    // Escolhe o modo de filtro
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

    // Chama a função de retornar partidas
    LinkedList *partidas = bdp_encontrar_partidas(bdp, times, modo);
    ll_free(times);

    if (ll_is_empty(partidas)) {
        printf("Nenhuma partida encontrada\n");
        return;
    }

    // Imprime os dados formatados em tabela
    printf("%s\t%9s\t\t\t%9s\n", "ID", "Time1", "Time2");
    for (int i = 0; i < ll_size(partidas); i++) {
        Partida *partida = ll_get(partidas, i);
        printf(
            "%d\t%9s\t%d\tx\t%d\t%9s\n",
            partida_id(partida),
            time_nome(partida_time(partida, 1)),
            partida_gols(partida, 1),
            partida_gols(partida, 2),
            time_nome(partida_time(partida, 2))
        );
    }
    printf("\n");
}


// Funcionalidade 3, para imprimir a tabela de classificação
void imprimir_tabela_classificacao(BDTimes *bdt) {
    printf("\nImprimindo classificação: \n");
    bdt_imprimir_times(bdt);
}


int main() {
   
    // Funções de inicialização do sistema
    BDTimes *bdt = bdt_criar_usando_arquivo("tabelas/times.csv");
    BDPartidas *bdp = bdp_criar_usando_arquivo("tabelas/partidas.csv", bdt);

    // Variável de entrada do usuário
    char escolha = '0';

    // Início do loop de escolhas do usuário
    while (escolha != 'Q' && escolha != 'q') {
        printf("Faça sua escolha: \
            \n\t1) Consultar time \
            \n\t2) Consultar partidas \
            \n\t3) Atualizar partida \
            \n\t4) Remover partida \
            \n\t5) Inserir partida \
            \n\t6) Imprimir tabela de classificação \
            \n\tQ) Sair\n");
        scanf(" %c", &escolha);

        switch(escolha) {
            case '1':
                consultar_times(bdt);
                break;
            case '2':
                consultar_partidas(bdp, bdt);
                break;
            case '3':
                printf("Estamos em obras para poder te atender melhor :)\n\n");
                break;
            case '4':
                printf("Estamos em obras para poder te atender melhor :)\n\n");
                break;
            case '5':
                printf("Estamos em obras para poder te atender melhor :)\n\n");
                break;
            case '6':
                imprimir_tabela_classificacao(bdt);
                break;
            case 'Q':
            case 'q':
                printf("Obrigado pela preferência, volte sempre!\n");
                return 0;
            default:
                printf("Entrada inválida\n\n");
                break;
        }
    }

    // Liberação de memória
    bdt_limpar(bdt);
    bdp_limpar(bdp);

    return 0;
}
