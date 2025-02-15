/**********************************************************************
 * LAB 06
 * Lunar Lander simulation. This is the Game class and main()
 **********************************************************************/

#include "position.h"    // everything should have a point
#include "angle.h"       // angle of the lander
#include "acceleration.h"// acceleration of lander
#include "uiInteract.h"  // for INTERFACE
#include "uiDraw.h"      // for RANDOM and DRAW*
#include "ground.h"      // for GROUND
#include "test.h"        // for the unit tests
#include "lander.h"      //
#include "star.h"        // Star class to handle twinkling
#include <cmath>         // for SQRT
#include <cassert>       // for ASSERT
#include <vector>        // for storing multiple stars
#include <cstdlib>       // for rand()
#include <ctime>         // for seeding random numbers
#include <iostream>
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

private:
   Angle a;
   Ground ground;
   std::vector<Star> stars; // Stores 50 Star objects
};


// Constructor Implementation
Simulator::Simulator(const Position& posUpperRight)
   : ground(posUpperRight),
   lander(Position(posUpperRight.getX() / 2, 300)),
   thrust()
{
   srand(static_cast<unsigned>(time(0))); // Seed the random number generator

   lander.reset(posUpperRight); // Reset the lander

   // Generate 50 stars with random positions and phases using the Star class
   for (int i = 0; i < 50; i++)
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
   ogstream gout;

   // Draw all stars using the Star class's draw method
   for (size_t i = 0; i < stars.size(); i++)
   {
      stars[i].draw(gout);
   }

   // Draw ground
   ground.draw(gout);

   // Draw lander using its own position
   lander.draw(thrust, gout);

   // Draw information last
   gout.setPosition(Position(10, 380));
   gout << "Fuel: "     << lander.getFuel()                          << endl
        << "Angle: "    << lander.angle.getDegrees()                 << endl
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

   // Update the twinkling phase of each star by calling its twinkle() method
   for (size_t i = 0; i < stars.size(); i++)
   {
      stars[i].twinkle();
   }
}


/*************************************
 * CALLBACK
 * Handle one frame of the simulator
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   Simulator* pSimulator = static_cast<Simulator*>(p);

   // Draw the game
   pSimulator->display();

   // Update lander acceleration (the -1 represents gravity)
   Acceleration acceleration = pSimulator->lander.input(pSimulator->thrust, -1);

   // Update lander position
   pSimulator->lander.coast(acceleration, .2);

   // Handle user input (including star twinkling)
   pSimulator->handleInput(pUI);

   // Debug output (optional)
   // cout << "Position: (" << pSimulator->lander.getPosition().getX() << ", "
   //      << pSimulator->lander.getPosition().getY() << ")" << endl;
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
