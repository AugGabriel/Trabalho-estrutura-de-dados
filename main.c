#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funções usadas como propriedade são nomeadas como substantivos, funções que realizam operação nomeadas como verbo

// TO DO
// Adicionar 'const' nos parâmetros das funções
// Inicializar strings

// DONE


// ==========================
//  Relacionados a Time
// ==========================

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
    int VALOR_VITORIA, VALOR_EMPATE;    // Ainda preciso descobrir o valor
    return time->vitorias * VALOR_VITORIA + time->empates * VALOR_EMPATE;
}

// Propriedade de time, que determina o saldo de gols
int saldo_de_gols(Time *time) {
    return time->gols_marcados - time->gols_sofridos;
}

// Construtor de time
Time *criar_time(int id, char *nome) {
    Time *time = (Time*)malloc(sizeof(Time));

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
    printf("Imprimir time\n");
    printf("Id: %d, Nome: %s\n", time->id, time->nome);
}

// ==========================
//  Relacionados a BDTime 
// ==========================

// Macro para definir a quantidade de times
#define _QUANT_TIMES 10

// Lista interna com os times carregados do arquivo de texto
static Time *_times[_QUANT_TIMES];

// Função interna, usada para encontrar o nome do time a partir do seu apelido
char *_filtro_maiusculas(char *string) {
    char *string_filt = (char*)malloc(15 * sizeof(char));
    int i = 0, j = 0;

    while (string[i] != '\0') {
        if (string[i] >= 65 && string[i] <= 90) {
            string_filt[j++] = string[i];
        }
        i++;
    }
    string_filt[++j] = '\0';

    return string_filt;
}

// Função que traz os dados do arquivo de texto para a lista _times
void carregar_dados_times() {
    FILE *arquivo = fopen("times.csv", "r");
    
    if (arquivo == NULL) {
        // Implementação de erro, baseada em perror()
    }

    for (int i = 0; i < _QUANT_TIMES; i++) {
        int id = 0;
        char *nome = (char*)malloc(sizeof(15 * sizeof(char)));

        fscanf(arquivo, " %d,%s", &id, nome);

        _times[i] = criar_time(id, nome);
    }

    fclose(arquivo);
}

// Funcionalidade do sistema, para consultar time a partir do nome ou do apelido
Time *consultar_time(const char *nome) {
    for (int i = 0; i < _QUANT_TIMES; i++) {
        if (
            strcmp(_times[i]->nome, nome) == 0 
            || strcmp(_filtro_maiusculas(_times[i]->nome), nome) == 0
        ) {
            return _times[i];
        }
    }
    return NULL;
}

// ==========================
//  Relacionados a Partida
// ==========================

// Estrutura de partida
typedef struct partida {
    int id;

    Time* time1;
    Time* time2;

    int gols_time1;
    int gols_time2;
} Partida;

// Construtor de partida
Partida *criar_partida(Time *time1, Time *time2, int gols_time1, int gols_time2) {
    static int cont = 0;

    Partida *partida = (Partida*)malloc(sizeof(Partida));
    partida->time1 = time1;
    partida->time2 = time2;
    partida->gols_time1 = gols_time1;
    partida->gols_time2 = gols_time2;

    return partida;
}

// Funcionalidade de consultar partida
Partida *consultar_partida() {

}

void apagar_partida(Partida *partida) {
    // apaga_time(partida->time1);
    // apaga_time(partida->time2);
    free(partida->time1);
    free(partida->time2);
    free(partida);
}

// ==========================
//  Relacionados a BDPartidas 
// ==========================
Partida *partidas[20];

// ==========================
//  Execução 
// ==========================
int main() {
    carregar_dados_times();
    // for (int i = 0; i < _QUANT_TIMES; i++) {
    //     printf("%d - %s\n", _times[i]->id, _times[i]->nome);
    // }
    
    // char entrada[15];
    char *entrada = "JAVAlis";
    // printf("Entrada: ");
    // scanf(" %s", entrada);
    // for (int i = 0; i < strlen(entrada); i++) {
    //     printf("%c", entrada[i]);
    // }
    // printf("\n");

    Time *time = consultar_time(entrada);
    imprimir_time(time);

    /*
    char escolha = '0';

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
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break;
            case '5':
                break;
            case '6':
                break;
            case 'Q':
            case 'q':
                break;
            default:
                break;
        }
    }
    */
    return 0;
}