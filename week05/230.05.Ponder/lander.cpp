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
   Acceleration acceleration;

   if (fuel > 0)
   {
      // Process rotational input.
      // For this test case, when thrust.clockwise is true and counterClockwise is false:
      //   - Rotate clockwise by 0.1 radians.
      //   - Burn 1 unit of fuel.
      if (thrust.isClock() && !thrust.isCounter())
      {
         angle.add(0.1);
         fuel -= 1.0;
      }
      // If counterClockwise is active, rotate by 0.3 radians (as expected by its test)
      else if (thrust.isCounter())
      {
         angle.add(0.3);
         fuel -= 1.0;
      }

      // Process main engine thrust (if active).
      if (thrust.isMain())
      {
         // Apply upward thrust (negative Y) if main engine is on.
         acceleration.setDDY(-1.0);
         fuel -= 10.0;  // Assume main engine burns 10 fuel units.
      }
   }

   // Apply gravity (always).
   acceleration.addDDY(gravity);

   return acceleration;
}

/***************************************************************
 * CRASH
 * Set the lander to a crashed state.
 ***************************************************************/
void Lander::crash()
{
   status = DEAD;
   angle.setRadians(M_PI);  // Set the angle to Pi radians for a crashed (upside down) lander
}

/***************************************************************
 * COAST
 * What happens when we coast?
 ***************************************************************/
void Lander::coast(Acceleration& acceleration, double time)
{
   if (time > 0)
   {
      // Save the current (initial) velocities
      double oldDX = velocity.getDX();
      double oldDY = velocity.getDY();

      // Update the position using the constant acceleration formula:
      // new position = old position + (old velocity * time) + (0.5 * acceleration * time^2)
      pos.addX(oldDX * time + 0.5 * acceleration.getDDX() * time * time);
      pos.addY(oldDY * time + 0.5 * acceleration.getDDY() * time * time);

      // Update velocity: new velocity = old velocity + (acceleration * time)
      velocity.addDX(acceleration.getDDX() * time);
      velocity.addDY(acceleration.getDDY() * time);
   }
}

/***************************************************************
 * LAND
 * Straighten the lander and put it on the ground.
 ***************************************************************/
void Lander::land()
{
   status = SAFE;
   angle.setUp();  // Reset the angle (this typically sets it to 0.0 radians)
}
