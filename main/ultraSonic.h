#ifndef _ULTRASONIC_H_
#define _ULTRASONIC_H_

#include <P1AM.h>
#include "buffer.h"
#include "housekeeping.h"

void pingSensor(int sensor) {
  switch (sensor) {
    case '1': 
      #define trigPin A1
      #define echoPin A2
      Serial.println("sensor 1");
      break;
    case '2': 
      #define trigPin A5
      #define echoPin A6
      Serial.println("sensor 2");
      break;
    case '3': 
      break;
    default: 
      Serial.println("Invalid Sensor!");
      break;
  }

  long duration;
  long int distance;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration / 2 / 29;

  addValue(roundToFive(distance));

  int value = getMode();

  Serial.print(value);
  Serial.println(" cm");
  
  if (value < 100 && value != 0) {
    
    stopCar(25);
    while (value < 100) {
      stopCar(0);
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      duration = pulseIn(echoPin, HIGH);
      distance = duration / 2 / 29;

      addValue(roundToFive(distance));

      value = getMode();

      Serial.print(value);
      Serial.println(" cm");
    }
    drive(25);
  } else {
    return;
  }

  return;
}

#endif
