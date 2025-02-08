/**********************************************************************
 * LAB 06
 * Lunar Lander simulation. This is the Game class and main()
 **********************************************************************/

#include "position.h"    // everything should have a point
#include "angle.h"       // angle of the lander
#include "uiInteract.h"  // for INTERFACE
#include "uiDraw.h"      // for RANDOM and DRAW*
#include "ground.h"      // for GROUND
#include "test.h"        // for the unit tests
#include <cmath>         // for SQRT
#include <cassert>       // for ASSERT
#include <vector>        // for storing multiple stars
#include <cstdlib>       // for rand()
#include <ctime>         // for seeding random numbers
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

private:
   Angle a;
   Ground ground;
   Position posLander;
   std::vector<Position> stars; // Stores 50 star positions
   std::vector<int> phases;     // Stores twinkling phases
};

// Constructor Implementation
Simulator::Simulator(const Position& posUpperRight)
   : ground(posUpperRight),
   posLander(posUpperRight.getX() / 2, posUpperRight.getY() / 2)
{
   srand(static_cast<unsigned>(time(0))); // Seed random number generator

   // Generate 50 stars with random positions and phases
   for (int i = 0; i < 50; i++)
   {
      // Random x-coordinate within screen width
      int x = rand() % static_cast<int>(posUpperRight.getX());

      // Random y-coordinate that is at least 10 pixels above the ground
      int y;
      do {
         y = rand() % static_cast<int>(posUpperRight.getY());
      } while (y <= ground.getElevation(Position(x, 0)) + 10);

      // Create a star Position and add it to the stars vector
      stars.push_back(Position(x, y));

      // Assign a random phase (0 to 255) for the star's twinkling
      phases.push_back(rand() % 256);
   }
}

/******************************
 * SIMULATOR DISPLAY
 * Places objects on the screen
 ******************************/
void Simulator::display()
{

   ogstream gout;
   // Draw all stars
   for (size_t i = 0; i < stars.size(); i++)
   {
      gout.drawStar(stars[i], phases[i]);
   }
   ground.draw(gout);
   gout.drawLander(posLander, a.getRadians());

}

/***********************************
 * SIMULATOR HANDLE INPUT
 * moves objects based on user input
 ***********************************/
void Simulator::handleInput(const Interface* pUI)
{
   if (pUI->isRight())
      a.add(-0.1);  // Rotate right
   if (pUI->isLeft())
      a.add(0.1);   // Rotate left

   // Update twinkling phase of each star randomly
   for (size_t i = 0; i < phases.size(); i++)
   {
      phases[i] = (phases[i] + rand() % 5) % 256; // Small random change in phase
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

   // Handle user input
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

   // Initialize OpenGL
   Position posUpperRight(400, 400);
   Interface ui("Lunar Lander", posUpperRight);

   // Initialize the simulator
   Simulator simulator(posUpperRight);

   // Run the game loop
   ui.run(callBack, static_cast<void*>(&simulator));

   return 0;
}