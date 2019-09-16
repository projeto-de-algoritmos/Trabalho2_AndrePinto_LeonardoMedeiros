# Aplicação dos algoritmos de grafos 2

2º Exercício Prático - Projeto de análise de algoritmos - 2019.2 - UnB - Gama
=========================
André Lucas de Sousa Pinto - 17/0068251
Leonardo de Araujo Medeiros - 17/0038891

## Instalação
1. Faça o clone deste projeto com o comando ```$ git clone https://github.com/projeto-de-algoritmos/Trabalho2_AndrePinto_LeonardoMedeiros.git ```;
2. Altere para a o diretório do projeto com o comando ```$ cd Trabalho2_AndrePinto_LeonardoMedeiros/```;
3. Use o comando ```$ make``` para compilar o projeto;
4. Use a o comando ```$ make run speed=NUMERO``` para executar a aplicação. NUMERO deve ser um valor numérico de 1 a 20.

OBS: caso não seja passada speed, ou nao seja um valor numérico de 1 a 20 o mesmo irá ter o valor de 2.

## História
Nesse jogo, em um mundo Pós-Apocalíptico existem apenas duas pessoas no mundo, Antonieta e Carvalho. Carvalho pretende passar o resto de sua vida em paz, longe de problemas e curtindo até o último dia. Antonieta esta prestes a mudar isso, o único problema é que ela não sabe aonde ele está e precisa encontrá-lo.

## Ideia proposta
A ideia era criar um labirinto utilando o algoritmo de kruskal (árvore geradora mínima - minimal spanning tree), criando um labirinto que exista um e apenas um caminho entre qualquer dois pontos.

## Dependências
- g++ compiler

 Nota: Para desenvolvimento deste projeto também é feito uso da biblioteca [SFML](https://www.sfml-dev.org/index.php), todavia esta já se encontra inclusa no repositório a fim de faciltiar a instalação da aplicação. Respeitando devidamente a [licença](https://www.sfml-dev.org/license.php) sobre o código da biblioteca utilizada.
