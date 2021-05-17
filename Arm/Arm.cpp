#include "Arm.h"

Arm::Arm(byte pinHip, byte pinShoulder, byte pinElbow) {
  this->pinHip = pinHip;
  this->pinShoulder = pinShoulder;
  this->pinElbow = pinElbow;
  ik = new InvKin(8.0, 12.0, 13.7);
}

void Arm::begin() {
  hip.attach(pinHip);
  shoulder.attach(pinShoulder);
  elbow.attach(pinElbow);
}

int Arm::radToMicros(double rad) {
  return round(rad * (MG996_MAX - MG996_MIN) / PI + MG996_MIN);
}

void Arm::move(int x, int y, int z) {
  ik->compute(x,y,z);
  writeArm(ik->getQ1(), ik->getQ2(), ik->getQ3());
}

void Arm::writeArm(double q1, double q2,double q3) {
  // writing the angles (given in microseconds) to the servos
  hip.writeMicroseconds(radToMicros(q1));
  shoulder.writeMicroseconds(radToMicros(q2));
  elbow.writeMicroseconds(radToMicros(q3));
}
