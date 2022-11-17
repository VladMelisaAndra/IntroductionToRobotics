const int joyXPin = A0;
const int joyYPin = A1;
const int joySWPin = 2;

const int joyMinThreshold = 400;
const int joyMaxThreshold = 700;

unsigned long lastjoySWPress = 0;
const int joySwPressThreshold = 800;

int joyX, joyY;

bool joyMoved = false;
bool joySWState = HIGH;
bool joyPrevSWState = HIGH;

const int latchPin = 11; 
const int clockPin = 10; 
const int dataPin = 12; 

const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

const byte regSize = 8; 

int displayDigits[] = {
  segD1, segD2, segD3, segD4
};
const int displayCount = 4;
const int encodingsNumber = 16;

unsigned long lastBlink = 0;
const int blinkInterval = 500;
int blinkValue = LOW;

int display[displayCount] = {0, 0, 0, 0};

int byteEncodings[encodingsNumber] = {
//A B C D E F G DP 
  B11111100, // 0 
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B11101110, // A
  B00111110, // b
  B10011100, // C
  B01111010, // d
  B10011110, // E
  B10001110  // F
};

int currentState = 1;
int currentPosition = 0;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  for (int i = 0; i < displayCount; i++) {
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], LOW);
  }  
  pinMode(joySWPin, INPUT_PULLUP);
}

void loop() {
  joyX = analogRead(joyXPin);
  joyY = analogRead(joyYPin);

  if(currentState == 1) {
    if(joyY < joyMinThreshold && joyMoved == false) { // LEFT
      if(currentPosition - 1 >= 0)
        currentPosition--;
      joyMoved = true;
    } else if(joyY > joyMaxThreshold && joyMoved == false) { // RIGHT
      if(currentPosition + 1 <= displayCount - 1)
        currentPosition++;
      joyMoved = true;
    }
    
  } else if (currentState == 2) {
    if(joyX > joyMaxThreshold && joyMoved == false) { // UP
      if(display[currentPosition] + 1 <= encodingsNumber - 1)
        display[currentPosition]++;
      joyMoved = true;
    } else if(joyX < joyMinThreshold && joyMoved == false) {// DOWN
      if(display[currentPosition] -1 >= 0)
        display[currentPosition]--;
      joyMoved = true;
    }
  }
    
  if(joyX >= joyMinThreshold && joyX <= joyMaxThreshold && joyY >= joyMinThreshold && joyY <= joyMaxThreshold) // joy is neutral
    joyMoved = false;
  
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

  writeNumber();
} 

void changeState() {
 if(currentState == 1)
    currentState = 2;
  else  
    currentState = 1;
}

void resetDisplay() {
  for (int i = 0; i < displayCount; i++)
    display[i] = 0;
  currentPosition = 0;
  currentState = 1;
}

void writeReg(int digit) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, digit);
    digitalWrite(latchPin, HIGH);
}

void activateDisplay(int displayNumber) { 
  for (int i = 0; i < displayCount; i++) {
    digitalWrite(displayDigits[i], HIGH);
  }
  digitalWrite(displayDigits[displayNumber], LOW);
}

void writeNumber() {
  int currentIndex = 0; 
  for (int i = 0; i <= displayCount - 1; i++) {
    int encoding = byteEncodings[display[i]];

    if(currentIndex == currentPosition) {
      if (currentState == 1 && millis() - lastBlink > blinkInterval) {
        blinkValue = !blinkValue;
        lastBlink = millis();
      } else if (currentState == 2 || blinkValue) 
        encoding++;  
    }      

    writeReg(encoding);
    activateDisplay(currentIndex);
    currentIndex++;
    delay(5);
  }
}