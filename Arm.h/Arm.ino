#include "Arm.h"

void setup() {
  Serial.begin(9600);

}

void loop() {
  int x,y,z;

  // Reading data from the serial port
  while (!Serial.available()); // waiting for something to be written to serial
  // reading the three coordinates as integers
  x = Serial.parseInt(); 
  y = Serial.parseInt();
  z = Serial.parseInt();

}
