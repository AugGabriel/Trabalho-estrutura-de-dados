#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "auxiliares_globais.h"
#include "time.h"
#include "bd_time.h"
#include "partida.h"
#include "bd_partida.h"
#include "tabela_classificacao.h"

int main() {

    // Funções de inicialização do sistema
    carregar_dados_times();
    carregar_dados_partidas();
    calcular_resultados();

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
                consultar_times();
                break;
            case '2':
                consultar_partidas();
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
                imprimir_tabela_classificacao();
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

    apagar_times();
    apagar_partidas();

    return 0;
}