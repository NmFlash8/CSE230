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
using namespace std;


/****************************************
 * SIMULATOR
 * Everything pertaining to the simulator.
 ****************************************/
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
   Position posStar;
   int phase;
};

// Constructor Implementation
Simulator::Simulator(const Position& posUpperRight)
   : ground(posUpperRight),
   posLander(posUpperRight.getX() / 2, posUpperRight.getY() / 2),
   posStar(200, 300),
   phase(2) {}

/******************************
 * SIMULATOR DISPLAY
 * Places objects on the screen
 ******************************/
void Simulator::display()
{
   ogstream gout;
   ground.draw(gout);
   gout.drawLander(posLander, a.getRadians());
   gout.drawStar(posStar, phase);
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

   phase++; // Update star twinkling phase
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