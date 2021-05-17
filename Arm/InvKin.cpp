#include "InvKin.h"

/**
 * Constructor for the InverseKinematic objeect
 */
InvKin::InvKin(double d1, double l2, double l3) {
  this->d1 = d1;
  this->l2 = l2;
  this->l3 = l3;
}

/**
 * compute() 
 */
void InvKin::compute(int x, int y, int z) {
  double s1, s2, s3;
  double c1, c2, c3;
  double dx, dy, dz; // variable to store the target

  // storing our target in double variable, to ease computation
  dx = x;
  dy = y;
  dz = z;

  // magic but maybe a little bit broken math stuff
  c1 = dx / sqrt(dx*dx + dy*dy);
  s1 = sqrt(1.0-c1*c1);
  q1 = atan2(dy,dx);

  c3 = (dx*dx+dy*dy+(dz-d1)*(dz-d1)-l2*l2-l3*l3)/(2.0*l2*l3);
  s3 = -sqrt(1.0-c3*c3);
  q3 = -atan2(s3,c3);

  s2 = ((l2+l3*c3)*(dz-d1)-l3*s3*(c1*dx+s1*dy))/((l2+l3*c3)*(l2+l3*c3)+(l3*s3)*(l3*s3));
  c2 = sqrt(1.0-s2*s2);
  q2 = atan2(s2,c2);
}

double InvKin::getQ1(){
  return q1;
}


double InvKin::getQ2(){
  return q2;
}


double InvKin::getQ3(){
  return q3;
}
