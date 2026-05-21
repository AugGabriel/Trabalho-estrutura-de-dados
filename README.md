# Trabalho-estrutura-de-dados

Trabalho da matéria de Estrutura de Dados, curso de Bacharelado de Sistemas de Informação, IFES Campus Serra.

**Alunos:** Gabriel Augusto Pereira e João Vitor Calmon Castiglioni Rangel Pôrto.

## EXECUÇÃO

O método de execução recomendado e que foi usado durante o desenvolvimento do projeto é:
1. Abra um terminal Ubuntu (versão 24.04 recomendada), nativo ou via WSL (Subsistema do Windows para Linux).
2. Caso não tiver GCC e Make, instale com o comando: `sudo apt update && sudo apt install build-essential gdb -y`.
4. Navegue até o diretório raiz do projeto e digite `make`.
5. A partir desse momento, o sistema será compilado e executado. Basta seguir as instruções apresentadas nas saídas do terminal.

Para mudar as partidas que serão carregadas no sistema, basta copiar e colar os dados para o arquivo `partidas.csv`, ordenado pelas colunas **ID**, **Time1**, **Time2**, **GolsTime1** e **GolsTime2**, com os valores separados por vírgula simples.

## ESTRUTURA DO PROJETO

O projeto está organizado por diretórios, com arquivos `.c` e `.h` em cada um. Estão separados em:

* **`time`**: onde estão depositados os TADs Time e BDTime.
* **`partida`**: onde estão depositados os TADs Partida e BDPartida.
* **`auxiliares`**: onde estão uma macro e uma função usados por todo o sistema.
* **`tabela_classificação`**: onde estão os arquivos `.c` e `.h` para a terceira funcionalidade, de imprimir a tabela de classificação.
* **`tabelas`**: onde estão os arquivos de texto com os dados de time e partida.

E na pasta raíz, ainda há o arquivo com a função principal (`main.c`), que é o ponto de entrada para o sistema.

## DECISÕES DE IMPLEMENTAÇÃO

Os principais TADs (Tipo Abstrato de Dados) utilizados foram:

* **Time**, que é responsável por armazenar os dados de um único time por vez.
* **BDTime**, responsável por armazenar todos os times, e processar informações referentes a mais de um time por vez.
* **Partida**, que assim como Time, é responsável por armazenar os dados de uma única partida por vez.
* e **BDPartida**, responsável por armazenar todos os times, e processar informações referentes a mais de um time por vez.

Durante a implementação do sistema, a reutilização de código foi uma prioridade, uma vez que a segunda funcionalidade utiliza funções já implementadas pela primeira, e o mesmo acontece entre a terceira e a segunda. Outras boas práticas da programação também foram base, como a não repetição de funcionalidades, agrupamento de responsabilidades e modularização.

A estrutura de pastas do projeto foi pensada para agrupar funcionalidades relacionadas, além de manter arquivos `.h` próximos dos `.c` correspondentes. Dessa forma, fica mais organizado e fácil de navegar. O Makefile foi configurado para incluir corretamente as subpastas na compilação, além de despejar todos os fragmentos .o e .d numa outra, de nome .build, mantendo o espaço de trabalho limpo.
