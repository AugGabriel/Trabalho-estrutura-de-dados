#include "bd_partida.h"

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

// Obtenção do tamanho de BDPartida
int bdp_size(BDPartida *bdp) {
    int i = 0;
    while (bdp_get(bdp, i) != NULL) {
        i++;
    }
    return i;
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

// Remover elemento do BDPartida
void bdp_remove(BDPartida *bdp, int id) {
    BDPartidaNode *prev = bdp->first;

    for (int i = 1; i < id; i++) {
        prev = prev->next;

        if (prev == NULL) {
            return;
        }
    }

    BDPartidaNode *node = prev->next;
    prev->next = node->next;
    free(node);
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
BDPartida *bdp_carregar_dados(BDPartida *bdp, BDTime *bdt) {
    FILE *arquivo = fopen(CAMINHO_BD_PARTIDA, "r");

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

    for (int i = 0; i < bdp_size(bdp); i++) {
        for (int j = 0; j < bdp_size(bdp); j++) {
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

// Função para aplicar as alterações de partida no arquivo bd de partida
void aplicar_alteracoes_partida(BDPartida *bdp) {
    for (int i = 0; i < bdp_size(bdp); i++) {
        Partida *partida = bdp_get(bdp, i);
        FILE *bd = fopen(CAMINHO_BD_PARTIDA, 'w');

        fprintf(
            "%d,%d,%d,%d,%d\n", 
            get_partida_id(partida),
            get_time1(partida),
            get_time2(partida),
            get_gols_time1(partida),
            get_gols_time2(partida)
        );
    }
}