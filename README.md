# Trabalho-estrutura-de-dados

Trabalho da matéria de Estrutura de Dados, curso de Bacharelado de Sistemas de Informação, IFES Campus Serra. O sistema gerencia um campeonato de futebol, permitindo consultar times e partidas, inserir, atualizar e remover partidas, e imprimir a tabela de classificação, por meio de um menu interativo no terminal.

**Alunos:** Gabriel Augusto Pereira e João Vitor Calmon Castiglioni Rangel Pôrto.

## EXECUÇÃO

O método de execução recomendado e que foi usado durante o desenvolvimento do projeto é:
1. Abra um terminal Ubuntu (versão 24.04 recomendada), nativo ou via WSL (Subsistema do Windows para Linux).
2. Caso não tiver GCC e Make, instale com o comando: `sudo apt update && sudo apt install build-essential gdb -y`.
3. Navegue até o diretório raiz do projeto e digite `make`.
4. A partir desse momento, o sistema será compilado e executado. Basta seguir as instruções apresentadas nas saídas do terminal.

### Utilização

O programa apresenta um menu em loop com as seguintes opções:

1. **Consultar time**: busca por nome ou prefixo, case-insensitive.
2. **Consultar partidas**: filtra por time mandante, visitante, ou ambos.
3. **Atualizar partida**: altera os placares de uma partida.
4. **Remover partida**.
5. **Inserir partida**.
6. **Imprimir tabela de classificação**: exibe tabela com estatísticas de todos os times.
* **Q**: sair. Ao sair, as alterações feitas nas partidas são salvas no arquivo de partidas.

### Dados

Os dados carregados/salvos ficam na pasta `tabelas`:

* **`tabelas/times.csv`**: um time por linha, no formato `id,nome`.
* **`tabelas/partidas.csv`**: uma partida por linha, no formato `ID,Time1,Time2,GolsTime1,GolsTime2`, com os valores separados por vírgula simples. `Time1` é o id do time mandante e `Time2` é o id do time visitante.

Para mudar as partidas que serão carregadas no sistema, basta editar o arquivo `tabelas/partidas.csv`, respeitando o formato acima.

## ESTRUTURA DO PROJETO

O projeto está organizado por diretórios, com os arquivos `.c` e `.h` correspondentes em cada um. Estão separados em:

* **`acoes_menu`**: funções que implementam as ações do menu (as 6 funcionalidades), fazendo a ponte entre a entrada do usuário e os TADs.
* **`linkedlist`**: TAD LinkedList genérico (lista simplesmente encadeada), que armazena tanto Time quanto Partida através de um enum `NodeType`.
* **`time`**: onde estão depositados os TADs Time e BDTimes.
* **`partida`**: onde estão depositados os TADs Partida e BDPartidas.
* **`auxiliares`**: onde estão as macros globais (caminhos dos arquivos, tamanho máximo de entrada) e as funções de comparação de strings/char sem diferenciar maiúsculas de minúsculas.
* **`tabelas`**: onde estão os arquivos `.csv` com os dados de times e partidas.

Na pasta raiz, ainda há o arquivo com a função principal (`main.c`), que é o ponto de entrada e contém o loop do menu, além do `Makefile` e este `README.md`. O Makefile inclui automaticamente as subpastas na compilação e joga os fragmentos `.o` e `.d` numa pasta `.build`, mantendo o espaço de trabalho limpo.

## DECISÕES DE IMPLEMENTAÇÃO

Os principais TADs (Tipo Abstrato de Dados) utilizados foram:

* **LinkedList**, lista simplesmente encadeada genérica que armazena elementos de tipos diferentes (Time ou Partida) usando um enum `NodeType`. É a base de armazenamento dos dois bancos de dados, com operações de criar, inserir no início, inserir no fim (append), remover, obter por posição, tamanho, imprimir e liberar.
* **Time**, responsável por armazenar os dados de um time (id, nome, vitórias, empates, derrotas, gols marcados/sofridos) e calcular propriedades derivadas (saldo de gols e pontos ganhos).
* **BDTimes**, responsável por armazenar e gerenciar todos os times (usando uma LinkedList), com busca por id, por índice e por nome/prefixo.
* **Partida**, que assim como Time é responsável por armazenar os dados de uma única partida por vez (id, os dois times e os gols de cada um), podendo também aplicar e/ou reverter sua contribuição nas estatísticas dos times.
* **BDPartidas**, responsável por armazenar e gerenciar todas as partidas (usando uma LinkedList), com carregamento/gravação em arquivo, inserção, remoção e busca de partidas.

As principais decisões de implementação foram:

* **Lista simplesmente encadeada genérica**: o mesmo TAD LinkedList é usado nos dois TADs de banco de dados para criar a lista interna de cada um. Guarda o tipo de cada nó (`NodeType`) para despachar corretamente na impressão e na liberação de memória.
* **Referência de times por ID**: as partidas referenciam os times buscando pelo id (`bdt_obter_por_id`), e não pela posição na lista, de forma que a lógica seja robusta independente da ordem de inserção dos elementos.
* **Preservação da ordem do arquivo**: os dados são inseridos no fim da lista (append), preservando a ordem do arquivo original e evitando que a ordem se inverta a cada gravação.
* **Estatísticas incrementais**: as estatísticas de cada time são mantidas atualizadas incrementalmente a cada operação de CRUD, por uma única função que aplica ou reverte a contribuição de uma partida (`partida_aplicar_resultado()`). No carregamento, cada partida é aplicada uma vez; ao inserir, remover ou atualizar, o resultado é aplicado ou revertido. Isso evita recalcular tudo a cada exibição e mantém a tabela de classificação sempre coerente.
* **Reutilização de código**: a funcionalidade 2 (consultar partidas) reaproveita a busca de times da funcionalidade 1; as funcionalidades 3 e 4 (atualizar e remover) reaproveitam a consulta de partidas da funcionalidade 2. Outras boas práticas também foram base, como a não repetição de funcionalidades, o agrupamento de responsabilidades e a modularização.
* **Persistência**: as alterações feitas nas partidas são gravadas de volta no arquivo `partidas.csv` ao sair do programa.
* **Busca flexível de times**: a consulta aceita nome completo ou prefixo, sem diferenciar maiúsculas de minúsculas.
* **Organização em pastas + Makefile**: a estrutura de pastas agrupa TADs relacionados, mantendo os arquivos `.h` próximos dos `.c` correspondentes. O Makefile inclui corretamente as subpastas na compilação e isola os artefatos de build (`.o` e `.d`) na pasta `.build`, mantendo o espaço de trabalho limpo.
