/***********************************************************************
 * Header File:
 *    STAR
 * Author:
 *    Br. Helfrich (modified by [Your Name])
 * Summary:
 *    A single star that twinkles
 ************************************************************************/

#pragma once
#include "position.h"   // for Position
#include "uiDraw.h"     // for DRAWSTAR and RANDOM

 /*****************************************************
  * STAR
  * A star that twinkles
  *****************************************************/
class Star
{
public:
   // Constructors
   Star() : pos(0, 0), phase(0) {}
   Star(double x, double y) : pos(x, y), phase(0) {}

   // Reset the star position randomly within given width/height
   void reset(double width, double height)
   {
      pos.setX(random(0.0, width));
      pos.setY(random(0.0, height));
      phase = random(0, 255);  // Randomize the phase
   }

   // Update the star's phase to simulate twinkling
   void twinkle()
   {
      phase = static_cast<unsigned char>((phase + 1) % 256);
   }

   // Draw the star
   void draw(ogstream& gout) const
   {
      gout.drawStar(pos, phase);
   }

private:
   Position pos;
   unsigned char phase;
};
