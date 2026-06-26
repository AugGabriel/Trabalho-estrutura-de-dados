#ifndef TIME_H
#define TIME_H

// Estrutura de time
typedef struct time Time;

char *time_nome(Time *t);

// Propriedade de time, que determina os pontos ganhos
int time_pontos_ganhos(const Time *time);

// Propriedade de time, que determina o saldo de gols
int time_saldo_de_gols(const Time *time);

// Construtor de time
Time *time_criar(const int id, char *nome);

// Função para imprimir time
void time_print(Time *time);

// Função para liberar memória alocada para time
void time_limpar(Time *time);

// END Time ------------------------------------------

#endif