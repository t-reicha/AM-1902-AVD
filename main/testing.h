#ifndef _TESTING_H_
#define _TESTING_H_

#include <P1AM.h>


/*
float fps;
float period;
float circumference = 1.5; // example value


void goDistance(float vel, float dist) {
  fps = veltofps(vel);
  period = fps * dist;
  testDrive(vel, period); // what does this do and where is it defined?
}

float veltofps(float vel) {
  float rpm = vel * z; // what is z? not defined
  float dist = rpm * circumference;
  fps = dist / 60;
  return fps;
}

void testDrive(float vel, float period) {
  P1.writePWM(vel, frequency, slot, d);
  P1.writePWM(vel, frequency, slot, p);

  // how do i make it run for the set time then stop?
}
*/

/*
float floatMap(float value, float fromLow, float fromHigh, float toLow, float toHigh) {
  return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}
*/

/*
// non-blocking delay test
void asyncDelay(int ms) {
  unsigned long timenow = 0;

  if(millis() >= timenow + ms) {
    timenow + ms;
  }
}
*/
#endif
