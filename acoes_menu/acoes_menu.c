// Módulo para ações do menu escolhidas pelo usuário

#include "acoes_menu.h"

// Função interna para 
// Se nada for encontrado, imprime aviso, libera a lista vazia e retorna NULL.
// Se encontrar, retorna a lista (o chamador deve dar free()).
LinkedList *_buscar_retornar_times(BDTimes *bdt) {
    // Entrada do usuário
    char nome[TAMANHO_MAX_ENTRADA];

    printf("Digite o nome ou o apelido do time: ");
    scanf(" %s", nome);

    LinkedList *times = bdt_encontrar_times(bdt, nome);

    // Validação da lista de times: tratamento único do "não encontrado"
    if (ll_is_empty(times)) {
        printf("\nTime não encontrado\n\n");
        ll_free(times, 0);   // libera a lista vazia aqui mesmo
        return NULL;         // sinal único de "não achou"
    }

    return times;
}

// Funcionalidade 1, para consultar e imprimir os times a partir do nome ou prefixo
void consultar_times(BDTimes *bdt) {
    LinkedList *resultados = _buscar_retornar_times(bdt);
    // Validação da lista. Vem como NULL, caso nenhum time encontrado
    if (resultados) {
        // Imprime o cabeçalho
        printf("%s\t%9s\t\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG");
        // Imprime a lista de times encontrada
        ll_print(resultados);
        // Limpa a memória da lista alocada dinamicamente, sem excluir os dados dos nós
        ll_free(resultados, /*Apagar informações? Falso: */ 0);
    }
}

// Funcionalidade 2, para consultar partidas a partir do nome de um time
int consultar_partidas(BDPartidas *bdp, BDTimes *bdt) {
    // Busca pelos times
    LinkedList *times = _buscar_retornar_times(bdt);
    if (!times) {
        return 0;
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
            return 0;
        default:
            printf("Opção inválida\n");
            return 0;
    }

    // Chama a função de retornar partidas
    LinkedList *partidas = bdp_encontrar_partidas(bdp, times, modo);
    
    if (ll_is_empty(partidas)) {
        printf("Nenhuma partida encontrada\n");
        return 0;
    }

    // Imprime os dados formatados em tabela
    printf("%s\t%9s\t\t\t%9s\n", "ID", "Time1", "Time2");
    ll_print(partidas);
    printf("\n");
    
    int apagar_informacoes = 0;
    ll_free(times, apagar_informacoes);
    ll_free(partidas, apagar_informacoes);

    // valido
    return 1;
}

// Funcionalidade 3, para atualizar uma partida
void atualizar_partida(BDTimes *bdt, BDPartidas *bdp) {
    // Consulta de partidas, para escolher a que será alterada

    int valido = consultar_partidas(bdp, bdt);
    if (!valido) {
        return;
    }

    // Entrada do id da partida a ser alterada
    int id;
    printf("\nDigite o ID do registro a ser atualizado: ");
    scanf("%i", &id);
    
    // Obtenção da Partida selecionada
    Partida *partida = bdp_obter_por_id(bdp, id);
    
    // Mostrando a partida selecionada
    printf("\nPartida selecionada para alteração: \n");
    partida_imprimir(partida);

    // Entrada da quantidade de pontos em char, para aceitar o caractere '-'
    char pontos1, pontos2;
    printf("\nDigite o novo valor para os campos Placar1 e Placar2\npara manter o valor atual de um campo, digite '-'\n");
    scanf(" %c", &pontos1);
    scanf(" %c", &pontos2);

    // Tratamento das entradas possíveis
    if (pontos1 != '-') {
        partida_definir_gols(partida, /* Time: */ 1, pontos1 - '0');
    }
    if (pontos2 != '-') {
        partida_definir_gols(partida, /* Time: */ 2, pontos2 - '0');
    }

    // Mostrando o resultado
    partida_imprimir(partida);
}

// Funcionalidade 4, para remoção de partida
void remover_partida(BDTimes *bdt, BDPartidas *bdp) {
    // Consulta de partidas, para escolher a que será alterada
    int valido = consultar_partidas(bdp, bdt);
    if (!valido) {
        return;
    }

    // Entrada do id da partida a ser alterada
    int id;
    printf("\nDigite o ID do registro a ser atualizado: ");
    scanf("%i", &id);

    // Entrada da confirmação
    char confirm;
    printf("\nTem certeza que deseja excluir o registro abaixo? (S/N)\n");
    partida_imprimir(bdp_obter_por_id(bdp, id));
    scanf(" %c", &confirm);

    // Cancelou a exclusão
    if (confirm != 's' && confirm == 'S') {
        printf("\nOperação cancelada\n\n");
        return;
    }
    
    bdp_remover_por_id(bdp, id);
    printf("\nRegistro excluído!\n\n");
}

// Funcionalidade 5, para inserção de partida
void inserir_partida() {}

// Funcionalidade 6, para imprimir a tabela de classificação
void imprimir_tabela_classificacao(BDTimes *bdt, BDPartidas *bdp) {
    printf("\nImprimindo classificação: \n");
    bdp_calcular_resultados(bdp, bdt);
    bdt_imprimir_times(bdt);
}