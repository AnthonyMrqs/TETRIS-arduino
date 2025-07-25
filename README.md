# TETRIS-arduino

Este relatório analisa o código-fonte de um jogo Tetris implementado em um sistema embarcado, fornecendo uma explicação detalhada das funções e discutindo o uso dos critérios especificados.

# Descrição Geral do Código:
- O código implementa um jogo Tetris em um sistema embarcado, utilizando um display LCD e botões como dispositivos de entrada e saída.
- O jogador controla a queda e a posição das peças Tetris usando os botões, e o jogo é exibido no display LCD.
- O código gerencia o estado do jogo, pontuação, recordes e interações com o usuário.

# Critérios Utilizados:
- Dispositivos de Entrada e Saída: Os botões são utilizados como dispositivos de entrada para permitir ao jogador controlar o movimento das peças Tetris. O display LCD é usado como dispositivo de saída para exibir o estado atual do jogo.
- Processamento de Dados de Entrada: O código processa os dados de entrada dos botões para determinar o movimento das peças Tetris no tabuleiro.
- Uso da Memória Não Volátil: A memória EEPROM é utilizada para armazenar e recuperar os recordes mais altos alcançados pelos jogadores.
- Uso da Classe Serial e do Buffer: A comunicação serial é inicializada no setup do código, mas não é usada ativamente no jogo Tetris.

# Análise Detalhada das Funções:

Setup():
- Esta função é chamada uma vez quando o programa começa a ser executado.
- Configura os pinos dos botões como entradas e inicializa os objetos dos displays LCD.
- Inicia a comunicação serial para depuração.
- Lê os registros de pontuação armazenados na EEPROM.

Loop():
- O loop principal do programa.
- Verifica se a condição do jogo é verdadeira (ainda em execução).
- Se verdadeira, exibe o título do jogo e o score atual no LCD.
- Se não, chama a função endGame() para finalizar o jogo.

ReadButton():
- Responsável por ler o estado do botão de movimento.
- Alterna o estado da variável j entre 0 e 1.

ForwardButton():
- Lê o estado do botão de velocidade.
- Define a variável speed com base no estado do botão.

Rolling():
- Implementa a lógica principal do jogo Tetris.
- Move a peça para baixo, verifica colisões, processa entrada de botões.

Down(int j):
- Move as linhas do jogo uma posição para baixo a partir da linha especificada j.

AddPiece(int i, int j):
- Adiciona uma peça ao jogo na posição especificada (i, j).
- Verifica se a posição já está ocupada por outra peça.

Check(int i, int j):
- Verifica se há uma peça na posição (i+1, j).

EliminateLines():
- Verifica linhas completas no tabuleiro e as elimina.
- Adiciona pontos ao score do jogador.

AddScore():
- Adiciona pontos ao score do jogador.
- Atualiza a exibição do score no LCD.

PrintGame():
- Exibe o estado atual do jogo no display LCD.

UpdateTopScores(int newScore):
- Atualiza a lista de recordes com base no novo score.

EndGame():
- Chamada quando o jogo termina.
- Exibe mensagem de fim de jogo no LCD.
- Verifica e atualiza recordes.
- Armazena recordes na EEPROM.

ClearGame():
- Limpa a matriz do jogo.

ReadRecordFromEEPROM(int m):
- Lê o registro de recorde na posição m da EEPROM.

StoreRecordToEEPROM(int m, int record):
- Armazena o recorde na posição m da EEPROM.

# Link do projeto utilizando o software TinkerCad:
https://www.tinkercad.com/things/jvSQotYC8ll-tetris-/editel?returnTo=%2Fdashboard%2Fdesigns%2Fcircuits&sharecode=1hA3PHpdNnxLeQcA-JPobLtYrjx0gyKspn2shekacgM
