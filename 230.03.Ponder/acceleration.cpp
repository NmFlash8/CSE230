/***********************************************************************
 * Source File:
 *    ACCELERATION
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about changing speed
 ************************************************************************/

#include "acceleration.h"
#include "angle.h"
#include <cmath>


/*********************************************
 * ACCELERATION : ADD
 *  a += a
 *********************************************/
void Acceleration::add(const Acceleration& acceleration)
{
   ddx += acceleration.ddx;
   ddy += acceleration.ddy;
}


/*********************************************
 * ACCELERATION : SET
 *  set from angle and direction
 *********************************************/
void Acceleration::set(const Angle& angle, double magnitude)
{
   double angleRad = angle.getRadians();  // Get radians from angle class
   ddy = magnitude * cos(angleRad);       
   ddx = magnitude * sin(angleRad); 
}
