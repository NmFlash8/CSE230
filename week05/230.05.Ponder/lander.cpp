/***********************************************************************
 * Source File:
 *    LANDER
 * Author:
 *    Br. Helfrich
 * Summary:
 *    All the information about the lunar lander
 ************************************************************************/

#include "lander.h"
#include "acceleration.h"


 /***************************************************************
  * RESET
  * Reset the lander and its position to start the game over
  ***************************************************************/
void Lander::reset(const Position& posUpperRight)
{
   // Set the angle of the lander to straight up
   angle.setUp();

   // Set the status of the lander to PLAYING
   status = PLAYING;

   // Fill the fuel with 5000.0 units
   fuel = 5000.0;

   // Set the horizontal velocity to a random value between -4m/s and -10m/s
   velocity.setDX(random(-10.0, -4.0));

   // Set the vertical velocity to a random value between -2m/s and 2m/s
   velocity.setDY(random(-2.0, 2.0));

   // Set the horizontal position to 1 pixel from the right of the screen
   pos.setX(posUpperRight.getX() - 1);

   // Set the vertical position between 75% and 95% of the height of the screen
   pos.setY(posUpperRight.getY() * random(0.75, 0.95));
}

/***************************************************************
 * DRAW
 * Draw the lander on the screen
 ***************************************************************/
void Lander::draw(const Thrust& thrust, ogstream& gout) const
{
   // Draw the lander at its current position and angle
   gout.drawLander(pos, angle.getDegrees());

   // Turn on the flames as necessary
   gout.drawLanderFlames(pos, angle.getDegrees(), thrust.isMain(), thrust.isClock(), thrust.isCounter());
}

/***************************************************************
 * INPUT
 * Accept input from the Neil Armstrong
 ***************************************************************/
Acceleration Lander::input(const Thrust& thrust, double gravity)
{
   Acceleration acceleration;

   // If there is no fuel, do not apply any thrust.
   if (fuel > 0) {
      // Handle horizontal acceleration based on thrust direction
      if (thrust.isClock()) {
         acceleration.setDDX(1.0); 
      }
      else if (thrust.isCounter()) {
         acceleration.setDDX(-1.0); 
      }

      // Handle vertical acceleration based on main thrust
      if (thrust.isMain()) {
         acceleration.setDDY(-1.0); // Apply upward thrust (negative Y for upward movement)
      }
   }

   // Apply gravity as a downward force
   acceleration.addDDY(gravity); 

   return acceleration;
}



/******************************************************************
 * COAST
 * What happens when we coast?
 *******************************************************************/
void Lander::coast(Acceleration& acceleration, double time)
{
   if (time > 0)
   {
      // Update velocity with acceleration
      velocity.addDX(acceleration.getDDX() * time);
      velocity.addDY(acceleration.getDDY() * time);

      // Update position with velocity
      pos.addX(velocity.getDX() * time);
      pos.addY(velocity.getDY() * time);
   }
}