#include "tabela_classificacao.h"

void tabela_classificacao_carregar(BDPartidas *bdp) {
    for (int i = 0; i < MAX_PARTIDAS && bdp_get(bdp, i) != NULL; i++) {
        Partida *partida = bdp_get(bdp, i);

        Time *time1 = get_time1(partida);
        Time *time2 = get_time2(partida);

        // Gols marcados
        int gm1 = get_gols_marcados(time1) + get_gols_time1(partida);
        int gm2 = get_gols_marcados(time2) + get_gols_time2(partida);
        set_gols_time1(partida, gm1);
        set_gols_time2(partida, gm2);

        // Gols sofridos
        int gs1 = get_gols_sofridos(time1) + get_gols_time1(partida);
        int gs2 = get_gols_sofridos(time2) + get_gols_time2(partida);
        set_gols_sofridos(time1, gs1);
        set_gols_sofridos(time2, gs2);
        
        if (get_gols_time1(partida) == get_gols_time2(partida)) {       // Empate
            set_empates(time1, get_empates(time1) + 1);
            set_empates(time2, get_empates(time2) + 1);
        }
        else if (get_gols_time1(partida) > get_gols_time2(partida)) {   // Vitória do time 1
            set_vitorias(time1, get_vitorias(time1) + 1);
            set_derrotas(time2, get_derrotas(time2) + 1);
        }
        else {                                                  // Vitória do time 2
            set_derrotas(time1, get_derrotas(time1) + 1);
            set_vitorias(time2, get_vitorias(time2) + 1);
        }
    }
}