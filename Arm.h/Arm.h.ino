#ifndef ARM_H
#define ARM_H

#include <Arduino.h>
#include <Servo.h>
#include <math.h>
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
      Arm (byte pin1, byte pin2, byte pin3); 
      void move(int x, int  y, int z);
      void begin();
    private:
      InverseKinematic ik; 
      Servo hip;
      Servo shoulder;
      Servo elbow;
      byte pinHip;
      byte pinShoulder;
      byte pinElbow;
      int radToMicros(double rad);
  };

#endif
