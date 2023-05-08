#ifndef _ULTRASONIC_H_
#define _ULTRASONIC_H_

#define trigPinD A1
#define echoPinD A2

#define trigPinP A5
#define echoPinP A6

#include <P1AM.h>
#include "buffer.h"
#include "housekeeping.h"

int pingSensorD() {

  long duration;
  long int distance;

  housekeeping();
  
  digitalWrite(trigPinD, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinD, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinD, LOW);

  housekeeping();

  duration = pulseIn(echoPinD, HIGH);
  distance = duration / 2 / 29;

  addValue(roundToFive(distance));

  housekeeping();

  int value = getMode();

  Serial.print(value);
  Serial.println(" cm");

  housekeeping();

  return(value);
}

int pingSensorP() {

  long duration;
  long int distance;

  housekeeping();
  
  digitalWrite(trigPinP, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinP, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinP, LOW);

  housekeeping();

  duration = pulseIn(echoPinP, HIGH);
  distance = duration / 2 / 29;

  addValue(roundToFive(distance));

  housekeeping();

  int value = getMode();

  Serial.print(value);
  Serial.println(" cm");

  housekeeping();

  return(value);
}

void checkDistance() {
  long duration;
  long int distance;
  int value;

  housekeeping();
  
  if (pingSensorD() < 100 && pingSensorD() != 0 || pingSensorP() < 100 && pingSensorP() != 0) {
    
    stopCar(25);
    while (pingSensorD() < 100 || pingSensorP() < 100) {
      housekeeping();
      stopCar(0);
      digitalWrite(trigPinD, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPinD, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPinD, LOW);

      duration = pulseIn(echoPinD, HIGH);
      distance = duration / 2 / 29;

      addValue(roundToFive(distance));

      value = getMode();

      Serial.print(value);
      Serial.println(" cm");
      delay(250);

      digitalWrite(trigPinP, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPinP, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPinP, LOW);

      duration = pulseIn(echoPinP, HIGH);
      distance = duration / 2 / 29;

      addValue(roundToFive(distance));

      value = getMode();

      Serial.print(value);
      Serial.println(" cm");
    }
    drive(25);
  } else {
    housekeeping();
    return;
  }
}




#endif
