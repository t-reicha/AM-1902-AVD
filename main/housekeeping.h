#ifndef _HOUSEKEEPING_H_
#define _HOUSEKEEPING_H_

boolean MB_C[16]; //Modbus Coil Bits
boolean MB_I[16]; //Modbus Input Bits
int MB_HR[16];    //Modbus Holding Registers
int MB_IR[16];    //Modbus Input Registers
//int Slot1_Inputs;

EthernetServer server(502); //Standard Modbus Port is 502
EthernetClient client;
ModbusTCPServer modbusTCPServer;

void updateCoils() {//Read the Coil bits from the Modbus Library
  for (int i=0;i<16;i++){
    MB_C[i] = modbusTCPServer.coilRead(i);
  }
}

void updateInputs() { //Write the Input bits to the Modbus Library
  for (int i=0;i<16;i++){
    modbusTCPServer.discreteInputWrite(i,MB_I[i]);
  }
}

void updateHoldingRegisters() {//Read the Holding Register words from the Modbus Library
  for (int i=0;i<16;i++){
    MB_HR[i] = modbusTCPServer.holdingRegisterRead(i);
  }
}

void updateInputRegisters() { //Write the Input Registers to the Modbus Library
  for (int i=0;i<16;i++){
    modbusTCPServer.inputRegisterWrite(i,MB_IR[i]);
  }
}

void housekeeping() {
  EthernetClient newClient = server.accept(); //listen for incoming clients
  
  if (newClient) { //newest connection is always accepted
    client = newClient;
    Serial.print("Client Accept:"); //a new client connected
    Serial.println(client.remoteIP());
    }
  if(client.available()){ //if data is available
    modbusTCPServer.accept(client); //accept that data
    modbusTCPServer.poll(); //service any Modbus TCP requests, while client connected
    }
  if(client && !client.connected()){ //Stop any clients which are disconnected
    client.stop();
    Serial.println("Client Stopped"); //the client disconnected
    }
      
  //Read from P1-08SIM Input Module and then write into Modbus memory
  //Slot1_Inputs = P1.readDiscrete(1,0); //Read from P1-08SIM Input Simulator Module
  //for (int i=0;i<8;i++){
    //MB_I[i]=Slot1_Inputs&(1<<i);
  //}
  updateInputs(); //Write current state of the Modbus Inputs into MB_I[]

  //Read from Analog Input Modules and then write into Modbus memory
  updateInputRegisters(); //Write current state of the Modbus Inputs into MB_IR[]

  updateCoils(); //Read current state of the Modbus Coils into MB_C[]
  for (int i=0;i<8;i++){
//    P1.writeDiscrete(MB_C[i],2,i+1);//Data,Slot,Channel ... Channel is one-based.
  }
  
  updateHoldingRegisters(); //Read current state of the Modbus Registers into MB_HR[]
  MB_HR[0]++; //TestApp, increment the Modbus Register 400000 just to have data changing.
  modbusTCPServer.holdingRegisterWrite(0,MB_HR[0]);
}

#endif
