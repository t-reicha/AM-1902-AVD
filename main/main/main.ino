#include <Ethernet.h>
#include <P1AM.h>
#include "movement.h"
#include "tasks.h"
#include "testing.h"
#include "ultraSonic.h"


void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  while (!P1.init()) {
    ;
  }

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // alpha();

  // bravo();

  // rgb();

  delay(2500);

  charlie();

  //pingSensor('1');
  //delay(1000);
  
  //exit(1);
}
