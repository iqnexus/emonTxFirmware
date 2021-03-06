/*
  
  emonTxV3 Current Only Example - Read from the four CT channels and serial print power values
   -----------------------------------------
  Part of the openenergymonitor.org project
  Licence: GNU GPL V3
*/

#include <RFu_JeeLib.h>                  //not needed for this sketch 
#include "EmonLib.h"                     // Include Emon Library
EnergyMonitor ct1, ct2, ct3, ct4;        // Create two instances

void setup()
{  
  rf12_initialize(10,RF12_868MHZ,210);     // initialize RFM12B
   //rf12_sleep(0);                        //rf12 sleep seems to cause issue on the RFu, not sure why? Need to look into this

  
  Serial.begin(9600);
  Serial.println("emonTx V3 Current Only Example");
  
  ct1.current(1, 90.909);             // CT channel 1, calibration.  calibration (2000 turns / 22 Ohm burden resistor = 90.909)
  ct2.current(2, 90.909);             // CT channel 2, calibration.
  ct3.current(3, 90.909);             // CT channel 2, calibration.
  
  //CT 3 is high accuracy @ low power -  4.5kW Max 
  ct4.current(4, 16.66);             // CT channel 2, calibration.    calibration (2000 turns / 120 Ohm burden resistor = 16.66)
  pinMode(6, OUTPUT);
}

void loop()
{
  double Irms1 = ct1.calcIrms(1480);   // Calculate RMS current 1 - 1480 is  number of samples
  double Irms2 = ct2.calcIrms(1480);   // Calculate RMS current 2
  double Irms3 = ct3.calcIrms(1480);   // Calculate RMS current 2
  double Irms4 = ct4.calcIrms(1480);   // Calculate RMS current 2
  
  /*Serial.print(Irms1);                 // Print Current 1   
  Serial.print(' '); 
  Serial.print(Irms2);                 // Print Current 2
  Serial.print(' '); 
  Serial.print(Irms3);                 // Print Current 2
  Serial.print(' '); 
  Serial.print(Irms4);                 // Print Current 2
  */
  
  // By multiplying by the nominal voltage, we can indicate the approximate apparent power:
  //Serial.print(' '); 
  Serial.print(Irms1*240);           // Print apparent power 1   
  Serial.print(' '); 
  Serial.print(Irms2*240);         // Print apparent power 2
  Serial.print(' '); 
  Serial.print(Irms3*240);         // Print apparent power 2
  Serial.print(' '); 
  Serial.println(Irms4*240);         // Print apparent power 2
  
 digitalWrite(6, LOW);
 delay(500);
 digitalWrite(6, HIGH);
 
}
