#ifndef INVKIN_H
#define INVKIN_H

#include <math.h>
#include "config.h"

/**
 * @file
 * @version 1.0
 * @author Marco Colangelo
 * 
 * Class created to obtein the three edges (calculated by x,y,z given via input)
 * All math stuff
  */

class InvKin {
    public:
     InvKin(double d1,double l2,double l3);
     double getQ1();
     double getQ2();
     double getQ3();
     void compute(int x, int y , int z)
    private:
      double q1,q2,q3;
      double d1,l2,l3;
  };



#endif
