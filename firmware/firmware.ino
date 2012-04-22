#include <Servo.h>

#define FIRST_LED_PIN 22

Servo servo1;

int servoDegrees = 0;

int numLedsLit = 0;

void setup() {
  servo1.attach(9);
}

void loop() {
  servo1.write(servoDegrees);
  
  for (int i = 0; i < numLedsLit; i++) {
    digitalWrite(FIRST_LED_PIN + i, HIGH);
    delay(1);
    digitalWrite(FIRST_LED_PIN + i, LOW);
  }
}
