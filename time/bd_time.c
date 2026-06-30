#include "bd_time.h"

// Definição do struct do nó para BDTime
struct bd_time_node {
    Time *info;
    BDTimeNode *next;
};

// Definição do struct para BDTime
struct bd_time {
    BDTimeNode *first;
};

// Criação de BDTime
BDTime *bdt_create() {
    BDTime *bdt = (BDTime*)malloc(sizeof(BDTime));
    bdt->first = NULL;
    return bdt;
}

// Obtenção de elemento de BDTime. Se index for fora de BDTime, retorno é NULL
Time *bdt_get(BDTime *bdt, int index) {
    BDTimeNode *node = bdt->first;

    for (int i = 0; i < index; i++) {
        node = node->next;

        if (node == NULL) {
            return NULL;
        }
    }

    return node->info;
}

// Imprimir todos os times da lista
void bdt_print(BDTime *bdt) {
    for (BDTimeNode *node = bdt->first; node != NULL; node = node->next) {
        imprimir_time(node->info);
    }
}

// Adição de elemento ao final de BDTime. Retorna o index aonde o elemento foi adicionado
int bdt_append(BDTime *bdt, Time *info) {
    BDTimeNode *node = (BDTimeNode*)malloc(sizeof(BDTimeNode));
    node->info = info;
    node->next = NULL;
    int index = 0;
    
    if (bdt->first == NULL) {
        // Insere no começo
        bdt->first = node;
    }
    else {
        // Encontra o último nó, e adiciona à frente
        BDTimeNode *last = bdt->first;

        while (last->next != NULL) {
            last = last->next;
            index++;
        }
        last->next = node;
    }

    return index;
}

// Apagar BDTime e seus nós
void bdt_free(BDTime *bdt) {
    BDTimeNode *node = bdt->first;

    while (node != NULL) {
        BDTimeNode *next = node->next;
        free(node);
        node = next;
    }

    free(bdt);
}

// Função que traz os dados do arquivo de texto para a lista _times
BDTime *carregar_dados_times() {
    BDTime *bdt = bdt_create();
    FILE *arquivo = fopen("tabelas/times.csv", "r");
    
    // Validação do arquivo
    if (arquivo == NULL) {
        perror("Alocação de memória falhou");
        exit(EXIT_FAILURE);
    }

    // Cria um Time para cada linha do arquivo de texto
    for (int i = 0; i < QUANT_TIMES; i++) {
        int id;
        char *nome = (char*)malloc(sizeof(15 * sizeof(char)));
        inicializa_string(nome, 15);

        fscanf(arquivo, " %d,%s", &id, nome);

        Time *time = criar_time(id, nome);

        bdt_append(bdt, time);
    }

    // Fecha o arquivo
    fclose(arquivo);

    // Retorna o BDTime
    return bdt;
}

// Função auxiliar para montar prefixo, para consulta de time
char *_monta_prefixo(char *nome, const int tamanho) {
    char *prefixo = (char*)malloc((tamanho + 1) * sizeof(char));

    for (int i = 0; i < tamanho; i++) {
        prefixo[i] = nome[i];
    }
    prefixo[tamanho] = '\0';

    return prefixo;
}

// Função usada para montar lista de times a partir do nome ou do prefixo
BDTime *retornar_times(BDTime *bdt, const char *nome) {
    BDTime *times = bdt_create();

    for (int i = 0; i < QUANT_TIMES; i++) {
        char *prefixo = _monta_prefixo(get_nome(bdt_get(bdt, i)), strlen(nome));

        if (
            string_comp_insensitive(get_nome(bdt_get(bdt, i)), nome) == 0         // Entrada bate com o nome
            || string_comp_insensitive(prefixo, nome) == 0                        // Entrada bate com o prefixo
        ) {
            bdt_append(times, bdt_get(bdt, i));
        }

        free(prefixo);
    }

    return times;
}

// Função para imprimir vários times em sequência, com cabeçalho
void imprimir_times(BDTime *bdt) {
    printf("%-5s %-15s %-5s %-5s %-5s %-5s %-5s %-5s %-5s\n", "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG");
    bdt_print(bdt);
    printf("\n");
}

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
    BDTime *times = retornar_times(bdt, nome);

    // Validação da lista
    if (bdt_get(times, 0) == NULL) {
        printf("\nNenhum time encontrado\n\n");
        return;
    }

    // Impressão da lista
    imprimir_times(times);

    // Liberação de memória da lista alocada dinamicamente
    bdt_free(times);
}