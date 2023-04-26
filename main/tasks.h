#ifndef _TASKS_H_
#define _TASKS_H_

#include "movement.h"
#include "ultraSonic.h"
#include <P1AM.h>


void alpha() {
  
  speed0();
  centerServo();
  delay(1500);  

  drive(25);
  delay(2000);

  stopCar(25);
  delay(500);
  
  turn(100);
  delay(2500);
  
  drive(25);
  delay(2000);

  stopCar(25);
  delay(500);
  
  turn(-100);
  delay(2500);
  
  drive(25);
  delay(2000);

  stopCar(25);
  delay(500);
  
  turn(0);
  delay(2500);
  
  drive(-25);
  delay(2500);

  stopCar(-25);
  delay(1500);
  
  signalFinish('A');
  delay(1500);
  
  return;
}


void bravo() {
  speed0();
  centerServo();
  delay(1500);
  
  drive(20);
  delay(500);

  turn(-100);
  delay(3750);

  turn(100);
  delay(21000);

  turn(-100);
  delay(3750);

  turn(0);

  delay(1500);
  
  stopCar(20);
  delay(2000);

  signalFinish('B');
  delay(1500);

  return;
}


void charlie() {
  
  speed0();
  centerServo();

  unsigned long timenow = 0;

  drive(25);
  
  while (millis() <= timenow + 100000) {
    //pingSensor('1');
    //delay(250);
    pingSensor('2');
    delay(250);
  }

    
  stopCar(25);
  delay(2000);
  signalFinish('C');
  delay(10000);
}

#endif
