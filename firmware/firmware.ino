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
  startupSequence();
  servoDegrees = 90;
}

void loop() {
//  if (Serial.available()) {
//    servoDegrees = min(180, max(0, Serial.read())); 
//    numLedsLit = float(servoDegrees)/MAX_DEGREES * NUM_LEDS;
//  }
  
  updateExternals();

}

void startupSequence() {
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(FIRST_LED_PIN + i, OUTPUT);
    digitalWrite(FIRST_LED_PIN + i, HIGH);
    delay(200);
    digitalWrite(FIRST_LED_PIN + i, LOW);
  }
  
//  for (int i = 0; i <= 180; i++) {
//    servo1.write(i);
//    delay(150);
//  }
  
  for (int i = 0; i <= 180; i++) {
    servoDegrees = i;
    numLedsLit = float(servoDegrees)/MAX_DEGREES * NUM_LEDS;
    int endTime = millis() + 200;
    while (millis() < endTime) {
      updateExternals();
    }
  }
}

void delayMicros(long usec) {
  unsigned long start = micros(); 
  while (micros() - usec < start) {}  
}
  
void updateExternals() {
  servo1.write(servoDegrees);
  
  for (int i = FIRST_LED_PIN; i < FIRST_LED_PIN+numLedsLit; i+=5) {
    for (int j = 0; j < 5 && i + j < FIRST_LED_PIN+numLedsLit; j++) {
      digitalWrite(i + j, HIGH);
    }
  }

  delay(100);
  
  for (int i = FIRST_LED_PIN; i < FIRST_LED_PIN+numLedsLit; i+=5) {
    for (int j = 0; j < 5 && i + j < FIRST_LED_PIN+numLedsLit; j++) {
      digitalWrite(i + j, LOW);
    }
  }
}
