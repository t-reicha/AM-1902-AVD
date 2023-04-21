#ifndef _TASKS_H_
#define _TASKS_H_

#include "movement.h"
#include "ultraSonic.h"
#include <P1AM.h>

/*
void alpha() {
  
  stopCar();
  centerServo();
  delay(1500);  

  drive(2000, 8.5);
  delay(500);
  
  turn(2500, 8.5);
  delay(500);
  
  drive(2000, 8.5);
  delay(500);
  
  turn(2500, 6.5);
  delay(500);
  
  drive(2000, 8.5);
  delay(500);
  
  turn(2500, 7.5);
  delay(500);
  
  drive(2000, 6.5);
  delay(1500);
  
  signalFinish('A');
  delay(1500);
  
  
  return;
}


void bravo() {
  stopCar();
  centerServo();
  delay(1500);
  
  drive(8.25);
  delay(500);

  turn(6.5);
  delay(3750);

  turn(8.5);
  delay(21000);

  turn(6.5);
  delay(3750);

  turn(7.5);

  delay(1500);
  
  stopCar();
  delay(2000);

  signalFinish('B');
  delay(1500);

  return;
}
*/

void charlie() {
  
  speed0();
  centerServo();

  unsigned long timenow = 0;

  driveForward(25);
  
  while (millis() <= timenow + 100000) {
    //pingSensor('1');
    //delay(250);
    pingSensor('2');
    delay(250);
  }

    
  stopCarForward(25);
  delay(2000);
  signalFinish('C');
  delay(10000);
}

#endif
