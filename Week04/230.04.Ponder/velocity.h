/***********************************************************************
 * Header File:
 *    VELOCITY
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about speed
 ************************************************************************/

#pragma once

// for unit tests
class TestPosition;
class TestVelocity;
class TestAcceleration;
class TestLander;

// for add()
class Acceleration;
class Angle;

 /*********************************************
  * Velocity
  * I feel the need, the need for speed
  *********************************************/
class Velocity
{
   // for unit tests
   friend TestPosition;
   friend TestVelocity;
   friend TestLander;

public:
   // constructors
   Velocity() : dx(0.0), dy(0.0) {} // Default to zero velocity
   Velocity(double dx, double dy) : dx(dx), dy(dy) {}

   // getters
   double getDX() const { return dx; }
   double getDY() const { return dy; }
   double getSpeed() const;

   // setters
   void setDX(double dx) { this->dx = dx; }
   void setDY(double dy) { this->dy = dy; }
   void set(const Angle& angle, double magnitude);

   // Add methods for Ticket 2
   void addDX(double ddx);
   void addDY(double ddy);
   void add(const Acceleration& acceleration, double time);

private:
   double dx;           // horizontal velocity
   double dy;           // vertical velocity
};