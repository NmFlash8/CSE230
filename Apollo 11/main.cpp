/*************************************************************
 * 1. Name:
 *      Diego Estrada
 *      Noah Mcsheehy
 * 2. Assignment Name:
 *      Lab 02: Apollo 11
 * 3. Assignment Description:
 *      Simulate the Apollo 11 landing
 * 4. What was the hardest part? Be as specific as possible.
 *      It took us a little while to figure out that the program 
 *      just needed a few adjustments to work. For example we didn't 
 *      realize the position was suppose to be assumed to 0, and figuring 
 *      out how to measure in speed was confusing till we saw it was 
 *      already a variable the functions were using.
 * 5. How long did it take for you to complete the assignment?
 *      ~3 hours. 30 minutes for formatting, 
 *      1 hour for reading and understanding 
 *      1.5 hours for coding 
 *****************************************************************/

#include <iostream>  // for CIN and COUT
#include <cmath>     // for sin, cos, pi, and hypot
#include <iomanip>   // for setw() formatting
using namespace std;

#define WEIGHT   15103.000   // Weight in KG
#define GRAVITY     -1.625   // Vertical acceleration due to gravity, in m/s^2
#define THRUST   45000.000   // Thrust of main engine, in Newtons (kg m/s^2)
#define M_PI 3.14159265358979323846 // Had issues importing M_PI from cmath, so we just declared it as a constant.

/***************************************************
 * COMPUTE DISTANCE
 * Apply inertia to compute a new position using the distance equation.
 * The equation is:
 *     s = s + v t + 1/2 a t^2
 * INPUT
 *     s : original position, in meters
 *     v : velocity, in meters/second
 *     a : acceleration, in meters/second^2
 *     t : time, in seconds
 * OUTPUT
 *     s : new position, in meters
 **************************************************/
double computeDistance(double s, double v, double a, double t)
{
   // Simplfied Algebra
   // s = s + v * t + 1.0 / 2.0 * a * pow(t, 2.0)
   // s = s + v * t + 0.5 * a * pow(t, 2.0)        Simplify 1 / 2
   // s = s + v * t + 0.5 * a * t * t              Convert pow(t, 2.0) to t * t
   return s + v * t + 0.5 * a * t * t;
}

/**************************************************
 * COMPUTE ACCELERATION
 * Find the acceleration given a thrust and mass.
 * This will be done using Newton's second law of motion:
 *     f = m * a
 * INPUT
 *     f : force, in Newtons (kg * m / s^2)
 *     m : mass, in kilograms
 * OUTPUT
 *     a : acceleration, in meters/second^2
 ***************************************************/
double computeAcceleration(double f, double m)
{
   // Simplfied Algebra
   // a = f / m   Divide m to separate a
   return f / m;
}

/***********************************************
 * COMPUTE VELOCITY
 * Starting with a given velocity, find the new
 * velocity once acceleration is applied. This is
 * called the Kinematics equation. The
 * equation is:
 *     v = v + a t
 * INPUT
 *     v : velocity, in meters/second
 *     a : acceleration, in meters/second^2
 *     t : time, in seconds
 * OUTPUT
 *     v : new velocity, in meters/second
 ***********************************************/
double computeVelocity(double v, double a, double t)
{
   // v = v + a * t
   return v + a * t;
}


/***********************************************
 * COMPUTE VERTICAL COMPONENT
 * Find the vertical component of a velocity or acceleration.
 * The equation is:
 *     cos(a) = y / total
 * This can be expressed graphically:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    |a/
 *    |/
 * INPUT
 *     a : angle, in radians
 *     total : total velocity or acceleration
 * OUTPUT
 *     y : the vertical component of the total
 ***********************************************/
double computeVerticalComponent(double a, double total)
{
   // Simplfied Algebra
   // y = cos(a) * total   Move total to the other side.
   return cos(a) * total;
}


/***********************************************
 * COMPUTE HORIZONTAL COMPONENT
 * Find the horizontal component of a velocity or acceleration.
 * The equation is:
 *     sin(a) = x / total
 * This can be expressed graphically:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    |a/
 *    |/
 * INPUT
 *     a : angle, in radians
 *     total : total velocity or acceleration
 * OUTPUT
 *     x : the vertical component of the total
 ***********************************************/
double computeHorizontalComponent(double a, double total)
{
   // Simplfied Algebra
   // x = sin(a) * total   Move total to the other side.
   return sin(a) * total;
}

/************************************************
 * COMPUTE TOTAL COMPONENT
 * Given the horizontal and vertical components of
 * something (velocity or acceleration), determine
 * the total component. To do this, use the Pythagorean Theorem:
 *    x^2 + y^2 = t^2
 * where:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    | /
 *    |/
 * INPUT
 *    x : horizontal component
 *    y : vertical component
 * OUTPUT
 *    total : total component
 ***********************************************/
double computeTotalComponent(double x, double y)
{
   // Simplified Algebra
   // t^2 = x^2 + y^2      Move the total
   // t = sqrt(x^2 + y^2)  Apply sqrt to both sides
   // t = hypot(x, y)      Use the hypotenuse for further simplification
   return hypot(x, y);
}


/*************************************************
 * RADIANS FROM DEGREES
 * Convert degrees to radians:
 *     radians / 2pi = degrees / 360
 * INPUT
 *     d : degrees from 0 to 360
 * OUTPUT
 *     r : radians from 0 to 2pi
 **************************************************/
double radiansFromDegrees(double d)
{
   // M_PI stands for pi 3.14
   // Simplified Algebra
   // r / 2 * M_PI = d / 360         Standard
   // r = (d / 360.0) * 2.0 * M_PI   Separate r 
   // r = (d / 360.0) * 2.0 * M_PI   Simplify
   return d / 180.0 * M_PI;
}


/**************************************************
 * PROMPT
 * A generic function to prompt the user for a double
 * INPUT
 *      message : the message to display to the user
 * OUTPUT
 *      response : the user's response
 ***************************************************/
double prompt(const char* message)
{
   double response;
   cout << message;
   cin >> response;
   return response;
}


/***************************************************
 * DISPLAY STATUS
 * Display the current time, position, velocity, speed,
 * and angle of the Lunar Module.
 * INPUT
 *     time  : current time in seconds
 *     x     : horizontal position in meters
 *     y     : vertical position (altitude) in meters
 *     dx    : horizontal velocity in meters/second
 *     dy    : vertical velocity in meters/second
 *     angle : angle of the Lunar Module in degrees
 ***************************************************/
void displayStatus(int time, double x, double y, double dx, double dy, double angle) {
   double speed = computeTotalComponent(dx, dy);
   // Display the console out in the mannor shown in example
   cout << setw(2)    << time  << "s - "
        << "x,y: ("   << x     << ", "   << y  << ") m  "
        << "dx,dy: (" << dx    << ", "   << dy << ") m/s  "
        << "speed: "  << speed << " m/s  "
        << "angle: "  << angle << " deg" << endl;

}


/****************************************************************
 * MAIN
 * Prompt for input, compute new position, and display output
 ****************************************************************/
int main()
{
   // Prompt for initial conditions
   double dy = prompt("What is your vertical velocity (m/s)? ");
   double dx = prompt("What is your horizontal velocity (m/s)? ");
   double y = prompt("What is your altitude (m)? ");
   double x = 0.0; // Position
   double aDegrees = prompt("What is the angle of the LM where 0 is up (degrees)? ");
   double t = 1.0; // Time

   // Blank line seporator
   cout << endl;

   // Calculate aditional conditions
   double aRadians = radiansFromDegrees(aDegrees);
   double accelerationThrust = computeAcceleration(THRUST, WEIGHT);
   double ddxThrust, ddyThrust, ddx, ddy, v;

   // Set the console out display to show decimals
   cout.setf(ios::fixed | ios::showpoint);
   cout.precision(2);

   for (int simulation = 0; simulation < 10; ++simulation)
   {
      if (simulation % 5 == 0) // Display the message at the start and every 5th simulation
      {
         cout << "For the next 5 seconds with the main engine on, the position of the lander is: \n";
         cout << endl;
      }
      if (simulation == 5) // Allow rotation change at the 5-second mark
      {
         aDegrees = prompt("Enter new angle for the LM (degrees): ");
         aRadians = radiansFromDegrees(aDegrees);
         cout << endl;
      }

      // Compute thrust components
      ddxThrust = computeHorizontalComponent(aRadians, accelerationThrust);
      ddyThrust = computeVerticalComponent(aRadians, accelerationThrust);

      // Compute total accelerations
      ddx = ddxThrust;
      ddy = ddyThrust + GRAVITY;

      // Update position
      x = computeDistance(x, dx, ddx, t);
      y = computeDistance(y, dy, ddy, t);

      // Update velocity
      dx = computeVelocity(dx, ddx, t);
      dy = computeVelocity(dy, ddy, t);

      // Compute total velocity
      v = computeTotalComponent(dx, dy);

      // Display status
      displayStatus(simulation + 1, x, y, dx, dy, aDegrees);

   }
   return 0;
}
