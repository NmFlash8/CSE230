/***********************************************************************
 * Source File:
 *    ANGLE
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#include "angle.h"
#include <math.h>  // for floor()
#include <cassert>
using namespace std;

/*************************************
 * ANGLE : Default constructor
 *************************************/
Angle::Angle() : radians(0.0) {}

/*************************************
 * ANGLE : Copy constructor
 *************************************/
Angle::Angle(const Angle& rhs) : radians(rhs.radians) {}

/*************************************
 * ANGLE : Constructor with degrees
 *************************************/
Angle::Angle(double degrees) : radians(convertToRadians(degrees)) {}

/*************************************
 * ANGLE : Converts radians to degrees
 *************************************/
double Angle::convertToDegrees() const
{
   return radians * (180.0 / M_PI);  // Convert radians to degrees
}

/*************************************
 * ANGLE : Converts degrees to radians
 *************************************/
double Angle::convertToRadians(double degrees) const
{
   return degrees * (M_PI / 180.0);  // Convert degrees to radians
}

/*************************************
 * ANGLE : Normalize radians
 * Prevents radians from going over or under 2 Pi
 *************************************/
double Angle::normalize(double radians) const
{
   const double TWO_PI = 2 * M_PI;

   // Normalize the angle to be within [0, 2 * M_PI]
   radians = fmod(radians, TWO_PI);

   // If radians is negative, make it positive by adding TWO_PI
   if (radians < 0)
      radians += TWO_PI;

   return radians;
}


/*************************************
 * ANGLE : Get the angle in radians
 *************************************/
double Angle::getRadians() const
{
   return radians;
}

/*************************************
 * ANGLE : Get the angle in degrees
 *************************************/
double Angle::getDegrees() const
{
   return convertToDegrees();
}

/*************************************
 * ANGLE : Set the angle using degrees
 *************************************/
void Angle::setDegrees(double degrees)
{
   radians = convertToRadians(degrees);
   radians = normalize(radians);
}

/*************************************
 * ANGLE : Set the angle using radians
 *************************************/
void Angle::setRadians(double radians)
{
   this->radians = normalize(radians);
}

/*****************************************
 * ANGLE : Set the angle to 0 radians (up)
 *****************************************/
void Angle::setUp()
{
   radians = 0.0;
}

/********************************************
 * ANGLE : Set the angle to Pi radians (down)
 ********************************************/
void Angle::setDown()
{
   radians = M_PI;
}

/***********************************************
 * ANGLE : Set the angle to Pi/2 radians (right)
 ***********************************************/
void Angle::setRight()
{
   radians = M_PI / 2;
}

/***********************************************
 * ANGLE : Set the angle to 3Pi/2 radians (left)
 ***********************************************/
void Angle::setLeft()
{
   radians = 3 * M_PI / 2;
}

/**********************************************
 * ANGLE : Reverse the direction by Pi radians
 **********************************************/
void Angle::reverse()
{
   radians = normalize(radians + M_PI);
}

/*************************************
 * ANGLE : Add a delta to the current radians
 *************************************/
Angle& Angle::add(double delta)
{
   radians = normalize(radians + delta);
   return *this;
}