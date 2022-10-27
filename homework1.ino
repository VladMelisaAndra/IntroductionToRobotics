const int redPotPin = A0;
const int greenPotPin = A1;
const int bluePotPin = A2;

const int blueLedPin = 11;
const int greenLedPin = 10;
const int redLedPin = 9;

const int minimumPotValue = 0;
const int maximumPotValue = 1023;

const int minimumLedValue = 0;
const int maximumLedValue = 255;

bool commonAnode = false;

int redPotValue;
int greenPotValue;
int bluePotValue;

void setup() {
  pinMode(redPotPin, INPUT);
  pinMode(greenPotPin, INPUT);
  pinMode(bluePotPin, INPUT);

  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
}

void loop() {
  redPotValue = map(analogRead(redPotPin), minimumPotValue, maximumPotValue, minimumLedValue, maximumLedValue);
  greenPotValue = map(analogRead(greenPotPin), minimumPotValue, maximumPotValue, minimumLedValue, maximumLedValue);
  bluePotValue = map(analogRead(bluePotPin), minimumPotValue, maximumPotValue, minimumLedValue, maximumLedValue);
  
  setColor(redPotValue, greenPotValue, bluePotValue);
}

void setColor(int redPotValue, int greenPotValue, int bluePotValue) {
  if(commonAnode) {
    redPotValue = maximumLedValue - redPotValue;
    greenPotValue = maximumLedValue - greenPotValue;
    bluePotValue = maximumLedValue - bluePotValue;
  }
  analogWrite(redLedPin, redPotValue);
  analogWrite(greenLedPin, greenPotValue);
  analogWrite(blueLedPin, bluePotValue);
}