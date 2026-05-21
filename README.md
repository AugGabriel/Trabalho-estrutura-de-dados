# Trabalho-estrutura-de-dados
Trabalho da matéria de Estrutura de Dados, curso de Bacharelado de Sistemas de Informação, IFES.
Alunos: Gabriel Augusto Pereira e João Vitor Calmon Castiglioni Rangel Pôrto.

EXECUÇÃO
Para a execução do projeto, é necessário estar instalado no dispositivo: compilador GCC; Subsistema do Windows para Linux (WSL); e algum Distro Ubuntu, recomendado o 22.01. No diretório raíz do projeto, abra o terminal, e digite "make". Isso será o suficiente para iniciar a execução do sistema, e a partir disso, as saídas do sistema no terminal serão seu guia de como prosseguir.

Para mudar as partidas que serão carregadas no sistema, é só copiar e colar os dados para o arquivo partidas.csv, ordenado pelas colunas ID, Time1, Time2, GolsTime1 e GolsTime2, com os valores separados por vírgula simples.

ESTRUTURA DO PROJETO
O projeto está organizado por diretórios, com arquivos .c e .h em cada um. Estão separados em:
    time: onde estão depositados os TADs Time e BDTime;
    partida: onde estão depositados os TADs Partida e BDPartida;
    auxiliares: onde estão uma macro e uma função usados por todo o sistema;
    tabela_classificação: onde estão os arquivos .c e .h para a terceira funcionalidade, de imprimir a tabela de classificação;
    e tabelas: onde estão os arquivos de texto com os dados de time e partida.

Fora dos diretórios ainda há a função principal (main), responsável pela entrada e saída principal do sistema.

DECISÕES DE IMPLEMENTAÇÃO
Os principais TADs (Tipo Abstrato de Dados) utilizados foram: 
    Time, que é responsável por armazenar os dados de um único time por vez;
    BDTime, responsável por armazenar todos os times, e processar informações referentes a mais de um time por vez;
    Partida, que assim como Time, é responsável por armazenar os dados de uma única partida por vez;
    e BDPartida, responsável por armazenar todos os times, e processar informações referentes a mais de um time por vez.

Durante a implementação do sistema, uma das prioridades foi a reutilização de código, uma vez que a segunda funcionalidade utiliza funções já implementadas pela primeira, e o mesmo da terceira com a segunda. As boas práticas da programação também foram contempladas, como não repetição de funcionalidades, agrupamento de responsabilidades, modularização, entre outros.