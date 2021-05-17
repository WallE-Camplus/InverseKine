#ifndef ARM_H
#define ARM_H

#include <Arduino.h>
#include <Servo.h>
#include <math.h>
#include "InvKin.h"

/**
 * @file
 * @version 1.0
 * @author Marco Colangelo
 * 
 * Class to control an arm composed by hip, shoulder and wist
 * It implements the InverseKinematics class to return the three edges
 */
class Arm {
  public:
    Arm(byte pinHip, byte pinShoulder, byte pinElbow); 
    void move(int x, int  y, int z);
    void writeArm(double q1, double q2, double q3);
    void begin();
  private:
    InvKin *ik; 
    Servo hip;
    Servo shoulder;
    Servo elbow;
    byte pinHip;
    byte pinShoulder;
    byte pinElbow;
    int radToMicros(double rad);
};

#endif
