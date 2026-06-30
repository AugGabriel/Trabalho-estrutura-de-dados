// Módulo para ações do menu escolhidas pelo usuário

#include "acoes_menu.h"

// Funcionalidade 1, para consultar e imprimir os times a partir do nome ou prefixo
void consultar_times(BDTime *bdt) {

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
void consultar_partidas(BDPartida *bdp, BDTime *bdt) {

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

// Funcionalidade 3, para atualizar uma partida
void atualizar_partida(BDTime *bdt, BDPartida *bdp) {
    // Consulta de partidas, para escolher a que será alterada
    consultar_partidas(bdt, bdp);

    // Entrada do id da partida a ser alterada
    int id;
    printf("\nDigite o ID do registro a ser atualizado: ");
    scanf("%d", id);

    // Entrada da quantidade de pontos em char, para aceitar o caractere '-'
    char pontos1, pontos2;
    printf("Digite o novo valor para os campos Placar1 e Placar2\npara manter o valor atual de um campo, digite '-'\n");
    scanf("%c %c", pontos1, pontos2);

    // Tratamento das entradas possíveis
    if (pontos1 != '-') {
        set_gols_time1(bdp_get(bdp, id), (int)pontos1);
    }
    if (pontos2 != '-') {
        set_gols_time2(bdp_get(bdp, id), (int)pontos2);
    }

    // Mostrando o resultado
    imprimir_partida(bdp_get(bdp, id));
}

// Funcionalidade 4, para remoção de partida
void remover_partida(BDTime *bdt, BDPartida *bdp) {
    // Consulta de partidas, para escolher a que será alterada
    consultar_partidas(bdt, bdp);

    // Entrada do id da partida a ser alterada
    int id;
    printf("\nDigite o ID do registro a ser atualizado: ");
    scanf("%d", id);

    // Entrada da confirmação
    char confirm;
    printf("\nTem certeza que deseja excluir o registro abaixo? (s/N)");
    imprimir_partida(bdp_get(bdp, id));
    scanf(" %c", confirm);

    // Cancelou a exclusão
    if (confirm != 's' && confirm == 'S') {
        return;
    }

    bdp_remove(bdp, id);
}

// Funcionalidade 5, para inserção de partida
void inserir_partida() {}

// Funcionalidade 6, para imprimir a tabela de classificação
void imprimir_tabela_classificacao(BDTime *bdt) {
    printf("\nImprimindo classificação: \n");
    imprimir_times(bdt);
}