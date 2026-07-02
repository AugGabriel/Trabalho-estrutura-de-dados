#ifndef TIME_H
#define TIME_H

// Estrutura de time
typedef struct time Time;

/**
 * Cria um time com estatísticas zeradas e retorna um ponteiro para ele.
 *
 * @param id   - Identificador do time.
 * @param nome - Nome do time (o ponteiro é armazenado, não copiado).
 * @return     - Ponteiro para o time criado, ou NULL se a alocação falhar.
 */
Time *time_criar(const int id, char *nome);

/**
 * Calcula os pontos ganhos pelo time.
 *
 * @param time - Ponteiro para o time.
 * @return     - Total de pontos ganhos.
 */
int time_pontos_ganhos(const Time *time);

/**
 * Calcula o saldo de gols do time.
 *
 * @param time - Ponteiro para o time.
 * @return     - Saldo de gols.
 */
int time_saldo_de_gols(const Time *time);

// Getters dos atributos armazenados no time
int time_id(Time *t);
char *time_nome(Time *t);
int time_gols_marcados(Time *t);
int time_gols_sofridos(Time *t);
int time_vitorias(Time *t);
int time_derrotas(Time *t);
int time_empates(Time *t);

// Setters dos atributos de estatística do time
void time_definir_gols_marcados(Time *t, int valor);
void time_definir_gols_sofridos(Time *t, int valor);
void time_definir_vitorias(Time *t, int valor);
void time_definir_derrotas(Time *t, int valor);
void time_definir_empates(Time *t, int valor);

/**
 * Imprime uma linha com os dados do time, formatada em tabela.
 *
 * @param time - Ponteiro para o time a ser impresso.
 */
void time_imprimir(Time *time);

/**
 * Libera a memória alocada para o time.
 *
 * @param time - Ponteiro para o time a ser liberado.
 */
void time_limpar(Time *time);

#endif
