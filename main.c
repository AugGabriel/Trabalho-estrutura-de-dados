#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "acoes_menu.h"
#include "auxiliares_globais.h"
#include "bd_partida.h"
#include "bd_time.h"
#include "partida.h"
#include "tabela_classificacao.h"
#include "time.h"

int main() {

    // Funções de inicialização do sistema
    BDTime *bdt = bdt_create();
    bdt_carregar_dados(bdt);

    BDPartida *bdp = bdp_create();
    bdp_carregar_dados(bdp, bdt);

    tabela_classificacao_carregar(bdp);

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
                consultar_partidas(bdt, bdp);
                break;
            case '3':
                atualizar_partida();
                break;
            case '4':
                remover_partida(bdt, bdp);
            break;
            case '5':
                inserir_partida();
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
    bdt_end(bdt);
    bdp_end(bdp);

    return 0;
}