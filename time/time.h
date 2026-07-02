#ifndef TIME_H
#define TIME_H

// Estrutura de time
typedef struct time Time;

// Construtor de time
Time *time_criar(const int id, char *nome);

// Propriedade de time, que determina os pontos ganhos
int time_pontos_ganhos(const Time *time);

// Propriedade de time, que determina o saldo de gols
int time_saldo_de_gols(const Time *time);

// Atributos de time
int time_id(Time *t);
char *time_nome(Time *t);
int time_gols_marcados(Time *t);
int time_gols_sofridos(Time *t);
int time_vitorias(Time *t);
int time_derrotas(Time *t);
int time_empates(Time *t);
void time_definir_gols_marcados(Time *t, int valor);
void time_definir_gols_sofridos(Time *t, int valor);
void time_definir_vitorias(Time *t, int valor);
void time_definir_derrotas(Time *t, int valor);
void time_definir_empates(Time *t, int valor);

// Função para imprimir time
void time_imprimir(Time *time);

void time_zerar(Time *time);

// Função para liberar memória alocada para time
void time_limpar(Time *time);

#endif