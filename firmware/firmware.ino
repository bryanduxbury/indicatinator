#include <Servo.h>

#define FIRST_LED_PIN 14
#define NUM_LEDS 40
#define MAX_DEGREES 180.0

Servo servo1;

int servoDegrees = 0;

int numLedsLit = 0;

void setup() {
  servo1.attach(9);
  Serial.begin(9600);
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(FIRST_LED_PIN + i, OUTPUT);
  }

  startupSequence();
}

void loop() {
  startupSequence();
//  if (Serial.available()) {
//    servoDegrees = min(180, max(0, Serial.read())); 
//    numLedsLit = float(servoDegrees)/MAX_DEGREES * NUM_LEDS;
//  }
//  
//  updateExternals();
}

void startupSequence() {
  for (int i = 0; i <= 180; i++) {
    servoDegrees = i;
    numLedsLit = float(servoDegrees)/MAX_DEGREES * NUM_LEDS;
    int endTime = millis() + 20;
    while (millis() < endTime) {
      updateExternals();
    }
  }
}

void updateExternals() {
  servo1.write(servoDegrees);
  for (int i = 0; i < numLedsLit; i++) {
    digitalWrite(FIRST_LED_PIN + i, HIGH);
    delay(1);
    digitalWrite(FIRST_LED_PIN + i, LOW);
  }
}
