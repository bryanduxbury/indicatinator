#include <Servo.h>

#define FIRST_LED_PIN 14
#define NUM_LEDS 40
#define MIN_DEGREES 5
#define MAX_DEGREES 167

Servo servo1;

int servoDegrees = 0;
float percent = 0;

int numLedsLit = 0;

int first = -1;

void setup() {
  servo1.attach(9);
  Serial.begin(9600);
  startupSequence();
  servoDegrees = 0;
}

// Temporary input parsing for debugging
void parseInput() {
 int input = Serial.read() - 48;
 if (first == -1) {
   first = input;
 }
 else {
   percent = (first * 10) + input;
   first = -1;
   Serial.println(percent);
 }
}

void loop() {
  if (Serial.available()) {
    parseInput();
    percent = percent/float(100);
    percent = min(1, max(0, percent));
    servoDegrees = MAX_DEGREES - (percent * (MAX_DEGREES - MIN_DEGREES));

    numLedsLit = round(percent * float(NUM_LEDS));
    servo1.write(servoDegrees);
  }
  
  updateLEDs();
}

void startupSequence() {
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(FIRST_LED_PIN + i, OUTPUT);
//    digitalWrite(FIRST_LED_PIN + i, HIGH);
//    delay(200);
//    digitalWrite(FIRST_LED_PIN + i, LOW);
  }

//  for (int i = 180; i >= 0; i--) {
//    servoDegrees = i;
//    numLedsLit = float(servoDegrees)/MAX_DEGREES * NUM_LEDS;
//    long endTime = millis() + 5;
//    while (millis() < endTime) {
//      updateExternals();
//    }
//  }
}
  
void updateLEDs() {
  for (int i = FIRST_LED_PIN; i < FIRST_LED_PIN+numLedsLit; i+=5) {
    for (int j = 0; j < 5 && i + j < FIRST_LED_PIN+numLedsLit; j++) {
      digitalWrite(i + j, HIGH);
    }
    delay(1);
    for (int j = 0; j < 5 && i + j < FIRST_LED_PIN+numLedsLit; j++) {
      digitalWrite(i + j, LOW);
    }
  }
}
