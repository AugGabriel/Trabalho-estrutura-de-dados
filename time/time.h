#ifndef TIME_H
#define TIME_H

// Estrutura de time
typedef struct time Time;

// Construtor de time
Time *time_criar(const int id, char *nome);

char *time_nome(Time *t);

// Propriedade de time, que determina os pontos ganhos
int time_pontos_ganhos(const Time *time);

// Propriedade de time, que determina o saldo de gols
int time_saldo_de_gols(const Time *time);

void time_alterar_gols_marcados(Time *t, int valor);

void time_alterar_gols_sofridos(Time *t, int valor);

void time_alterar_vitorias(Time *t, int valor);

void time_alterar_derrotas(Time *t, int valor);

void time_alterar_empates(Time *t, int valor);

// Função para imprimir time
void time_print(Time *time);

// Função para liberar memória alocada para time
void time_limpar(Time *time);

#endif