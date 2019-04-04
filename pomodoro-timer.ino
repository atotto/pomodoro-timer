#include <avr/sleep.h>

const int timerOutPin = 11;
#define analogOutMax 235

void timer() {
  unsigned long startTime = millis();
  long elapsedTime = 0;

  int outputValue = 0;
  long endTime = 1500000; // 25 min

  for (;;) {
    elapsedTime = long(millis() - startTime);

    outputValue = analogOutMax - (int)(((float)elapsedTime / (float)endTime) * (float)analogOutMax);
    if (outputValue > analogOutMax) {
      outputValue = analogOutMax;
    }
    if (outputValue < 0) {
      outputValue = 0;
      break;
    }
    analogWrite(timerOutPin, outputValue);
  }
  analogWrite(timerOutPin, 0);
}

void setup() {
  pinMode(13, OUTPUT);
  pinMode(timerOutPin, OUTPUT);

  analogWrite(timerOutPin, analogOutMax*0.7);
  delay(100);
  analogWrite(timerOutPin, analogOutMax*0.8);
  delay(100);
  analogWrite(timerOutPin, analogOutMax*0.9);
  delay(100);
  analogWrite(timerOutPin, analogOutMax);

  // LED
  digitalWrite(13, HIGH);
  delay(600);
  digitalWrite(13, LOW);

  timer();

  analogWrite(timerOutPin, 0);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_mode();
}

void loop() {
}