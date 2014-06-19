/***********************************************************************
 * Program:
 *    Skeet Shooter
 * Author:
 *    Jared Wrathall
 * Summary:
 *    
 ***********************************************************************/

#include "asteroid.h"

// set the bounds of the game
float Point::xMin = -600.0;
float Point::xMax =  600.0;
float Point::yMin = -350.0;
float Point::yMax =  350.0;

/*********************************************
 * CALLBACK
 * The main interaction loop of the engine.
 * This gets called from OpenGL.  It give us our
 * interface pointer (where we get our events from)
 * as well as a void pointer which we know is our
 * game class.
 *********************************************/
void callBack(const Interface *pUI, void *p)
{
    Asteroid *pAsteroid = (Asteroid *)p;
   
    //draw it
	 pAsteroid->interact(pUI);
    pAsteroid->advance();
    pAsteroid->draw();
  
}

/*********************************
 * MAIN
 * initialize the drawing window, initialize
 * the game,and run it!
 *********************************/
int main(int argc, char **argv)
{
   // Start the drawing
   Interface ui(argc, argv, "Asteroids!");

   // play the game.  Our function callback will get called periodically
   Asteroid asteroid;  
   ui.run(callBack, (void *)&asteroid);

   return 0;
}

    
