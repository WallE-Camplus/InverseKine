#include <math.h>
#include <Arduino.h>
#include <Servo.h>

#define MG996_MIN 544 // microseconds corresponding to the minimum angle for our servo, so 0 degrees
#define MG996_MAX 2130 // microseconds corresponding to the theoretical maximux angle for our servo, so 180 degrees

// pin definitions
#define PINHIP 11
#define PINSHO 9
#define PINELB 3

// creating servo objects
Servo hip;
Servo shoulder;
Servo elbow;

// some terrible global variables
double q1, q2, q3;
double l1=1.4, l2=12, l3=13.7, d1=8;

void inverseKine(int x, int y, int z) {
  double s1, s2, s3;
  double c1, c2, c3;
  double dx, dy, dz; // variable to store the target

  // storing our target in double variable, to ease computation
  dx = x;
  dy = y;
  dz = 16-z; // have no idea why this is needed

  // magic but maybe a little bit broken math stuff
  c1 = dx / sqrt(dx*dx + dy*dy);
  s1 = dy / sqrt(dx*dx + dy*dy);
  q1 = atan2(dy,dx);

  c3 = (dx*dx+dy*dy+(dz-d1)*(dz-d1)-l2*l2-l3*l3)/(2.0*l2*l3);
  s3 = sqrt(1.0-c3*c3);
  q3 = atan2(s3,c3);

  s2 = ((l2+l3*c3)*(dz-d1)-l3*s3*(c1*dx+s1*dy))/((l2+l3*c3)*(l2+l3*c3)+(l3*s3)*(l3*s3));
  c2 = sqrt(1.0-s2*s2);
  q2 = -atan2(s2,c2);
}

void writeArm(int anghip, int angshoulder, int angelbow) {
  Serial.println("Moving to:" + String(anghip) + ", " + String(angshoulder) + ", "+ String(angelbow) + ".");

  // writing the angles (given in degrees) to the servos
  hip.write(anghip);
  shoulder.write(angshoulder);
  elbow.write(angelbow);
}

void moveArm(int x, int y, int z) {
  inverseKine(x,y,z); // computing inverse kinematics to move to the given position, donesn't move by itself
  
  Serial.println("Computed angles:" + String(q1) + ", " + String(q2) + ", "+ String(q3) + ".");
  
  writeArm(q1*RAD_TO_DEG, q2*RAD_TO_DEG, q3*RAD_TO_DEG); // convert the angles from radians to degrees and moves the arm
}

void setup() {
  Serial.begin(9600);

  // initializing the servos setting the correct minimum and maximum impulses
  hip.attach(PINHIP, MG996_MIN, MG996_MAX);
  shoulder.attach(PINSHO, MG996_MIN, MG996_MAX);
  elbow.attach(PINELB, MG996_MIN, MG996_MAX);
}

void loop() {
  int x,y,z;

  // Reading data from the serial port
  while (!Serial.available()); // waiting for something to be written to serial
  // reading the three coordinates as integers
  x = Serial.parseInt(); 
  y = Serial.parseInt();
  z = Serial.parseInt();
  while(Serial.available() > 0) Serial.read(); // unreliable way to remove trailing newlines

  // moves the arm to the given coordinates in the plane
  moveArm(x,y,z); 

  /* 
   * for test purpose this can be used instead of the previous call to interpret the data read from 
   * serial as angles, and directly write them to the motors. useful to check for correctness of the
   * arm itself.
   */
  //writeArm(x,y,z);
  
  delay(50); // waiting a little for the arm to move into position
}
