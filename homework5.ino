#include <LiquidCrystal.h>
#include <EEPROM.h>

const int lcdNumberOfColumns = 16;
const int lcdNumberOfRows = 3;

const byte rs = 9;
const byte en = 8;
const byte d4 = 7;
const byte d5 = 6;
const byte d6 = 5;
const byte d7 = 4;

const byte lcdContrastPin = 3;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte lcdContrast;

const int joyXPin = A0;
const int joyYPin = A1;
const int joySWPin = 2;

const int joyLeftThreshold = 400;
const int joyRightThreshold = 600;

bool joyIsNeutral = true;
bool joySWState = HIGH;
bool joyPrevSWState = HIGH;

unsigned long lastjoySWPress = 0;
const int joySwPressThreshold = 800;

const int startGameMenuOption = 0;
const int highscoreMenuOption = 1;
const int settingsMenuOption = 2;
const int aboutMenuOption = 3;
const int howToPlayMenuOption = 4;

const int gameMenuIsLoading = -1;
const int gameMenuOptionOverflow = 5;
int currentMenuOption = gameMenuIsLoading;

int gameOpenedTimer;
const int welcomeMessageInterval = 4000;

int gameLevel = 1;
int highscore = 0;

bool enteredTheOptionFeatures = false;

void setup() {
  pinMode(lcdContrastPin, OUTPUT);

  lcd.begin(lcdNumberOfColumns, lcdNumberOfRows);
  lcd.print("Welcome!");

  EEPROM.update(0, highscore);
  analogWrite(lcdContrastPin, lcdContrast);
  pinMode(joySWPin, INPUT_PULLUP);
  analogWrite(lcdContrastPin, lcdContrast);

  gameOpenedTimer = millis();
}

void loop() {
  if(currentMenuOption == gameMenuIsLoading && millis() - gameOpenedTimer > welcomeMessageInterval)
  {
    currentMenuOption = startGameMenuOption;
    print();
  }

  int joyX = analogRead(joyXPin);
  int joyY = analogRead(joyYPin);

  if(joyX >= joyLeftThreshold && joyX <= joyRightThreshold && joyY >= joyLeftThreshold && joyY <= joyRightThreshold) 
    joyIsNeutral = true;
      
  if (joyX > joyRightThreshold && joyIsNeutral && enteredTheOptionFeatures == false) {
    currentMenuOption--;
    if (currentMenuOption == gameMenuIsLoading){
      currentMenuOption = howToPlayMenuOption;
    }
    joyIsNeutral = false;
    print();
  }

  if (joyX < joyLeftThreshold && joyIsNeutral && enteredTheOptionFeatures == false) {
    currentMenuOption++;
    if (currentMenuOption == gameMenuOptionOverflow)
      currentMenuOption = startGameMenuOption;
    joyIsNeutral = false;
    print();

  }

  if(joyY < joyLeftThreshold && joyIsNeutral && enteredTheOptionFeatures == true) {
    enteredTheOptionFeatures = false;
    print();
  }
   
  if(joyY > joyRightThreshold && joyIsNeutral && enteredTheOptionFeatures == true) {
    enteredTheOptionFeatures = false;   
    print(); 
  }

  joySWState = digitalRead(joySWPin);
  if(joySWState != joyPrevSWState){
    if(joySWState == LOW){
      enterTheOptionFeatures();
    }
    joyPrevSWState = joySWState;
  }
}

void print() {
  lcd.clear();
  if(currentMenuOption == startGameMenuOption)
    lcd.print("Start game");  
  else if(currentMenuOption == highscoreMenuOption)
    lcd.print("Highscore");
  else if(currentMenuOption == settingsMenuOption)
    lcd.print("Settings");  
  else if(currentMenuOption == aboutMenuOption)
    lcd.print("About");
  else if(currentMenuOption == howToPlayMenuOption)
    lcd.print("How to play");  
}

void enterTheOptionFeatures() {
  lcd.clear();
  enteredTheOptionFeatures = true;
  if(currentMenuOption == startGameMenuOption) {
    gameLevel = 1;
    lcd.print("Game started!");     
    delay(1000);
    lcd.clear();
    lcd.print("Congrats! You");
    goToNextLcdLine();
    lcd.print("reached score 20!");
  } else if(currentMenuOption == highscoreMenuOption) {
    highscore = EEPROM.read(0);
    lcd.print("Highscore: "); 
    lcd.print(highscore);     
  } else if(currentMenuOption == settingsMenuOption) {
    lcd.print("Settings Menu");    
  } else if(currentMenuOption == aboutMenuOption) {
    lcd.print("Snake Game by");    
    goToNextLcdLine();
    lcd.print("Vlad Melisa");   
  } else if(currentMenuOption == howToPlayMenuOption) {
    lcd.print("Eat food and");    
    goToNextLcdLine();
    lcd.print("avoid obstacles.");   
  }
}

void goToNextLcdLine() {
  lcd.setCursor(0, 1);
}

