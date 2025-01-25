/***********************************************************************
 * Source File:
 *    ACCELERATION
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Definitions for the methods of the Acceleration class
 ************************************************************************/

#include "acceleration.h"
#include "angle.h"

#include <cmath>  

 /*********************************************
  * Set the acceleration based on angle and magnitude
  *********************************************/
void Acceleration::set(const Angle& a, double magnitude)
{
   // Handle edge case where magnitude is zero
   if (magnitude == 0.0)
   {
      ddx = 0.0;
      ddy = 0.0;
      return;  
   }

   double radians = a.getDegrees() * (M_PI / 180.0); // Convert angle to radians

   // Apply trigonometry to calculate the acceleration components
   ddx = magnitude * cos(radians); // Horizontal component (X-axis)
   ddy = magnitude * sin(radians); // Vertical component (Y-axis)

   
}


void Acceleration::add(const Acceleration& rhs)
{
   this->ddx += rhs.ddx; // Accumulate horizontal acceleration
   this->ddy += rhs.ddy; // Accumulate vertical acceleration
}
