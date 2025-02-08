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
   status = DEAD;
}

/***************************************************************
 * DRAW
 * Draw the lander on the screen
 ***************************************************************/
void Lander::draw(const Thrust& thrust, ogstream& gout) const
{
}

/***************************************************************
 * INPUT
 * Accept input from the Neil Armstrong
 ***************************************************************/
Acceleration Lander::input(const Thrust& thrust, double gravity)
{
   pos.setX(-99.9);
   return Acceleration();
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