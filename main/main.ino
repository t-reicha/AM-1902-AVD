#include <Ethernet.h>
#include <P1AM.h>
#include <SPI.h>
#include <ArduinoRS485.h>
#include <ArduinoModbus.h>
#include "movement.h"
#include "tasks.h"
#include "testing.h"
#include "ultraSonic.h"
#include "housekeeping.h"

byte mac[] = {
  0x60, 0x52, 0xD0, 0x07, 0x42, 0xBC
};

IPAddress ip(192, 168, 1, 11);


void setup() {
  
  Serial.begin(115200);
  while (!P1.init()) {
    ;
  }

  Ethernet.begin(mac, ip);
  server.begin();

  if (!modbusTCPServer.begin()) {
    Serial.println("Failed to start Modbus TCP Server!");
    while (1);
  }

  modbusTCPServer.configureCoils(0x00, 16);
  modbusTCPServer.configureDiscreteInputs(0x00, 16);
  modbusTCPServer.configureHoldingRegisters(0x00, 16);
  modbusTCPServer.configureInputRegisters(0x00, 16);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.println("Done with setup!");
}

void loop() {

  if (MB_C[0]) {
    alpha();
  }

  if (MB_C[1]) {
    bravo();
  }

  // charlie();

  // test stopCar(), and test new signalFinish()
  // test new alpha()
}
