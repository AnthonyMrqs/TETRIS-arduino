# TETRIS-arduino

Este relatório analisa o código-fonte de um jogo Tetris implementado em um sistema embarcado, fornecendo uma explicação detalhada das funções e discutindo o uso dos critérios especificados.

#Descrição Geral do Código:
- O código implementa um jogo Tetris em um sistema embarcado, utilizando um display LCD e botões como dispositivos de entrada e saída.
- O jogador controla a queda e a posição das peças Tetris usando os botões, e o jogo é exibido no display LCD.
- O código gerencia o estado do jogo, pontuação, recordes e interações com o usuário.

#Critérios Utilizados:

○	Dispositivos de Entrada e Saída: Os botões são utilizados como dispositivos de entrada para permitir ao jogador controlar o movimento das peças Tetris. O display LCD é usado como dispositivo de saída para exibir o estado atual do jogo, incluindo o tabuleiro, o score e as mensagens.
○	Processamento de Dados de Entrada: O código processa os dados de entrada dos botões para determinar o movimento das peças Tetris no tabuleiro. Ele verifica os estados dos botões e calcula a posição e a rotação das peças em resposta às entradas do jogador.
○	Uso da Memória Não Volátil: A memória EEPROM é utilizada para armazenar e recuperar os recordes mais altos alcançados pelos jogadores. Isso garante que os recordes persistam mesmo quando o sistema é desligado ou reiniciado.
○	Uso da Classe Serial e do Buffer: A comunicação serial é inicializada no setup do código, mas não é usada ativamente no jogo Tetris. A classe Serial pode ser usada para depuração e comunicação com outros dispositivos, se necessário.

#Análise Detalhada das Funções:

Setup():

○	Esta função é chamada uma vez quando o programa começa a ser executado.
○	Ela configura os pinos dos botões como entradas e inicializa os objetos dos displays LCD.
○	Inicia a comunicação serial para depuração.
○	Lê os registros de pontuação armazenados na EEPROM e os armazena na lista topScores.

Loop():
○	O loop principal do programa.
○	Verifica se a condição do jogo é verdadeira (ainda em execução).
○	Se verdadeira, exibe o título do jogo e o score atual no LCD, e chama a função rolling() para continuar o jogo.
○	Se não, chama a função endGame() para finalizar o jogo.

ReadButton():
○	Esta função é responsável por ler o estado do botão de movimento.
○	Ela alterna o estado da variável j entre 0 e 1, que controla o movimento horizontal da peça no jogo.

ForwardButton():
○	Lê o estado do botão de velocidade.
○	Define a variável speed com base no estado do botão, controlando a velocidade de descida da peça no jogo.

Rolling():
○	Implementa a lógica principal do jogo Tetris.
○	Move a peça para baixo, verifica colisões, processa entrada de botões, atualiza o score, elimina linhas completas e atualiza a exibição no LCD.

●	Down(int j):
Esta função é chamada para mover as linhas do jogo uma posição para baixo a partir da linha especificada j.
É usada para simular a queda das peças no jogo Tetris.

AddPiece(int i, int j):
○	Adiciona uma peça ao jogo na posição especificada (i, j).
○	Verifica se a posição já está ocupada por outra peça. Se estiver, isso indica o fim do jogo.

Check(int i, int j):
○	Verifica se há uma peça na posição (i+1, j).
○	É usada para detectar colisões e impedir que a peça desça mais quando atingir o fundo do tabuleiro ou encontrar outra peça.

EliminateLines():
○	Verifica se há linhas completas no tabuleiro e as elimina.
○	Adiciona pontos ao score do jogador para cada linha eliminada com sucesso.

AddScore():
Adiciona pontos ao score do jogador.
○	Atualiza a exibição do score no LCD.

PrintGame():

- Exibe o estado atual do jogo no display LCD.
- UpdateTopScores(int newScore):
- Atualiza a lista de recordes com base no novo score obtido pelo jogador.

EndGame():
■	Esta função é chamada quando o jogo termina.
■	Exibe uma mensagem de fim de jogo no LCD.
■	Verifica se o jogador alcançou um novo recorde e, se sim, atualiza e exibe os recordes.
■	Armazena os recordes atualizados na EEPROM.
■	Entra em loop infinita até o jogador pressionar o botão de reset da placa Arduino.

ClearGame():
■	Limpa a matriz do jogo, definindo todas as posições como vazias.
■	ReadRecordFromEEPROM(int m):
■	Lê o registro de recorde na posição m da EEPROM e o retorna.
■	StoreRecordToEEPROM(int m, int record):
■	Armazena o recorde na posição m da EEPROM.

#Link do projeto utilizando o software TinkerCad:

https://www.tinkercad.com/things/jvSQotYC8ll-tetris-/editel?returnTo=%2Fdashboard%2Fdesigns%2Fcircuits&sharecode=1hA3PHpdNnxLeQcA-JPobLtYrjx0gyKspn2shekacgM

