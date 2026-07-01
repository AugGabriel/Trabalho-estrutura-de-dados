#include "linkedlist.h"
#include "acoes_menu.h"
#include "auxiliares_globais.h"
#include "bd_partidas.h"
#include "bd_times.h"
#include "time.h"
#include "partida.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Funções de inicialização do sistema
    BDTimes *bdt = bdt_criar_usando_arquivo(CAMINHO_BD_TIME);
    BDPartidas *bdp = bdp_criar_usando_arquivo(CAMINHO_BD_PARTIDA, bdt);

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
                atualizar_partida(bdt, bdp);
                break;
            case '4':
                remover_partida(bdt, bdp);
            break;
            case '5':
                inserir_partida();
                break;
            case '6':
                imprimir_tabela_classificacao(bdt, bdp);
                break;
            case 'Q':
            case 'q':
                printf("Obrigado pela preferência, volte sempre!\n");
                break;
            default:
                printf("Entrada inválida\n\n");
                break;
        }
    }

    // Aplicação das alterações no arquivo de partidas
    bdp_salvar_em_arquivo(bdp, CAMINHO_BD_PARTIDA);

    // Liberação de memória
    bdt_encerrar(bdt);
    bdp_encerrar(bdp);

    return 0;
}
