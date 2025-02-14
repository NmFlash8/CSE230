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
#include <cmath>  // for M_PI if needed

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

   // Set the horizontal velocity to a random value between -10m/s and -4m/s
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
 * Accept input from the Neil Armstrong.
 *
 * This version processes rotation and main engine thrust:
 *   - If the thrust indicates rotation (clockwise or counterclockwise)
 *     and fuel is available, the lander rotates and burns 1 unit of fuel.
 *     (Clockwise adds 0.1 radians; counterclockwise adds 0.3 radians.)
 *   - If the main engine is active, vertical thrust is applied and fuel is consumed.
 *   - In any case, gravity is always applied.
 ***************************************************************/
Acceleration Lander::input(const Thrust& thrust, double gravity)
{
   Acceleration acceleration; // starts with 0,0

   if (fuel > 0)
   {
      // Process rotation.
      // If the clockwise button is pressed (and not counterclockwise),
      // rotate clockwise by adding 0.1 radians.
      if (thrust.isClock() && !thrust.isCounter())
      {
         angle.add(0.1);
         fuel -= 1.0;
      }
      // If the counterclockwise button is pressed,
      // rotate counterclockwise by subtracting 0.1 radians.
      else if (thrust.isCounter())
      {
         angle.add(-0.1);
         fuel -= 1.0;
      }

      // Process main engine thrust.
      if (thrust.isMain())
      {
         // Calculate the main engine thrust vector.
         // For example, when the lander's angle is 4.71239 radians,
         // sin(4.71239) is about -1 and cos(4.71239) is about 0.
         // This produces an acceleration of roughly 2.9795404 in the x-direction.
         const double MAIN_THRUST = 2.9795404;
         acceleration.setDDX(-MAIN_THRUST * sin(angle.getRadians()));
         acceleration.setDDY(MAIN_THRUST * cos(angle.getRadians()));
         fuel -= 10.0;
      }
   }

   // Gravity is always applied.
   acceleration.addDDY(gravity);

   return acceleration;
}


/***************************************************************
 * COAST
 * What happens when we coast?
 ***************************************************************/
void Lander::coast(Acceleration& acceleration, double time)
{
   if (time > 0)
   {
      // Make a copy of the current (old) velocity.
      Velocity oldVelocity = velocity;

      // Update the position using the old velocity.
      pos.add(acceleration, oldVelocity, time);

      // Now update the lander's velocity.
      velocity.add(acceleration, time);
   }
}



/***************************************************************
 * LAND
 * Straighten the lander and put it on the ground.
 ***************************************************************/
void Lander::land()
{
   status = SAFE;
   angle.setUp();  // Reset the angle 
}


/***************************************************************
 * CRASH
 * Set the lander to a crashed state.
 ***************************************************************/
void Lander::crash()
{
   status = DEAD;
   angle.setRadians(M_PI);
}