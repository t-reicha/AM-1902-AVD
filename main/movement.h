#ifndef _MOVEMENT_H_
#define _MOVEMENT_H_

#include <P1AM.h>
#include <stdio.h>
#include "housekeeping.h"

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


void stopCar(float speeds) {

  float neutral = 7.5;
  
  float dutyCycle = floatMap(speeds, -100, 100, 5, 10);

  if (dutyCycle > neutral) {
    while (dutyCycle > neutral) {
      P1.writePWM(dutyCycle, frequency, slot, d);
      P1.writePWM(dutyCycle, frequency, slot, p);

      dutyCycle -= 0.05;
      delay(50);
    }
  } else if (dutyCycle < neutral) {
    while (dutyCycle < neutral) {
      P1.writePWM(dutyCycle, frequency, slot, d);
      P1.writePWM(dutyCycle, frequency, slot, p);

      dutyCycle += 0.05;
      delay(50);
    }
  }
}


void turn(float amount) {
  dutyCycle = floatMap(amount, -100, 100, 6.5, 8.5);

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

void lights(int light, bool state) {
  int digitalSlot = 1;
  
  if (light == 1) {
    if (state == true) {
      P1.writeDiscrete(HIGH, digitalSlot, 1);
    } else if (state == false) {
      P1.writeDiscrete(LOW, digitalSlot, 1);
    }
  } else if (light == 2) {
    if (state == true) {
      P1.writeDiscrete(HIGH, digitalSlot, 2);
    } else if (state == false) {
      P1.writeDiscrete(LOW, digitalSlot, 2);
    }
  } else {
    Serial.println("Invalid light!");
  }
}


// rewrite using lights() and test
void signalFinish(char task) {
  int digitalSlot = 1;


  switch(task) {
    case 'A':
      lights(1, true);
      lights(2, true);
      delay(1000);
      housekeeping();
      
      lights(1, false);
      lights(2, false);
      delay(1000);
      
      lights(1, true);
      lights(2, true);
      delay(2000);
      housekeeping();
      
      lights(1, false);
      lights(2, false);
      
      break;
    case 'B':
      lights(1, true);
      lights(2, true);
      delay(2000);
      housekeeping();
      
      lights(1, false);
      lights(2, false);
      delay(1000);
      
      lights(1, true);
      lights(2, true);
      delay(1000);
      housekeeping();
      
      lights(1, false);
      lights(2, false);
      delay(1000);
      
      lights(1, true);
      lights(2, true);
      delay(1000);
      housekeeping();
      
      lights(1, false);
      lights(2, false);
      delay(1000);
      
      lights(1, true);
      lights(2, true);
      delay(1000);
      housekeeping();
      
      lights(1, false);
      lights(2, false);
      
      break;
    case 'C':
      lights(1, true);
      lights(2, true);
      delay(2000);
      housekeeping();

      lights(1, false);
      lights(2, false);
      delay(1000);

      lights(1, true);
      lights(2, true);
      delay(1000);
      housekeeping();

      lights(1, false);
      lights(2, false);
      delay(1000);

      lights(1, true);
      lights(2, true);
      delay(2000);
      housekeeping();

      lights(1, false);
      lights(2, false);
      delay(1000);

      lights(1, true);
      lights(2, true);
      delay(1000);
      housekeeping();

      lights(1, false);
      lights(2, false);
      
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


#endif
