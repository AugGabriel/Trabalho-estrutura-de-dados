// Módulo para ações do menu escolhidas pelo usuário

#include "acoes_menu.h"

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

    int apagar_informacoes = 0;
    ll_free(times, apagar_informacoes);
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
    
    if (ll_is_empty(partidas)) {
        printf("Nenhuma partida encontrada\n");
        return;
    }

    // Imprime os dados formatados em tabela
    printf("%s\t%9s\t\t\t%9s\n", "ID", "Time1", "Time2");
    for (int i = 0; i < ll_size(partidas); i++) {
        Partida *partida = ll_get(partidas, i);
        partida_imprimir(partida);
    }
    printf("\n");
    
    int apagar_informacoes = 0;
    ll_free(times, apagar_informacoes);
    ll_free(partidas, apagar_informacoes);
}

// Funcionalidade 3, para atualizar uma partida
void atualizar_partida(BDTimes *bdt, BDPartidas *bdp) {
    // Consulta de partidas, para escolher a que será alterada
    consultar_partidas(bdp, bdt);

    // Entrada do id da partida a ser alterada
    int id;
    printf("\nDigite o ID do registro a ser atualizado: ");
    scanf("%i", &id);

    // Entrada da quantidade de pontos em char, para aceitar o caractere '-'
    char pontos1, pontos2;
    printf("Digite o novo valor para os campos Placar1 e Placar2\npara manter o valor atual de um campo, digite '-'\n");
    scanf("%c", &pontos1);
    scanf("%c", &pontos2);

    // Tratamento das entradas possíveis
    if (pontos1 != '-') {
        partida_definir_gols(bdp_obter_partida(bdp, id), 1, (int)pontos1);
    }
    if (pontos2 != '-') {
        partida_definir_gols(bdp_obter_partida(bdp, id), 2, (int)pontos2);
    }

    // Mostrando o resultado
    partida_imprimir(bdp_obter_partida(bdp, id));
}

// Funcionalidade 4, para remoção de partida
void remover_partida(BDTimes *bdt, BDPartidas *bdp) {
    // Consulta de partidas, para escolher a que será alterada
    consultar_partidas(bdp, bdt);

    // Entrada do id da partida a ser alterada
    int id;
    printf("\nDigite o ID do registro a ser atualizado: ");
    scanf("%i", &id);

    // Entrada da confirmação
    char confirm;
    printf("\nTem certeza que deseja excluir o registro abaixo? (s/N)");
    partida_imprimir(bdp_obter_partida(bdp, id));
    scanf("%c", &confirm);

    // Cancelou a exclusão
    if (confirm != 's' && confirm == 'S') {
        return;
    }
    
    // TODO
    //bdp_remove(bdp, id);
}

// Funcionalidade 5, para inserção de partida
void inserir_partida() {}

// Funcionalidade 6, para imprimir a tabela de classificação
void imprimir_tabela_classificacao(BDTimes *bdt) {
    printf("\nImprimindo classificação: \n");
    bdt_imprimir_times(bdt);
}