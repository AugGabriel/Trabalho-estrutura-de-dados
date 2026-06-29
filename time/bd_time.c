#include "bd_time.h"

// Lista interna com os times carregados do arquivo de texto
static Time *_times[QUANT_TIMES];

// Função para acessar valores da lista privada
Time **lista_times() { return _times; }

// Função que traz os dados do arquivo de texto para a lista _times
void carregar_dados_times() {
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

        _times[i] = criar_time(id, nome);
    }

    // Fecha o arquivo
    fclose(arquivo);
}

// Função auxiliar usada para criar e inicializar lista vazia de times
Time **_inicializa_lista_times() {
    Time **times = (Time**)malloc(QUANT_TIMES * sizeof(Time*));
    for (int i = 0; i < QUANT_TIMES; i++) {
        times[i] = NULL;
    }
    return times;
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
Time **retornar_times(const char *nome) {
    Time **times = _inicializa_lista_times();
    int j = 0;

    for (int i = 0; i < QUANT_TIMES; i++) {
        char *prefixo = _monta_prefixo(get_nome(_times[i]), strlen(nome));

        if (
            string_comp_insensitive(get_nome(_times[i]), nome) == 0         // Entrada bate com o nome
            || string_comp_insensitive(prefixo, nome) == 0                  // Entrada bate com o prefixo
        ) {
            times[j++] = _times[i];
        }

        free(prefixo);
    }

    return times;
}

// Função para imprimir vários times em sequência, com cabeçalho
void imprimir_times(Time **times) {
    printf("%s\t%9s\t\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG");
    
    for (int i = 0; times[i] != NULL && i < QUANT_TIMES; i++) {
        Time *time = times[i];
        imprimir_time(time);
    }

    printf("\n");
}

// Funcionalidade 1, para consultar e imprimir os times a partir do nome ou prefixo
void consultar_times() {

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
    Time **times = retornar_times(nome);

    // Validação da lista
    if (times[0] == NULL) {
        printf("\nNenhum time encontrado\n\n");
        return;
    }

    // Impressão da lista
    imprimir_times(times);

    // Liberação de memória da lista alocada dinamicamente
    free(times);
}

// Funcionalidade para desalocar todos os times
void apagar_times() {
    for (int i = 0; i < QUANT_TIMES; i++) {
        apagar_time(_times[i]);
    }
}