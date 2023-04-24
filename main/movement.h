#ifndef _MOVEMENT_H_
#define _MOVEMENT_H_

#include <P1AM.h>
#include <stdio.h>

float dutyCycle = 7.5;
int slot = 2;
int frequency = 50;
int d = 1;
int p = 2;


float floatMap(float value, float fromLow, float fromHigh, float toLow, float toHigh) {
  return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}


void centerServo() {

  dutyCycle = 7.5;
  P1.writePWM(dutyCycle, frequency, slot, 3);
}



void driveOld(float speeds) {
  dutyCycle = speeds;

  if (dutyCycle < 5) {
    Serial.println("Duty Cycle is too low! (motors)");
    return;
  } else if (dutyCycle > 10) {
    Serial.println("Duty Cycle is too high! (motors)");
    return;
  } else {
    P1.writePWM(dutyCycle, frequency, slot, 1);
    P1.writePWM(dutyCycle, frequency, slot, 2);
  }
}


void drive(float speeds) {
  float dutyCycle = floatMap(speeds, -100, 100, 5, 10);
  float finalCycle = 7.5;

  if (dutyCycle < 5) {
    Serial.println("Duty Cycle is too low! (motors)");
    return;
  } else if (dutyCycle > 10) {
    Serial.println("Duty Cycle is too high! (motors)");
    return;
  } else {

    if (dutyCycle > 7.5 && dutyCycle <= 10) {
      while (finalCycle < dutyCycle) {
        P1.writePWM(finalCycle, frequency, slot, d);
        P1.writePWM(finalCycle, frequency, slot, p);

        finalCycle += 0.05;
        delay(50);
      }
    } else if (dutyCycle < 7.5 && dutyCycle >= 5) {
       while (finalCycle > dutyCycle) {
        P1.writePWM(finalCycle, frequency, slot, d);
        P1.writePWM(finalCycle, frequency, slot, p);

        finalCycle -= 0.05;
        delay(50);
        Serial.println(finalCycle);
      }
    }
  }
}


void stopCarForward(float speeds) {

  float neutral = 7.5;
  
  float dutyCycle = floatMap(speeds, 0, 100, 7.5, 10);

  while (dutyCycle > neutral) {
    P1.writePWM(dutyCycle, frequency, slot, d);
    P1.writePWM(dutyCycle, frequency, slot, p);

    dutyCycle -= 0.05;
    delay(50);
  }
}


void stopCarBackward(float speeds) {

  float neutral = 7.5;
  
  float dutyCycle = floatMap(speeds, 0, 100, 7.5, 5);

  while (dutyCycle < neutral) {
    P1.writePWM(dutyCycle, frequency, slot, d);
    P1.writePWM(dutyCycle, frequency, slot, p);

    dutyCycle += 0.05;
    delay(50);
    Serial.println(dutyCycle);
  }
}


void turn(float amount) {
  dutyCycle = amount;

  if (dutyCycle < 6.5) {
    Serial.println("Duty Cycle is too low! (servo)");
    return;
  } else if (dutyCycle > 8.5) {
    Serial.println("Duty Cycle is too high! (servo)");
    return;
  } else {
    
    P1.writePWM(dutyCycle, frequency, slot, 3);
  }
}



void signalFinish(char task) {
  int digitalSlot = 1;


  switch(task) {
    case 'A':
      P1.writeDiscrete(HIGH, digitalSlot, 1);
      P1.writeDiscrete(HIGH, digitalSlot, 2);
      delay(1000);
      
      P1.writeDiscrete(LOW, digitalSlot, 1);
      P1.writeDiscrete(LOW, digitalSlot, 2);
      delay(1000);
      
      P1.writeDiscrete(HIGH, digitalSlot, 1);
      P1.writeDiscrete(HIGH, digitalSlot, 2);
      delay(2000);
      
      P1.writeDiscrete(LOW, digitalSlot, 1);
      P1.writeDiscrete(LOW, digitalSlot, 2);
      
      break;
    case 'B':
      P1.writeDiscrete(HIGH, digitalSlot, 1);
      P1.writeDiscrete(HIGH, digitalSlot, 2);
      delay(2000);
      
      P1.writeDiscrete(LOW, digitalSlot, 1);
      P1.writeDiscrete(LOW, digitalSlot, 2);
      delay(1000);
      
      P1.writeDiscrete(HIGH, digitalSlot, 1);
      P1.writeDiscrete(HIGH, digitalSlot, 2);
      delay(1000);
      
      P1.writeDiscrete(LOW, digitalSlot, 1);
      P1.writeDiscrete(LOW, digitalSlot, 2);
      delay(1000);
      
      P1.writeDiscrete(HIGH, digitalSlot, 1);
      P1.writeDiscrete(HIGH, digitalSlot, 2);
      delay(1000);
      
      P1.writeDiscrete(LOW, digitalSlot, 1);
      P1.writeDiscrete(LOW, digitalSlot, 2);
      delay(1000);
      
      P1.writeDiscrete(HIGH, digitalSlot, 1);
      P1.writeDiscrete(HIGH, digitalSlot, 2);
      delay(1000);
      
      P1.writeDiscrete(LOW, digitalSlot, 1);
      P1.writeDiscrete(LOW, digitalSlot, 2);
      
      break;
    case 'C':
      P1.writeDiscrete(HIGH, digitalSlot, 1);
      P1.writeDiscrete(HIGH, digitalSlot, 2);
      delay(2000);

      P1.writeDiscrete(LOW, digitalSlot, 1);
      P1.writeDiscrete(LOW, digitalSlot, 2);
      delay(1000);

      P1.writeDiscrete(HIGH, digitalSlot, 1);
      P1.writeDiscrete(HIGH, digitalSlot, 2);
      delay(1000);

      P1.writeDiscrete(LOW, digitalSlot, 1);
      P1.writeDiscrete(LOW, digitalSlot, 2);
      delay(1000);

      P1.writeDiscrete(HIGH, digitalSlot, 1);
      P1.writeDiscrete(HIGH, digitalSlot, 2);
      delay(2000);

      P1.writeDiscrete(LOW, digitalSlot, 1);
      P1.writeDiscrete(LOW, digitalSlot, 2);
      delay(1000);

      P1.writeDiscrete(HIGH, digitalSlot, 1);
      P1.writeDiscrete(HIGH, digitalSlot, 2);
      delay(1000);

      P1.writeDiscrete(LOW, digitalSlot, 1);
      P1.writeDiscrete(LOW, digitalSlot, 2);
      
      break;
    case 'D':
      break;
    case 'E':
      break;
    case 'F':
      break;
    case 'G':
      break;
    case 'H':
      break;
    case 'I':
      break;
    default:
      Serial.println("Invalid task code!\n");
  }
}


void speed0() {
  float dutyCycle = 7.5;
  
  P1.writePWM(dutyCycle, frequency, slot, d);
  P1.writePWM(dutyCycle, frequency, slot, p);
}

#endif
