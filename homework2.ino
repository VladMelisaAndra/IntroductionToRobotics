const int greenForPeopleLedPin = 9;
const int redForPeopleLedPin = 8;

const int greenForCarsLedPin = 7;
const int yellowForCarsLedPin = 6;
const int redForCarsLedPin = 5;

const int buttonPin = 4;
const int buzzerPin = 3;
  
byte reading = LOW;
byte lastReading = LOW;
byte buttonState = LOW;
byte buttonWasPressed = LOW;

unsigned long lastStateTime = 0;
unsigned long lastDebounceTime = 0;
unsigned int debounceDelay = 50;

unsigned long lastToneBuzzer = 0;
const int fastBuzzerInterval = 300;
const int slowBuzzerInterval = 550;
const int buzzerFrequency = 300;
const int buzzerDuration = 150;

unsigned long lastGreenBlinkForPeople = 0;
const int greenBlinkForPeopleInterval = 500;
int greenBlinkForPeopleLedValue = LOW;

int state = 1;
int durationStateOne = 8000;
int durationStateTwo = 3000;
int durationStateThree = 8000;
int durationStateFour = 4000;

 
void setup() {
  pinMode(buttonPin, INPUT_PULLUP);

  pinMode(greenForPeopleLedPin, OUTPUT);
  pinMode(redForPeopleLedPin, OUTPUT);

  pinMode(greenForCarsLedPin, OUTPUT);
  pinMode(yellowForCarsLedPin, OUTPUT);
  pinMode(redForCarsLedPin, OUTPUT);
}
 
void loop() {
  reading = digitalRead(buttonPin);
 
  if(reading != lastReading) {
      lastDebounceTime = millis();
  }
 
  if(millis() - lastDebounceTime > debounceDelay) {
    if(reading != buttonState) {
      buttonState = reading;
      if(buttonState == LOW) {
        buttonWasPressed = HIGH;
        lastStateTime = millis();
      }
    }
  }

  if(state == 1 && buttonWasPressed == HIGH && millis() - lastStateTime > durationStateOne) {
    buttonWasPressed = LOW;
    state = 2;
    lastStateTime = millis();
  } else if(state == 2 && millis() - lastStateTime > durationStateTwo) {
    state = 3;
    lastStateTime = millis();
  } else if(state == 3 && millis() - lastStateTime > durationStateThree) {
    state = 4;
    lastStateTime = millis();
  } else if(state == 4 && millis() - lastStateTime > durationStateFour) {
    state = 1;
    lastStateTime = millis();
  }

  if(state == 1) {
    digitalWrite(redForCarsLedPin, LOW);
    digitalWrite(greenForPeopleLedPin, LOW);
    digitalWrite(greenForCarsLedPin, HIGH);
    digitalWrite(redForPeopleLedPin, HIGH);
  } else if(state == 2) {
    digitalWrite(greenForCarsLedPin, LOW);
    digitalWrite(yellowForCarsLedPin, HIGH);
  } else if(state == 3) {
    if (millis() - lastToneBuzzer > slowBuzzerInterval) {
      lastToneBuzzer = millis();
      tone(buzzerPin, buzzerFrequency, buzzerDuration);
    }
    digitalWrite(yellowForCarsLedPin, LOW);
    digitalWrite(redForCarsLedPin, HIGH);
    digitalWrite(redForPeopleLedPin, LOW);
    digitalWrite(greenForPeopleLedPin, HIGH);
  } else if (state == 4) {
      if (millis() - lastToneBuzzer > fastBuzzerInterval) {
        lastToneBuzzer = millis();
        tone(buzzerPin, buzzerFrequency, buzzerDuration);
    }   
    if (millis() - lastGreenBlinkForPeople > greenBlinkForPeopleInterval) {
      greenBlinkForPeopleLedValue = !greenBlinkForPeopleLedValue;
      lastGreenBlinkForPeople = millis();
    }
    digitalWrite(greenForPeopleLedPin, greenBlinkForPeopleLedValue);
  }
 
  lastReading = reading;
}