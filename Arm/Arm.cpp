#include "Arm.h"

Arm::Arm(byte pinHip, byte pinShoulder, byte pinElbow){
  this->pinHip = pinHip;
  this->pinShoulder = pinShoulder;
  this->pinElbow = pinElbow;
}

void Arm::begin(){
  hip.attach(pinHip);
  shoulder.attach(pinShoulder);
  elbow.attach(pinElbow);
}

void Arm::radToMicros(double rad){
  return round(rad * (MG996_MAX - MG996_MIN) / PI + MG996_MIN);
}

void Arm::move(int x, int y, int z){
  InvKin ik (x,y,z);
  hip.writeMicroseconds(radToMicros(ik.getQ1()));
  shoulder.writeMicroseconds(radToMicros(ik.getQ2()));
  elbow.writeMicroseconds(radToMicros(ik.getQ3()));
}

void Arm::writeArm(double m1, double m2,double m3){
  // writing the angles (given in microseconds) to the servos
  hip.writeMicroseconds(uhip);
  shoulder.writeMicroseconds(ushoulder);
  elbow.writeMicroseconds(uelbow);
}
