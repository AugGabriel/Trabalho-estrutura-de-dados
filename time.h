#ifndef _TIME_H
#define _TIME_H

typedef struct time Time;

// Propriedade de time, que determina os pontos ganhos
int pontos_ganhos(Time *time);

// Propriedade de time, que determina o saldo de gols
int saldo_de_gols(Time *time);

// Construtor de time
Time *criar_time(int id, char *nome);

// Função para imprimir dados do time
void imprimir_time(Time *time);

// Função para liberar memória alocada para time
void apagar_time(Time *time);

#endif