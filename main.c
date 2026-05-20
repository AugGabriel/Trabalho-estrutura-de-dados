#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funções usadas como propriedade são nomeadas como substantivos, funções que realizam operação nomeadas como verbo

// ====================
//  Relacionados a Time
// ====================

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
int pontos_ganhos(Time *time) {
    int VALOR_VITORIA = 3, VALOR_EMPATE = 1;    // Não tenho certeza dos valores
    return time->vitorias * VALOR_VITORIA + time->empates * VALOR_EMPATE;
}

// Propriedade de time, que determina o saldo de gols
int saldo_de_gols(Time *time) {
    return time->gols_marcados - time->gols_sofridos;
}

// Construtor de time
Time *criar_time(int id, char *nome) {
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

// Função para imprimir dados do time
void imprimir_time(Time *time) {
    if (time == NULL) { 
        printf("Time com valor nulo\n");
        return;
    }

    printf("Id: %d \nNome: %s \nVitórias: %d \nEmpates: %d \nDerrotas: %d \
        \nGols marcados: %d \nGols sofridos: %d \nSaldo de gols: %d \nPontos ganhos: %d\n", 
        time->id, time->nome, time->vitorias, time->empates, time->derrotas, 
        time->gols_marcados, time->gols_sofridos, saldo_de_gols(time), pontos_ganhos(time)
    );
}

// Função para liberar memória alocada para time
void apagar_time(Time *time) {
    free(time);
}

// ======================
//  Relacionados a BDTime
// ======================

// Macro para definir a quantidade de times
#define _QUANT_TIMES 10

// Lista interna com os times carregados do arquivo de texto
static Time *_times[_QUANT_TIMES];

// Função que traz os dados do arquivo de texto para a lista _times
void carregar_dados_times() {
    FILE *arquivo = fopen("times.csv", "r");
    
    if (arquivo == NULL) {
        // Implementação de erro, baseada em perror()
    }

    for (int i = 0; i < _QUANT_TIMES; i++) {
        int id;
        char *nome = (char*)malloc(sizeof(15 * sizeof(char)));  // Inicialização?

        fscanf(arquivo, " %d,%s", &id, nome);

        _times[i] = criar_time(id, nome);
    }

    fclose(arquivo);
}

// Função auxiliar usada para criar e inicializar lista vazia de times
Time **_inicializa_lista_times() {
    Time **times = (Time**)malloc(_QUANT_TIMES * sizeof(Time*));
    for (int i = 0; i < _QUANT_TIMES; i++) {
        times[i] = NULL;
    }
    return times;
}

// Função auxiliar para montar prefixo, para consulta de time
char *_monta_prefixo(char *nome, int tamanho) {
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

    for (int i = 0; i < _QUANT_TIMES; i++) {
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

// Funcionalidade essencial, para consultar e imprimir os times a partir do nome ou prefixo
void consultar_times(const char *nome) {
    Time **times = retornar_times(nome);

    if (times[0] == NULL) {
        printf("Nenhum time encontrado\n");
        return;
    }

    printf("ID\tTime\t\tV\tE\tD\tGM\tGS\tS\tPG\n");
    
    for (int i = 0; times[i] != NULL && i < _QUANT_TIMES; i++) {
        Time *time = times[i];
        printf(
            "%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", time->id, time->nome, time->vitorias,
            time->empates, time->derrotas, time->gols_marcados, time->gols_sofridos, 
            saldo_de_gols(time), pontos_ganhos(time)
        );
    }

    printf("\n");
    free(times);
}

// =======================
//  Relacionados a Partida
// =======================

// Estrutura de partida
typedef struct partida {
    int id;

    Time* time1;
    Time* time2;

    int gols_time1;
    int gols_time2;
} Partida;

// Construtor de partida
Partida *criar_partida(int id, int id_time1, int id_time2, int gols_time1, int gols_time2) {
    static int cont = 0;

    Partida *partida = (Partida*)malloc(sizeof(Partida));

    partida->id = id;
    partida->time1 = _times[id_time1];
    partida->time2 = _times[id_time2];
    partida->gols_time1 = gols_time1;
    partida->gols_time2 = gols_time2;

    return partida;
}

// Função para liberar memória alocada para partida
void apagar_partida(Partida *partida) {
    // apagar_time(partida->time1);
    // apagar_time(partida->time2);
    free(partida);
}

// ==========================
//  Relacionados a BDPartidas 
// ==========================
#define _MAX_PARTIDAS 20
Partida *_partidas[_MAX_PARTIDAS];

enum filtro_pesquisa_partida {
    TIME_MANDANTE = 0,
    TIME_VISITANTE = 1,
    AMBOS = 2,
} FILTRO_PESQUISA_PARTIDA;

void carregar_dados_partidas() {
    FILE *arquivo = fopen("partidas.csv", "r");

    if (arquivo == NULL) {
        // Implementação de erro, baseada em perror()
    }

    for (int i = 0; i < _MAX_PARTIDAS; i++) {
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

    fclose(arquivo);
}

// Função auxiliar usada para criar e inicializar lista vazia de partidas
Partida **_inicializa_lista_partidas() {
    Partida **partidas = (Partida**)malloc(_MAX_PARTIDAS * sizeof(Partida*));
    for (int i = 0; i < _MAX_PARTIDAS; i++) {
        partidas[i] = NULL;
    }
    return partidas;
}

// Função usada para montar lista de partidas, a partir do modo de pesquisa e dos times para consultar
// Para cada partida, para cada time, se o time tiver jogado na partida, e na posição solicitada (mandante ou visitante), ele será adicionado à lista
Partida **retornar_partidas(Time **times, int modo) {
    Partida **partidas = _inicializa_lista_partidas();

    for (int i = 0; i < _MAX_PARTIDAS && _partidas[i] != NULL; i++) {       // Aqui considera que _partidas[] passa a ter valores nulos a partir de certo ponto, não funciona se não for assim
        for (int j = 0; j < _QUANT_TIMES && _times[j] != NULL; j++) {       // Mesma ideia aqui, considera que passa a ser nulo
            if (modo == TIME_MANDANTE && )
        }
    }
}

// Funcionalidade de consultar partida
Partida *consultar_partidas(char *nome) {
    Time **times = retornar_times(nome);

    if (times[0] == NULL) { 
        printf("Time não encontrado\n");
        return NULL;
    }

    int escolha;
    printf("Escolha o modo de consulta: \
        \n\t1)Por time mandante \
        \n\t2) Por time visitante \
        \n\t3) Por time mandante ou visitante \
        \n\t4) Retornar ao menu principal\n");
    scanf(" %d", &escolha);

    switch(escolha) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4: 
            break;
        default:
            break;
    }




    free(times);
}

// ==========================
//  Execução 
// ==========================
int main() {
    carregar_dados_times();
    carregar_dados_partidas();

    // for (int i = 0; i < _QUANT_TIMES; i++) {
    //     printf("%d - %s\n", _times[i]->id, _times[i]->nome);
    // }
    
    // char entrada[15];
    // char *entrada = "JAVAlis";
    // printf("Entrada: ");
    // scanf(" %s", entrada);

    char *entrada = "J";
    consultar_times(entrada);

    // char escolha = '0';
    // // char entrada[15];

    // while (escolha != 'Q' && escolha != 'q') {
    //     printf("Faça sua escolha: \
    //         \n\t1) Consultar time \
    //         \n\t2) Consultar partidas \
    //         \n\t3) Atualizar partida \
    //         \n\t4) Remover partida \
    //         \n\t5) Inserir partida \
    //         \n\t6) Imprimir tabela de classificação \
    //         \n\tQ) Sair\n");
    //     scanf(" %c", &escolha);

    //     switch(escolha) {
    //         case '1':
    //             printf("Digite o nome ou o apelido do time: ");
    //             scanf(" %s", entrada);

    //             Time *time = consultar_time(entrada);
    //             imprimir_time(time);

    //             break;
    //         case '2':
    //             break;
    //         case '3':
    //             break;
    //         case '4':
    //             break;
    //         case '5':
    //             break;
    //         case '6':
    //             break;
    //         case 'Q':
    //         case 'q':
    //             break;
    //         default:
    //             break;
    //     }
    // }

    return 0;
}