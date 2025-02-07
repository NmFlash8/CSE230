/***********************************************************************
 * Source File:
 *    VELOCITY
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about speed
 ************************************************************************/ 

#include "velocity.h"
#include "acceleration.h"
#include "angle.h"

#include <math.h>  // for sqrt()


/*********************************************
 * VELOCITY : GET SPEED
 *  find the magnitude of velocity
 *********************************************/
double Velocity::getSpeed() const
{
   return sqrt(dx * dx + dy * dy); // Magnitude of velocity
}

/*********************************************
 * VELOCITY : SET
 *  set from angle and direction
 *********************************************/
void Velocity::set(const Angle & angle, double magnitude)
{
   dy = magnitude * cos(angle.getRadians());
   dx = magnitude * sin(angle.getRadians());
}

/*********************************************
 * VELOCITY : ADD DX
 * Increment horizontal velocity
 *********************************************/
void Velocity::addDX(double ddx)
{
   dx += ddx;
}

/*********************************************
 * VELOCITY : ADD DY
 * Increment vertical velocity
 *********************************************/
void Velocity::addDY(double ddy)
{
   dy += ddy;
}

/*********************************************
 * VELOCITY : ADD
 *  v = v_0 + a t
 *********************************************/
void Velocity::add(const Acceleration& acceleration, double time)
{
   dx += acceleration.getDDX() * time; // Update horizontal velocity
   dy += acceleration.getDDY() * time; // Update vertical velocity
}