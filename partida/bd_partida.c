#include "bd_partida.h"

// Enumerate para modos de pesquisa de time, na funcionalidade 2
enum filtro_pesquisa_partida {
    TIME_MANDANTE,
    TIME_VISITANTE,
    AMBOS,
} FILTRO_PESQUISA_PARTIDA;

// Definição do struct do nó para BDPartida
struct bd_partida_node {
    Partida *info;
    BDPartidaNode *next;
};

// Definição do struct para BDPartida
struct bd_partida {
    BDPartidaNode *first;
};

// Criação de BDPartida
BDPartida *bdp_create() {
    BDPartida *bdp = (BDPartida*)malloc(sizeof(BDPartida));
    bdp->first = NULL;
    return bdp;
}

// Obtenção de elemento de BDPartida. Se index for fora de BDPartida, retorno é NULL
Partida *bdp_get(BDPartida *bdp, int index) {
    BDPartidaNode *node = bdp->first;

    for (int i = 0; i < index; i++) {
        node = node->next;

        if (node == NULL) {
            return NULL;
        }
    }

    return node->info;
}

// Imprimir todas as partidas da lista
void bdp_print(BDPartida *bdp) {
    for (BDPartidaNode *node = bdp->first; node != NULL; node = node->next) {
        imprimir_partida(node->info);
    }
}

// Adição de elemento ao final de BDPartida. Retorna o index aonde o elemento foi adicionado
int bdp_append(BDPartida *bdp, Partida *info) {
    BDPartidaNode *node = (BDPartidaNode*)malloc(sizeof(BDPartidaNode));
    node->info = info;
    node->next = NULL;
    int index = 0;
    
    if (bdp->first == NULL) {
        // Insere no começo
        bdp->first = node;
    }
    else {
        // Encontra o último nó, e adiciona à frente
        BDPartidaNode *last = bdp->first;

        while (last->next != NULL) {
            last = last->next;
            index++;
        }
        last->next = node;
        index++;
    }

    return index;
}

// Apagar BDPartida e seus nós
void bdp_free(BDPartida *bdp) {
    BDPartidaNode *node = bdp->first;

    while (node != NULL) {
        BDPartidaNode *next = node->next;
        free(node);
        node = next;
    }

    free(bdp);
}

// Função para carregar os dados do arquivo de texto para a lista de partidas
BDPartida *carregar_dados_partidas(BDTime *bdt) {
    BDPartida *bdp = bdp_create();
    FILE *arquivo = fopen("tabelas/partidas.csv", "r");

    // Validação do arquivo
    if (arquivo == NULL) {
        perror("Alocação de memória falhou");
        exit(EXIT_FAILURE);
    }

    // Cria uma Partida para cada linha do arquivo de texto
    for (int i = 0; i < MAX_PARTIDAS; i++) {
        int id;
        int id_mandante, id_visitante;
        int gols_mand, gols_visit;

        if (fscanf(
            arquivo, 
            " %d,%d,%d,%d,%d", 
            &id, 
            &id_mandante, 
            &id_visitante, 
            &gols_mand, 
            &gols_visit
        ) == EOF) {
            break;
        }

        bdp_append(bdp, criar_partida(bdt, id, id_mandante, id_visitante, gols_mand, gols_visit));
    }

    // Fecha o arquivo
    fclose(arquivo);

    // Retorna o BDPartida
    return bdp;
}

// Função usada para montar lista de partidas, a partir do modo de pesquisa e dos times para consultar
// Para cada partida, para cada time, se o time tiver jogado na partida, e na posição solicitada (mandante ou visitante), ele será adicionado à lista
BDPartida *retornar_partidas(BDPartida *bdp, BDTime *times, const int modo) {
    BDPartida *partidas = bdp_create();

    for (int i = 0; i < MAX_PARTIDAS && bdp_get(bdp, i) != NULL; i++) {         // Aqui considera que a lista de partidas passa a ter valores nulos a partir de certo ponto, não funciona se não for assim
        for (int j = 0; j < QUANT_TIMES && bdt_get(times, j) != NULL; j++) {             // Mesma ideia aqui, considera que passa a ser nulo
            if (
                (modo != TIME_VISITANTE && get_time1(bdp_get(bdp, i)) == bdt_get(times, j))    // Time mandante na partida
                || (modo != TIME_MANDANTE && get_time2(bdp_get(bdp, i)) == bdt_get(times, j))  // Time visitante na partida
            ) {
                bdp_append(partidas, bdp_get(bdp, i));
            }
        }
    }

    return partidas;
}

// Funcionalidade 2, para consultar partidas a partir do nome de um time
void consultar_partidas(BDTime *bdt, BDPartida *bdp) {

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

    BDTime *times = retornar_times(bdt, nome);

    // Validação da lista de times
    if (bdt_get(times, 0) == NULL) { 
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
    BDPartida *partidas = retornar_partidas(bdp, times, modo);
    bdt_free(times);

    if (bdp_get(partidas, 0) == NULL) {
        printf("Nenhuma partida encontrada\n");
        return;
    }

    // Imprime os dados formatados em tabela
    printf("%s\t%9s\t\t\t%9s\n", "ID", "Time1", "Time2");
    for (int i = 0; i < MAX_PARTIDAS && bdp_get(partidas, i) != NULL; i++) {
        Partida *partida = bdp_get(partidas, i);
        imprimir_partida(partida);
    }
    printf("\n");

    bdp_free(partidas);
}