#include <Servo.h>

#define FIRST_LED_PIN 14
#define LAST_LED_PIN 53
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
 int input = Serial.read();
 // line feed
 if (input == 10) {
   return;
 }
 input = input - 48;
 if (first == -1) {
   first = input;
 }
 else {
   percent = (first * 10) + input;
   first = -1;
 }
}

void startupSequence() {
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(FIRST_LED_PIN + i, OUTPUT);
  }
  
  calculateExternals(float(0));
  delay(1000);
  for (int i = 0; i <= 100; i++) {
    calculateExternals(float(i));
    unsigned long endTime = millis() + 15;
    while (millis() < endTime) {
      updateLEDs(); 
    }
  }
  for (int i = 180; i >= 0; i--) {
    calculateExternals(float(i));
    unsigned long endTime = millis() + 15;
    while (millis() < endTime) {
      updateLEDs(); 
    }
  }
}

void loop() {
  if (Serial.available()) {
    parseInput();
    calculateExternals(percent);
  }
  
  updateLEDs();
}

void calculateExternals(float percent) {
  percent = percent/float(100);
  percent = min(1, max(0, percent));
  servoDegrees = MAX_DEGREES - (percent * (MAX_DEGREES - MIN_DEGREES));

  numLedsLit = round(percent * float(NUM_LEDS));
  servo1.write(servoDegrees);
}
  
void updateLEDs() {
  for (int i = LAST_LED_PIN; i > LAST_LED_PIN-numLedsLit; i-=5) {
    for(int j = 0; j < 5 && i-j > LAST_LED_PIN-numLedsLit; j++) {
      digitalWrite(i - j, HIGH);
    }
    delay(1);
    for(int j = 0; j < 5 && i-j > LAST_LED_PIN-numLedsLit; j++) {
      digitalWrite(i - j, LOW);
    }
  }
}
