#ifndef _TASKS_H_
#define _TASKS_H_

#include "movement.h"
#include "ultraSonic.h"
#include "housekeeping.h"
#include <P1AM.h>


void alpha() {
  
  stopCar(0);
  centerServo();
  housekeeping();
  delay(1500);  

  drive(25);
  housekeeping();
  delay(2000);

  stopCar(25);
  housekeeping();
  delay(500);
  
  turn(100);
  housekeeping();
  delay(2500);
  
  drive(25);
  housekeeping();
  delay(2000);

  stopCar(25);
  housekeeping();
  delay(500);
  
  turn(-100);
  housekeeping();
  delay(2500);
  
  drive(25);
  housekeeping();
  delay(2000);

  stopCar(25);
  housekeeping();
  delay(500);
  
  turn(0);
  housekeeping();
  delay(2500);
  
  drive(-25);
  housekeeping();
  delay(2500);

  stopCar(-25);
  housekeeping();
  delay(1500);

  modbusTCPServer.coilWrite(0,0);
  housekeeping();
  
  signalFinish('A');
  housekeeping();
  delay(1500);
  
  return;
}


void bravo() {
  stopCar(0);
  centerServo();
  delay(1500);
  housekeeping();
  
  drive(20);
  delay(500);

  turn(-100);
  delay(3750);
  housekeeping();

  turn(100);
  delay(21000);

  turn(-100);
  delay(3750);
  housekeeping();

  turn(0);

  delay(1500);
  housekeeping();
  
  stopCar(20);
  delay(2000);
  housekeeping();

  modbusTCPServer.coilWrite(1,0);
  housekeeping();

  signalFinish('B');
  delay(1500);
  housekeeping();

  return;
}


void charlie() {

  housekeeping();
  
  stopCar(0);
  centerServo();
  delay(5000);

  unsigned long timenow = 0;

  drive(25);
  
  while (millis() <= timenow + 9999999) {
    housekeeping();
    pingSensorP();
    checkDistance();
    delay(250);
  }

  modbusTCPServer.coilWrite(2,0);
  housekeeping();
    
  stopCar(25);
  delay(2000);
  signalFinish('C');
  delay(10000);

  return;
}

#endif
