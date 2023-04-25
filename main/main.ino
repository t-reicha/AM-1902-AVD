#include <Ethernet.h>
#include <P1AM.h>
#include "movement.h"
#include "tasks.h"
#include "testing.h"
#include "ultraSonic.h"


void setup() {
  
  Serial.begin(115200);
  while (!P1.init()) {
    ;
  }

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  
  // alpha();

  // bravo();

  // charlie();

  // test stopCar(), and test new signalFinish()
}
