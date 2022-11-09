const int pinA = 4;
const int pinB = 5;
const int pinC = 6;
const int pinD = 7;
const int pinE = 8;
const int pinF = 9;
const int pinG = 10;
const int pinDP = 11;

const int joyXPin = A0;
const int joyYPin = A1;
const int joySWPin = 2;

const int joyLeftThreshold = 400;
const int joyRightThreshold = 700;

bool joyIsNeutral = true;
bool joySWState = HIGH;
bool joyPrevSWState = HIGH;

int currentState = 1;
const int segSize = 8;
int currentPosition = segSize - 1;

bool commonAnode = false; 

int segments[segSize] = { 
  //0 , 1 ,   2 ,   3 ,   4 ,   5 ,   6 ,   7
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

byte segmentsValues[segSize] = {
// a    b    c    d    e    f    g    dp
  LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW
};

int movementsMatrix[segSize][4] = {
//Left Down Right Up  ( 0-pinA, 1-pinB, 2-pinC, 3-pinD, 4-pinE, 5-pinF, 6-pinG, 7-pinDP)
  {5,  6,   1,  -1}, // a
  {5,  6,   -1,  0}, // b
  {4,  3,   7,  6}, // c
  {4,  -1,  2,   6}, // d
  {-1, 3,   2,   6}, // e
  {-1, 6,   1,   0}, // f
  {-1, 3,   -1,  0}, // g
  {2,  -1,   -1,  -1}, // dp
};

unsigned long lastBlink = 0;
const int blinkInterval = 500;
int blinkValue = LOW;

unsigned long lastjoySWPress = 0;
const int joySwPressThreshold = 800;

void setup() {
  for (int i = 0; i < segSize; i++) 
    pinMode(segments[i], OUTPUT);
  pinMode(joySWPin, INPUT_PULLUP);
}

void loop() {
  int joyX = analogRead(joyXPin);
  int joyY = analogRead(joyYPin);
  
  if (millis() - lastBlink > blinkInterval) {
    blinkValue = !blinkValue;
    lastBlink = millis();
  }

  if(currentState == 1)
    move(joyX, joyY);
  else if ((joyX > joyRightThreshold && joyIsNeutral) || (joyX < joyLeftThreshold && joyIsNeutral)) {
    segmentsValues[currentPosition] = !segmentsValues[currentPosition];
    joyIsNeutral = false;
  }

  if(joyX >= joyLeftThreshold && joyX <= joyRightThreshold && joyY >= joyLeftThreshold && joyY <= joyRightThreshold) 
    joyIsNeutral = true;
  
  setSegments();

  joySWState = digitalRead(joySWPin);
  if(joySWState != joyPrevSWState) {
    if(joySWState == LOW) 
      lastjoySWPress = millis();
    else {
      if(millis() - lastjoySWPress < joySwPressThreshold) 
        changeState();
      else 
        resetDisplay();     
    }
  }
  joyPrevSWState = joySWState;
}

void setSegments() {
  if(currentState == 1)
    digitalWrite(segments[currentPosition], blinkValue);
  for(int i = 0; i < segSize; i++) 
    if(currentState == 2 || i != currentPosition)
      digitalWrite(segments[i], segmentsValues[i] ^ commonAnode);
}

void move(int joyX, int joyY){
  int nextLed = -1;
  if(joyX < joyLeftThreshold && joyIsNeutral) 
    nextLed = movementsMatrix[currentPosition][1];
  if(joyX > joyRightThreshold && joyIsNeutral) 
    nextLed = movementsMatrix[currentPosition][3];
  if(joyY < joyLeftThreshold && joyIsNeutral) 
    nextLed = movementsMatrix[currentPosition][0];
  if(joyY > joyRightThreshold && joyIsNeutral) 
    nextLed = movementsMatrix[currentPosition][2];
  if(nextLed != -1)
      currentPosition = nextLed;  
  joyIsNeutral = false;
}

void changeState() {
 if(currentState == 1)
    currentState = 2;
  else  
    currentState = 1;
}

void resetDisplay() {
  for (int i = 0; i < segSize; i++)
    segmentsValues[i] = 0;
  currentPosition = segSize - 1;
  currentState = 1;
}