/*************************************************************
 * 1. Name:
 *      Deigo Estrada
 *      Noah McSheehy
 * 2. Assignment Name:
 *      Practice 02: Physics simulator
 * 3. Assignment Description:
 *      Compute how the Apollo lander will move across the screen
 * 4. What was the hardest part? Be as specific as possible.
 *      -a paragraph or two about how the assignment went for you-
 * 5. How long did it take for you to complete the assignment?
 *      -total time in hours: reading the assignment, submitting, etc.
 **************************************************************/
   
#include <iostream>  // for CIN and COUT
#include <cmath>     // for sin, cos, pi, and hypot
using namespace std;
   
#define WEIGHT   15103.000   // Weight in KG
#define GRAVITY     -1.625   // Vertical acceleration due to gravity, in m/s^2
#define THRUST   45000.000   // Thrust of main engine, in Newtons (kg m/s^2)

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
double computeVerticalComponent(double a, double y, double total)
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
   return hypot(x, y)
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
   return d / 360.0 * 2.0 * M_PI;
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

/****************************************************************
 * MAIN
 * Prompt for input, compute new position, and display output
 ****************************************************************/
int main()
{
    // Prompt for input and variables to be computed
    double dx = prompt("What is your horizontal velocity (m/s)? ");
    double dy = prompt("What is your vertical velocity (m/s)? ");
    double y = prompt("What is your altitude (m)? ");
    double x = prompt("What is your position (m)? ");
    double aDegrees = prompt("What is the angle of the LM where 0 is up (degrees)? ");
    double t = prompt("What is the time interval (s)? ");
    double aRadians;            // Angle in radians
    double accelerationThrust;  // Acceleration due to thrust 
    double ddxThrust;           // Horizontal acceleration due to thrust
    double ddyThrust;           // Vertical acceleration due to thrust
    double ddx;                 // Total horizontal acceleration
    double ddy;                 // Total vertical acceleration
    double v;                   // Total velocity

    // Go through the simulator five times
      // your code goes here
      // Hint: Update the position _before_ updating the velocity

      // Output
    cout.setf(ios::fixed | ios::showpoint);
    cout.precision(2);
    cout << "\tNew position:   (" << x << ", " << y << ")m\n";
    cout << "\tNew velocity:   (" << dx << ", " << dy << ")m/s\n";
    cout << "\tTotal velocity:  " << v << "m/s\n\n";


    return 0;
}