# Trabalho-estrutura-de-dados
Trabalho da matéria de Estrutura de Dados, curso de Bacharelado de Sistemas de Informação, IFES.
Alunos: Gabriel Augusto Pereira e João Vitor Calmon Castiglioni Rangel Pôrto.

EXECUÇÃO
Para a execução do projeto, é necessário estar instalado no dispositivo: compilador GCC; Subsistema do Windows para Linux (WSL); e algum Distro Ubuntu, recomendado o 22.01. No diretório raíz do projeto, abra o terminal, e digite "make". Isso será o suficiente para iniciar a execução do sistema, e a partir disso, as saídas do sistema no terminal serão seu guia de como prosseguir.

Para mudar as partidas que serão carregadas no sistema, é só copiar e colar os dados para o arquivo partidas.csv, ordenado pelas colunas ID, Time1, Time2, GolsTime1 e GolsTime2, com os valores separados por vírgula simples.

ESTRUTURA DO PROJETO
*Escrever*

DECISÕES DE IMPLEMENTAÇÃO
Os principais TADs (Tipo Abstrato de Dados) utilizados foram: 
    Time, que é responsável por armazenar os dados de um único time por vez;
    BDTime, responsável por armazenar todos os times, e processar informações referentes a mais de um time por vez;
    Partida, que assim como Time, é responsável por armazenar os dados de uma única partida por vez;
    e BDPartida, responsável por armazenar todos os times, e processar informações referentes a mais de um time por vez.

