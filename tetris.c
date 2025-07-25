#include <LiquidCrystal.h>
#include <Adafruit_LiquidCrystal.h>
#include <EEPROM.h>
#define botao 13
#define botaoF 8
#define NUM_TOP_SCORES 3

Adafruit_LiquidCrystal lcd_1(0);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Pinos do display LCD

int estadoBotao  = 0;
int estadoBotaoF = 0;
int i_ant = 0, j_ant = 0;
int j = 0;
int score = 0;
int speed = 0;
int record = 0;
char condition = 1;

int topScores[NUM_TOP_SCORES] = {0}; // Inicializa a lista com zeros

char game[][17] = {"      |         ", "      |         "};

void setup() {
  pinMode(botao, INPUT_PULLUP);
  pinMode(botaoF, INPUT_PULLUP);
  lcd_1.begin(16, 2);
  lcd.begin(16, 2);
  Serial.begin(9600);

  // Lendo os registros de pontuação da EEPROM e armazenando na lista topScores
  for (int i = 0; i < NUM_TOP_SCORES; i++) {
    int storedScore = EEPROM.read(i * sizeof(int));
    topScores[i] = storedScore;
  }
}

void loop() {
  if (condition == 1) {
    lcd_1.setCursor(0, 0);
    lcd_1.print("T  E  T  R  I  S");
    lcd_1.setCursor(0, 1);
    lcd_1.print("Score :");
    lcd_1.setCursor(9, 1);
    lcd_1.print(score);
    rolling();
  } else {
    endGame();
  }
}

void readButton() {
  estadoBotao = digitalRead(botao);
  if (estadoBotao == HIGH) {
    j = abs(j - 1);
  }
  delay(10);
}

void forwardButton() {
  estadoBotaoF = digitalRead(botaoF);
  if (estadoBotaoF == HIGH)
    speed = 750;
  else
    speed = 0;
  delay(10);
}

void rolling() {
  int i = 7;
  printGame();

  for (; i < 16; i++) {
    readButton();
    if (check(i, j)) {
      i++;
      break;
    }
    if (i > 7) {
      lcd.setCursor(i_ant, j_ant);
      lcd.write(' ');
    }

    lcd.setCursor(i, j);
    lcd.write('*');
    j_ant = j, i_ant = i;
    forwardButton();
    delay(500 - speed);
  }

  addPiece(i - 1, j);
  printGame();
  delay(500);
  eliminateLines();
  printGame();
}

void down(int j) {
  for (int i = j; i > 7; i--) {
    game[0][i] = game[0][i - 1];
    game[1][i] = game[1][i - 1];
  }
  game[0][7] = ' ';
  game[1][7] = ' ';
}

void addPiece(int i, int j) {
  if (game[j][i] == '*') {
    condition = 0;
    return;
  }
  game[j][i] = '*';
}

int check(int i, int j) {
  if (game[j][i + 1] == '*') {
    return 1;
  }
  return 0;
}

void eliminateLines() {
  for (int j = 7; j < 16; j++) {
    if (game[0][j] == '*' && game[1][j] == '*') {
      addScore();
      game[0][j] = ' ';
      game[1][j] = ' ';
      printGame();
      delay(500);
      down(j);
    }
  }
}

void addScore() {
  lcd_1.setBacklight(0);
  delay(100);
  score += 5;
  lcd_1.setCursor(9, 1);
  lcd_1.print(score);
  lcd_1.setBacklight(1);
  delay(100);
}

void printGame() {
  for (int i = 0; i < 2; i++) {
    lcd.setCursor(0, i);
    lcd.print(game[i]);
  }
}

void updateTopScores(int newScore) {
  if (newScore >= topScores[0]) {
    topScores[2] = topScores[1];
    topScores[1] = topScores[0];
    topScores[0] = newScore;
  } else if (newScore >= topScores[1]) {
    topScores[2] = topScores[1];
    topScores[1] = newScore;
  } else if (newScore >= topScores[2]) {
    topScores[2] = newScore;
  }
}

void endGame() {
  clearGame();
  
  record = readRecordFromEEPROM(); // Lendo o recorde da EEPROM
  Serial.println(record);
  Serial.println(score);
  
  lcd_1.setCursor(0, 0);
  lcd_1.print(" Y O U  L O S E ");
  
  if (score > record) {
    delay(500);
    lcd_1.setBacklight(0);
    delay(100);
    lcd_1.setBacklight(1);
    delay(100);
    
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print("      NEW       ");
    
    lcd_1.setCursor(0, 1);
    lcd_1.print("     RECORD     ");
    
    lcd_1.setBacklight(0);
    delay(100);
    lcd_1.setBacklight(1);
    delay(100);
    
    delay(500);
    storeRecordToEEPROM(score); // Salvando o novo recorde
    
    // Atualiza a lista de topScores
    updateTopScores(score);
  }
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print(" Score: ");
  lcd_1.print(score);
  
  lcd_1.setCursor(0, 1);
  lcd_1.print(" Record: ");
  lcd_1.print(record); // Mostrando o recorde
  
  // Exibe os três melhores recordes no monitor serial
  Serial.println("Top 3 Scores:");
  for (int i = 0; i < NUM_TOP_SCORES; i++) {
    Serial.print(i + 1);
    Serial.print(". ");
    Serial.println(topScores[i]);
    
    // Salva os três melhores recordes na EEPROM
    EEPROM.write(i * sizeof(int), topScores[i]);
  }
  
  Serial.print("Do you want to play again? (S or N)\n");
  condition = Serial.read();
 
  delay(10000);
}



void clearGame(){ // funcao para limpar o jogo
  for (int j = 7; j < 16; j++){
    game[0][j] = ' ';
    game[1][j] = ' ';
  }
}


void storeToEEPROM(int score) {
  EEPROM.write(0, score);
}

int readRecordFromEEPROM() {
  return EEPROM.read(0);
}

void storeRecordToEEPROM(int record) {
  EEPROM.write(0, record);
}
