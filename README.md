# InverseKine

Repository containing everything related to the arm's inverse kinematics algorithm.

## Arduino example

The `InverseKine` folder contains a simple Arduino code to test the math.

## Improvements
We noticed that q3 has to be considered negative and not positive, this can be seen by the right hand rule as well.
For the calculations the angles can be considered positive or negative indifferently (although not equivalent), but for the motors they have to be positive, as a negative angle is not accepted as an input signal. 
