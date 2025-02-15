/**********************************************************************
 * LAB 06
 * Lunar Lander simulation. This is the Game class and main()
 * Created by Diego Estrada, and Noah McSheehy.
 **********************************************************************/

#include "position.h"    // everything should have a point
#include "angle.h"       // angle of the lander
#include "acceleration.h"// acceleration of lander
#include "uiInteract.h"  // for INTERFACE
#include "uiDraw.h"      // for RANDOM and DRAW*
#include "ground.h"      // for GROUND
#include "test.h"        // for the unit tests
#include "lander.h"      // for all the lander logic
#include "star.h"        // Star class to handle twinkling
#include <cmath>         // for SQRT
#include <cassert>       // for ASSERT
#include <vector>        // for storing multiple stars
#include <cstdlib>       // for rand()
#include <ctime>         // for seeding random numbers
#include <iostream>      // 
using namespace std;


class Simulator
{
public:
   // Constructor
   Simulator(const Position& posUpperRight);

   // Display function
   void display();

   // Handle user input
   void handleInput(const Interface* pUI);

   Thrust thrust;
   Lander lander;
   Acceleration acceleration;
   Ground ground;

private:
   Angle a;
   std::vector<Star> stars; // Stores 50 Star objects
   Position posUpperRight;
};


// Constructor Implementation
Simulator::Simulator(const Position& posUpperRight)
   : ground(posUpperRight),
   lander(Position(posUpperRight.getX() / 2, 300)),
   thrust(),
   posUpperRight(posUpperRight)  // Initialize posUpperRight here
{
   lander.reset(posUpperRight); // Reset the lander

   // Generate 100 stars with random positions and phases using the Star class
   for (int i = 0; i < 100; i++)
   {
      Star star;
      star.reset(posUpperRight.getX(), posUpperRight.getY());
      stars.push_back(star);
   }
}


/******************************
 * SIMULATOR DISPLAY
 * Places objects on the screen
 ******************************/
void Simulator::display()
{
   ogstream gout; // Graphics output

   // Draw all stars using the Star class's draw method
   for (size_t i = 0; i < stars.size(); i++)
   {
      stars[i].draw(gout);
   }

   // Draw ground
   ground.draw(gout);

   // Draw lander using its own position
   lander.draw(thrust, gout);

   // Display status message
   string statusText = "";
   gout.setPosition(Position(200, 300)); // set position to the top middle of the screen
   if (lander.isFlying()) { statusText = "";                      }
   if (lander.isDead())   { statusText = "Crash landing!";        }
   if (lander.isLanded()) { statusText = "Armstrong is awesome!"; }
   gout << statusText;

   // Display info panel in top left
   gout.setPosition(Position(10, 380)); // set position Top left
   gout << "Fuel: "     << lander.getFuel()                          << endl
      //<< "Status: "   << statusText                                << endl
      //<< "Angle: "    << lander.angle.getDegrees()                 << endl
      //<< "Position: ("<< lander.getPosition().getX() << " , " << lander.getPosition().getY() << ")" << endl
        << "Speed: "    << lander.getSpeed() << " m/s "              << endl
        << "Altitude: " << ground.getElevation(lander.getPosition()) << endl;

}


/***********************************
 * SIMULATOR HANDLE INPUT
 * Moves objects based on user input
 ***********************************/
void Simulator::handleInput(const Interface* pUI)
{
   // Update thrust states based on user input
   thrust.set(pUI);

   // Reset the game when spacebar is pressed
   if (pUI->isSpace())
   {
      lander.reset(posUpperRight);
   }

   // Quit the game when 'q' is pressed
   if (pUI->isQ())
   {
      exit(0);
   }

   // Update the twinkling phase of each star by calling its twinkle() method
   for (size_t i = 0; i < stars.size(); i++)
   {
      stars[i].twinkle();
   }
}

/****************************************************
 * SIMULATOR LOGIC HANDLER
 * Updates lander state, checks for landing/crashing
 ****************************************************/
void updateSimulatorLogic(Simulator* pSimulator)
{
   // Variables for landing logic.
   Position landerPos = pSimulator->lander.getPosition();
   double speed = pSimulator->lander.getSpeed();

   // Check if the lander is on the platform and handle landing/crash
   if (pSimulator->ground.onPlatform(landerPos, pSimulator->lander.getWidth()))
   {
      if (speed <= pSimulator->lander.getMaxSpeed())
      {
         pSimulator->lander.land();
         //cout << "SUCCESS" << endl;
      }
      else
      {
         pSimulator->lander.crash();
         //cout << "Crashed on platform" << endl;
      }
   }

   // Check if the lander hit the ground and handle crash
   else if (pSimulator->ground.hitGround(landerPos, pSimulator->lander.getWidth()))
   {
      pSimulator->lander.crash();
      //cout << "Lander hit the ground" << endl;
   }

   // If the lander is still flying, update its state
   if (pSimulator->lander.isFlying())
   {
      // Update lander acceleration and position
      Acceleration acceleration = pSimulator->lander.input(pSimulator->thrust, -1);
      pSimulator->lander.coast(acceleration, .2);
   }
}


/*************************************
 * CALLBACK
 * Handle one frame of the simulator
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   Simulator* pSimulator = static_cast<Simulator*>(p);

   // Draw the simulator
   pSimulator->display();

   // Update simulator logic (landing, crashing, coasting, etc.)
   updateSimulatorLogic(pSimulator);

   // Handle user input for thrust adjustments
   pSimulator->handleInput(pUI);
}


/*********************************
 * Main Function
 *********************************/
#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPSTR pCmdLine,
   _In_ int nCmdShow)
#else
int main(int argc, char** argv)
#endif
{
   // Run unit tests
   testRunner();

   // Initialize OpenGL window parameters
   Position posUpperRight(400, 400);
   Interface ui("Lunar Lander", posUpperRight);

   // Initialize the simulator
   Simulator simulator(posUpperRight);

   // Run the game loop
   ui.run(callBack, static_cast<void*>(&simulator));

   return 0;
}
