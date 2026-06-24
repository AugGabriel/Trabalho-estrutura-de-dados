#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "auxiliares_globais.h"
//#include "time.h"
//#include "bd_time.h"
//#include "partida.h"
//#include "bd_partida.h"
//#include "tabela_classificacao.h"

#define TAMANHO_MAX_ENTRADA 15

// Inicializa string com caracteres de final, para garantir que ela termine em algum momento
// O ideal seria que a entrada com o %s encerrasse a string com \0, porém o comportamento pareceu variar entre compiladores
void inicializa_string(char *string, const int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        string[i] = '\0';
    }
}


// Estrutura de time
typedef struct time {
   int id;
   char *nome;

   int vitorias;
   int empates;
   int derrotas;

   int gols_marcados;
   int gols_sofridos;
} Time;

// Propriedade de time, que determina os pontos ganhos
int pontos_ganhos(const Time *time) {
    int VALOR_VITORIA = 3, VALOR_EMPATE = 1;    // Não tenho certeza dos valores
    return time->vitorias * VALOR_VITORIA + time->empates * VALOR_EMPATE;
}

// Propriedade de time, que determina o saldo de gols
int saldo_de_gols(const Time *time) {
    return time->gols_marcados - time->gols_sofridos;
}

// Construtor de time
Time *criar_time(const int id, char *nome) {
    Time *time = (Time*)malloc(sizeof(Time));

    if (time == NULL) {
        printf("Não foi possível alocar memória para o time\n");
        return NULL;
    }

    time->id = id;
    time->nome = nome;

    time->vitorias = 0;
    time->empates = 0;
    time->derrotas = 0;
    time->gols_marcados = 0;
    time->gols_sofridos = 0;

    return time;
}

// Função para liberar memória alocada para time
void apagar_time(Time *time) {
    free(time);
}


// Macro para definir a quantidade de times
#define QUANT_TIMES 10

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
        char *prefixo = _monta_prefixo(_times[i]->nome, strlen(nome));

        if (
            strcmp(_times[i]->nome, nome) == 0          // Entrada bate com o nome
            || strcmp(prefixo, nome) == 0               // Entrada bate com o prefixo
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
        printf(
            "%d\t%9s\t\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", time->id, time->nome, time->vitorias,
            time->empates, time->derrotas, time->gols_marcados, time->gols_sofridos, 
            saldo_de_gols(time), pontos_ganhos(time)
        );
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


// Estrutura de partida
typedef struct partida {
    int id;

    Time* time1;
    Time* time2;

    int gols_time1;
    int gols_time2;
} Partida;

// Construtor de partida
Partida *criar_partida(
            const int id, 
            const int id_time1, const int id_time2, 
            const int gols_time1, const int gols_time2
    ) {

    // Alocação de memória
    Partida *partida = (Partida*)malloc(sizeof(Partida));

    // Validação da alocação de memória
    if (partida == NULL) {
        perror("Alocação de memória falhou");
        exit(EXIT_FAILURE);
    }

    // Inicialização
    partida->id = id;
    partida->time1 = lista_times()[id_time1];
    partida->time2 = lista_times()[id_time2];
    partida->gols_time1 = gols_time1;
    partida->gols_time2 = gols_time2;

    return partida;
}

// Função para liberar memória alocada para partida
void apagar_partida(Partida *partida) {
    free(partida);
}


// Quantidade máxima de partidas permitida
#define MAX_PARTIDAS 100

// Lista interna de partidas
Partida *_partidas[MAX_PARTIDAS];

// Função para acesso à lista de partidas, por parte dos outros módulos
Partida **lista_partidas() { return _partidas; }

// Enumerate para modos de pesquisa de time, na funcionalidade 2
enum filtro_pesquisa_partida {
    TIME_MANDANTE = 0,
    TIME_VISITANTE = 1,
    AMBOS = 2,
} FILTRO_PESQUISA_PARTIDA;

// Função para carregar os dados do arquivo de texto para a lista de partidas
void carregar_dados_partidas() {
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
            return;
        }

        _partidas[i] = criar_partida(id, id_mandante, id_visitante, gols_mand, gols_visit);
    }

    // Fecha o arquivo
    fclose(arquivo);
}

// Função auxiliar usada para criar e inicializar lista vazia de partidas
Partida **_inicializa_lista_partidas() {
    Partida **partidas = (Partida**)malloc(MAX_PARTIDAS * sizeof(Partida*));

    for (int i = 0; i < MAX_PARTIDAS; i++) {
        partidas[i] = NULL;
    }

    return partidas;
}

// Função usada para montar lista de partidas, a partir do modo de pesquisa e dos times para consultar
// Para cada partida, para cada time, se o time tiver jogado na partida, e na posição solicitada (mandante ou visitante), ele será adicionado à lista
Partida **retornar_partidas(Time **times, const int modo) {
    Partida **partidas = _inicializa_lista_partidas();
    int k = 0;

    for (int i = 0; i < MAX_PARTIDAS && _partidas[i] != NULL; i++) {       // Aqui considera que _partidas[] passa a ter valores nulos a partir de certo ponto, não funciona se não for assim
        for (int j = 0; j < QUANT_TIMES && times[j] != NULL; j++) {        // Mesma ideia aqui, considera que passa a ser nulo
            if (
                (modo != TIME_VISITANTE && _partidas[i]->time1 == times[j])    // Time mandante na partida
                || (modo != TIME_MANDANTE && _partidas[i]->time2 == times[j])  // Time visitante na partida
            ) {
                partidas[k++] = _partidas[i];
            }
        }
    }

    return partidas;
}

// Funcionalidade 2, para consultar partidas a partir do nome de um time
void consultar_partidas() {

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

    Time **times = retornar_times(nome);

    // Validação da lista de times
    if (times[0] == NULL) { 
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
    Partida **partidas = retornar_partidas(times, modo);
    free(times);

    if (partidas[0] == NULL) {
        printf("Nenhuma partida encontrada\n");
        return;
    }

    // Imprime os dados formatados em tabela
    printf("%s\t%9s\t\t\t%9s\n", "ID", "Time1", "Time2");
    for (int i = 0; i < MAX_PARTIDAS && partidas[i] != NULL; i++) {
        Partida *partida = partidas[i];
        printf(
            "%d\t%9s\t%d\tx\t%d\t%9s\n",
            partida->id,
            partida->time1->nome,
            partida->gols_time1,
            partida->gols_time2,
            partida->time2->nome
        );
    }
    printf("\n");
}

// Função para desalocar a memória de todas as partidas
void apagar_partidas() {
    for (int i = 0; i < MAX_PARTIDAS; i++) {
        apagar_partida(_partidas[i]);
    }
}


void calcular_resultados() {
    for (int i = 0; i < MAX_PARTIDAS && lista_partidas()[i] != NULL; i++) {
        Partida *partida = lista_partidas()[i];

        Time *time1 = partida->time1;
        Time *time2 = partida->time2;

        // Gols marcados
        time1->gols_marcados += partida->gols_time1;
        time2->gols_marcados += partida->gols_time2;

        // Gols sofridos
        time1->gols_sofridos += partida->gols_time2;
        time2->gols_sofridos += partida->gols_time1;

        if (partida->gols_time1 == partida->gols_time2) {       // Empate
            time1->empates++;
            time2->empates++;
        }
        else if (partida->gols_time1 > partida->gols_time2) {   // Vitória do time 1
            time1->vitorias++;
            time2->derrotas++;
        }
        else {                                                  // Vitória do time 2
            time1->derrotas++;
            time2->vitorias++;
        }
    }
}

// Funcionalidade 3, para imprimir a tabela de classificação
void imprimir_tabela_classificacao() {
    printf("\nImprimindo classificação: \n");
    imprimir_times(lista_times());
}


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

    // Liberação de memória
    apagar_times();
    apagar_partidas();

    return 0;
}