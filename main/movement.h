#ifndef _MOVEMENT_H_
#define _MOVEMENT_H_

#include <P1AM.h>
#include <stdio.h>

float dutyCycle = 7.5; // set duty cycle to 7.5
int slot = 2; // set PLC slot to 2
int frequency = 50; //  set frequency to 50Hz
int d = 1;
int p = 2;


float floatMap(float value, float fromLow, float fromHigh, float toLow, float toHigh) {
  return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}

// center the wheels on the car
void centerServo() {

  dutyCycle = 7.5;
  P1.writePWM(dutyCycle, frequency, slot, 3); // write duty cycle and frequency to slot 2, channel 3 on the PLC - servo motor
}



/*
movement key:
5 = FULL REVERSE
10 = FULL THROTTLE
7.5 = NEUTRAL
*/

// make the car move forward or backward at a set speed for a set amount of time
void driveOld(float speeds) {
  dutyCycle = speeds;

  // if the duty cycle is too high, throw an error, otherwise proceed as normal
  if (dutyCycle < 5) {
    Serial.println("Duty Cycle is too low! (motors)"); // throw an error that the duty cycle on the motors is too low
    return;
  } else if (dutyCycle > 10) {
    Serial.println("Duty Cycle is too high! (motors)"); // throw an error that the duty cycle on the motors is too high
    return;
  } else {
    P1.writePWM(dutyCycle, frequency, slot, 1);
    P1.writePWM(dutyCycle, frequency, slot, 2);

    // delay(duration);

  
    // dutyCycle = 7.5;
    // P1.writePWM(dutyCycle, frequency, slot, 1);
    // P1.writePWM(dutyCycle, frequency, slot, 2);
  }
}

// use millis() to implement non-blocking delay later
void driveForward(float speeds) {
  float dutyCycle = floatMap(speeds, 0, 100, 7.5, 10);
  float finalCycle = 7.5;

  if (dutyCycle < 7.5) {
    Serial.println("Duty Cycle is too low! (motors)"); // throw an error that the duty cycle on the motors is too low
    return;
  } else if (dutyCycle > 10) {
    Serial.println("Duty Cycle is too high! (motors)"); // throw an error that the duty cycle on the motors is too high
    return;
  } else {
    
    while (finalCycle < dutyCycle) {
      P1.writePWM(finalCycle, frequency, slot, d);
      P1.writePWM(finalCycle, frequency, slot, p);

      finalCycle += 0.05;
      delay(50);
     // Serial.println(finalCycle);
    }
  }

  if (finalCycle > 7.5) {
    bool moving = true;
  } else {
    bool moving = false;
  }
}


void driveBackward(float speeds) {
  float dutyCycle = floatMap(speeds, 0, 100, 7.5, 5);
  float finalCycle = 7.5;

  if (dutyCycle > 7.5) {
    Serial.println("Duty Cycle is too high! (motors)"); // throw an error that the duty cycle on the motors is too low
    return;
  } else if (dutyCycle < 5) {
    Serial.println("Duty Cycle is too low! (motors)"); // throw an error that the duty cycle on the motors is too high
    return;
  } else {
    while (finalCycle > dutyCycle) {
      P1.writePWM(finalCycle, frequency, slot, d);
      P1.writePWM(finalCycle, frequency, slot, p);

      finalCycle -= 0.05;
      delay(50);
      Serial.println(finalCycle);
    }
  }

   if (finalCycle < 7.5) {
    bool moving = true;
  } else {
    bool moving = false;
  }
}


// set speed to 0 to stop the car
void stopCarForward(float speeds) {

  float neutral = 7.5;
  
  float dutyCycle = floatMap(speeds, 0, 100, 7.5, 10);

  while (dutyCycle > neutral) {
    P1.writePWM(dutyCycle, frequency, slot, d); // write duty cycle and frequency to slot 2, channel 1 on the PLC - driver side motor
    P1.writePWM(dutyCycle, frequency, slot, p); // write duty cycle and frequency to slot 2, channel 2 on the PLC - passenger side motor

    dutyCycle -= 0.05;
    delay(50);
   // Serial.println(dutyCycle);
  }
}


void stopCarBackward(float speeds) {

  float neutral = 7.5;
  
  float dutyCycle = floatMap(speeds, 0, 100, 7.5, 5);

  while (dutyCycle < neutral) {
    P1.writePWM(dutyCycle, frequency, slot, d); // write duty cycle and frequency to slot 2, channel 1 on the PLC - driver side motor
    P1.writePWM(dutyCycle, frequency, slot, p); // write duty cycle and frequency to slot 2, channel 2 on the PLC - passenger side motor

    dutyCycle += 0.05;
    delay(50);
    Serial.println(dutyCycle);
  }
}



/*
 TURNING KEY
 MAX LEFT = 8.5
 MAX RIGHT = 6.5
*/

// make the car turn a set amount, and wait a set amount of time for the action to complete
void turn(float amount) {
  dutyCycle = amount;

  // if the duty cycle is too high or too low, throw an error, otherwise continue as normal
  if (dutyCycle < 6.5) {
    Serial.println("Duty Cycle is too low! (servo)"); // throw an error that the duty cycle is too low
    return;
  } else if (dutyCycle > 8.5) {
    Serial.println("Duty Cycle is too high! (servo)"); // throw an error that the duty cycle is too high
    return;
  } else {
    
    P1.writePWM(dutyCycle, frequency, slot, 3);

    // delay(waitPeriod);
  }
}


// signal that a set task has been completed
void signalFinish(char task) {
  int digitalSlot = 1;

  // switch statement to determine the inputted task, and signal accordingly
  switch(task) {
    case 'A': // if the task is A, flash morse code 'A', if the task is B, signal morse code 'B', etc.
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
      Serial.println("Invalid task code!\n"); // throw an error if an invalid task code is passed
  }
}

void rgb() {

  int digitalSlot = 1;

  P1.writeDiscrete(HIGH, digitalSlot, 3);
  //delay(1000);
  P1.writeDiscrete(HIGH, digitalSlot, 4);
  //delay(1000);
  P1.writeDiscrete(HIGH, digitalSlot, 5);
  //delay(10000);
  //P1.writeDiscrete(LOW, digitalSlot, 3);
  //P1.writeDiscrete(LOW, digitalSlot, 4);
  //P1.writeDiscrete(LOW, digitalSlot, 5);
  
  return;
}

void speed0() {
  float dutyCycle = 7.5;
  
  P1.writePWM(dutyCycle, frequency, slot, d);
  P1.writePWM(dutyCycle, frequency, slot, p);
}

#endif
