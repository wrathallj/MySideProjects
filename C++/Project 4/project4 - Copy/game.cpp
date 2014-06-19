/***********************************************************************
 * Program:
 *    Project 2, Skeet
 *    Brother Helfrich, CS165
 * Author:
 *    Jared Wrathall
 * Summary: 
 *    
 *    Estimated:  25.0 hrs   
 *    Actual:     0.0 hrs
 *      Please describe briefly what was the most difficult part
 ************************************************************************/

#include <iostream>
#include "asteroid.h"
#define deg2rad(value) ((3.14159265 / 180) * (value))
#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define MIN(x,y) ((x) < (y) ? (x) : (y))


/*************************************************
 *************************************************
 ******************Asteroids**********************
 *************************************************
 ************************************************/

/**************************************************
 * ASTEROID : CONSTRUCTOR
 *      Initialize all objects;
 *************************************************/
Asteroid :: Asteroid()
{
	Point point;
	frame = 0;
		point.setX(random(-250, 250));
		point.setY(random(-250,250));

		object.push_back(new BigRock (point));
	
		point.setX(random(-250, 250));
		point.setY(random(-250,250));

	object.push_back(new BigRock (point));
	
		point.setX(random(-250, 250));
		point.setY(random(-250,250));

	object.push_back(new BigRock (point));

		point.setX(random(-250, 250));
		point.setY(random(-250,250));

	object.push_back(new BigRock (point));
	
		point.setX(random(-250, 250));
		point.setY(random(-250,250));

	object.push_back(new BigRock (point));

		point.setX(random(-250, 250));
		point.setY(random(-250,250));

	object.push_back(new BigRock (point));

		point.setX(random(-250, 250));
		point.setY(random(-250,250));

	object.push_back(new BigRock (point));
}


/**************************************************
 * Asteroid : ADVANCE
 *      Just move the game along.
 *************************************************/
void Asteroid :: advance()
{
	Point temp;
	
	if(ship.getIsDead())
	frame++;
	

	if(frame >= 30)
		{
			ship.getVector().getPoint().setX(0);
			ship.getVector().getPoint().setY(0);
			ship.setIsDead(false);
			frame = 0;

		}

	if(ship.getIsDead() == false)
	ship.advance();
	if(ship.getIsDead() == false)
	{
	for(int i = 0; i < 5; i++)
	{
			bullet[i].advance();
	}
	}
		for (int i = 0; i < object.size(); i++)
	{
		
		if(object[i]->getIsDead())
		{
			object[i]->regen();
			object[i]->setIsDead(false);
		}
		
		object[i]->advance();

		if(object[i]->getIsDead() == false)
		{
			if ( 25 > (ship.getVector() -object[i]->getVector()) && object[i]->getType() == 'B' )
					  ship.setIsDead(true);
			if ( 15 > (ship.getVector() -object[i]->getVector()) && object[i]->getType() == 'M')
					  ship.setIsDead(true);
			if ( 5 > (ship.getVector() -object[i]->getVector()) && object[i]->getType() == 'L')
					  ship.setIsDead(true);
			for(int j = 0; j <  5; j++)
				{
					if(bullet[j].getIsDead() == false)
					{
					
						if (15 > (bullet[j].getVector() - object[i]->getVector()) && object[i]->getType() == 'M')
						{
						bullet[j].setIsDead(true);
						object.push_back(new LittleRock (object[i]->getVector().getPoint()));
						object.push_back(new LittleRock (object[i]->getVector().getPoint()));
						object.push_back(new LittleRock (object[i]->getVector().getPoint()));
						object.push_back(new LittleRock (object[i]->getVector().getPoint()));
						object.push_back(new LittleRock (object[i]->getVector().getPoint()));
						cout << i << endl;
						 object.erase(object.begin() + i); 
						 if( i > 0)
						i--;
					  
						}
					}			
				}		
		}
	}
		for (int i = 0; i < object.size(); i++)
		{
			if(object[i]->getIsDead() == false)
			{
			
			for(int j = 0; j <5; j++)
				{
					if(bullet[j].getIsDead() == false)
					{
					
					if ( 25 > (bullet[j].getVector() - object[i]->getVector()) && object[i]->getType() == 'B')
						{
						bullet[j].setIsDead(true);
						object.push_back(new MedRock (object[i]->getVector().getPoint()));
						object.push_back(new MedRock (object[i]->getVector().getPoint()));
						object.push_back(new MedRock (object[i]->getVector().getPoint()));
				
						cout << i << endl;
						 object.erase(object.begin() + i);
						
					 if( i > 0)
						i--;
					
						}
					}			
				}		
			}	
		}
				
		
		for (int i = 0; i < object.size() ; i++)
		{
			if(object[i]->getIsDead() == false)
			{
			
			for(int j = 0; j < 5; j++)
				{
					if(bullet[j].getIsDead() == false)
					{
					
						if ( 5> (bullet[j].getVector() - object[i]->getVector()) && object[i]->getType() == 'L')
					{
						bullet[j].setIsDead(true);
					   
						object.erase(object.begin() + i);
						 if( i > 0)
						i--;
					} 

					}			
				}		
			}

		}
	
}

void Asteroid ::interact(const Interface *pUI)
{
	if(ship.getIsDead() == false)
	{
		for (int i = 0; i < ammo.size(); i++)
      if (bullet[i].getIsDead())
         {
			 ammo.pop_back();
		 }
		
	if(pUI->isSpace())
	{
		ammo.push_back(1);
	if(ammo.size() <= 5 )
	{
		ammo.push_back(1);
		for (int i = 0; i< ammo.size(); i++)
		{
			if(bullet[i].getIsDead())
				{
					ammo.pop_back();
					bullet[i].fire(ship.getAngle(), ship.getPoint());
					bullet[i].setFrames(0);
				}
				
		}
	}
	}

	 if (pUI->isDown())
   {
      int spread = ship.getAngle();
      
	    
      for (int j = 0; j <= 5; j++)
      {
		  cout << ammo.size() << endl;
         spread += 75;
         // add to the amount of bullets on screen
         ammo.push_back(spread);
      
         // make sure there are no more than 5 bullets on screen
         if (ammo.size() <= 5)
         {
            for (int k = 0; k < ammo.size(); k++)
            {
              
               if (bullet[k].getIsDead())
                  bullet[k].fire(ammo[k], ship.getPoint());
            }

         }
		 	if(bullet[j].getIsDead())
				{
					ammo.pop_back();
					bullet[j].fire(ship.getAngle(), ship.getPoint());
					bullet[j].setFrames(0);
				}
      }
   }
	 


	ship.move(pUI->isUp(), pUI->isLeft(), pUI->isRight());
	}
}

void Asteroid ::draw()
{
		for (int i = 0; i < object.size(); i++)
	{
		
			object[i]->draw();
			
	}
		if(ship.getIsDead() == false)
		ship.draw();
	
	for (int i = 0; i< 5; i++)
	{
		if (bullet[i].getIsDead() == false)
		 bullet[i].draw();
			
	}
}


/*************************************************
 *************************************************
 *******************Ship*************************
 *************************************************
 ************************************************/



/*************************************************
 * SHIP :: CONSTRUCTOR
 ************************************************/
Ship::Ship() 
{
	isDead = false;
	speed = 0;
	angle = 0;
   // set the location in the beginning
   vector.getPoint().setX(0);
   vector.getPoint().setY(0);
   vector.setDx(0);	
   vector.setDy(0);		
   start = false;
   
   back.getPoint().setX(0);
   back.getPoint().setY(0);
   back.setDx(0);
   back.setDy(0);

   back2.getPoint().setX(0);
   back2.getPoint().setY(0);
   back2.setDx(0);
   back2.setDy(0);
   int frames = 0;
}

/*************************************************
 * SHIP : ADVANCE
 *      Change the points of the ship
 ************************************************/
void Ship::advance()
{
	// frame count
	frames++;
 
	wrap();
 
 
	// get where the ship is
	vector.getPoint().addX(vector.getDx());
	vector.getPoint().addY(vector.getDy());
 
	// every three frames reset jets
	if(frames % 3 == 0)
	{
		back.getPoint().setX(vector.getPoint().getX());
		back.getPoint().setY(vector.getPoint().getY());
		back2.getPoint().setX(vector.getPoint().getX());
		back2.getPoint().setY(vector.getPoint().getY());

		// we don't want this getting too big
		frames = 0;
	}

	// get where the ships jets are
	back.getPoint().addX(back.getDx());
	back.getPoint().addY(back.getDy());

	back2.getPoint().addX(back2.getDx());
	back2.getPoint().addY(back2.getDy());

}

/*************************************************
 * SHIP : DRAW
 *      Draw the ship
 ************************************************/
void Ship::draw()
{
	
	// ship draw
   drawShip(vector.getPoint(), getAngle());

   // safety circle
   if(!start)
		drawCircle(vector.getPoint(), 10, 100,0);
   // draw jets
   if(start)
   {
		drawDot(back.getPoint());
		drawDot(back2.getPoint());
   }
}

/***************************************************
 * SHIP : MOVE
 *      Change the angle of the ship whether you push 
 *      the left, or right. Change speed with up
 **************************************************/
void Ship :: move(int up, int left, int right)
{
	// change the angles
	if(left )	
	{
		angle += 13;
	}
	else if(right)
	{	
		
		angle -= 13;
	}

	// if pressing up and not above max speed
	if(up && speed < 50)
	{
		// the game has begun
		start = true;

		// accelerate speed
		speed += 3;

		// set the new x speed and y speed
		vector.setDx(-sin(deg2rad(angle + 90)) * speed / 15);
		vector.setDy( cos(deg2rad(angle + 90)) * speed / 15);
	}
	
	// once you start you never stop
	if (start && speed > 10)
	{
		// decelerate
		speed -= 1;

		// set the new speed for...
		// ship
		vector.setDx(-sin(deg2rad(angle + 90)) * speed / 15);
		vector.setDy( cos(deg2rad(angle + 90)) * speed / 15);

		// jet 1
		back.setDx(-sin(deg2rad(angle - 75)) * speed / 15);
		back.setDy( cos(deg2rad(angle - 75)) * speed / 15);

		// jet 2
		back2.setDx(-sin(deg2rad(angle - 105)) * speed / 15);
		back2.setDy( cos(deg2rad(angle - 105)) * speed / 15);
	}

}
/***************************************************
 * SHIP : Wrap
 *      If you hit the edge of the screen you come out on other side
 **************************************************/
void Ship :: wrap()
{
	if ( vector.getPoint().getX() > vector.getPoint().getXMax())
		vector.getPoint().setX(vector.getPoint().getXMin());
	if ( vector.getPoint().getY() > vector.getPoint().getYMax())
		vector.getPoint().setY(vector.getPoint().getYMin());
	if ( vector.getPoint().getX() < vector.getPoint().getXMin())
		vector.getPoint().setX(vector.getPoint().getXMax());
	if ( vector.getPoint().getY() < vector.getPoint().getYMin())
		vector.getPoint().setY(vector.getPoint().getYMax());
}
/*************************************************
 *************************************************
 *******************OBJECTS************************
 *************************************************
 ************************************************/


/*************************************************
 *************************************************
 ****************LITTLEROCK***********************
 *************************************************
 ************************************************/

/*************************************************
 * ROCK :: CONSTRUCTOR
 *      set dead to true in the beginning so it
 *      does not just appear.
 ************************************************/
LittleRock :: LittleRock(Point point)
{
   start = point;
   rockSize = 5;
}

/*************************************************
 * ROCK : DRAW
 * Draw the stuff
 ************************************************/
void LittleRock::draw() 
{
   // drawing the bird at each new location.

   drawCircle(vector.getPoint(), rockSize, 20 * 2, 0);
}

/**************************************************
 *BIRD : ADVANCE
 *************************************************/
void LittleRock :: advance()
{
	wrap();
   // move the bird across the screen. 
   vector.getPoint().addX(vector.getDx()); 
   vector.getPoint().addY(vector.getDy());
}

/*************************************************
 * BIRD : REGEN
 *      Draw the stuff after the bird has been
 *      killed
 ************************************************/
void LittleRock::regen()
{
   
  vector.getPoint().setX(start.getX());
  vector.getPoint().setY(start.getY());

   

   vector.setDx(random(-4,4));
   vector.setDy(random(-4,4));

   // move even or down if the random location is
   // grater than 0
   
 
   
     
}

/**************************************************
 * BIRD : KILL
 *  DIE DIE DIE
 *************************************************/
void LittleRock :: kill()
{

   vector.getPoint().setX(-200);
   vector.getPoint().setY(0);
   vector.setDy(0);
   vector.setDx(0);
      
}

/***************************************************
 * LITTLEROCK : Wrap
 *      If you hit the edge of the screen you come out on other side
 **************************************************/
void LittleRock :: wrap()
{
	if ( vector.getPoint().getX() > vector.getPoint().getXMax())
		vector.getPoint().setX(vector.getPoint().getXMin());
	if ( vector.getPoint().getY() > vector.getPoint().getYMax())
		vector.getPoint().setY(vector.getPoint().getYMin());
	if ( vector.getPoint().getX() < vector.getPoint().getXMin())
		vector.getPoint().setX(vector.getPoint().getXMax());
	if ( vector.getPoint().getY() < vector.getPoint().getYMin())
		vector.getPoint().setY(vector.getPoint().getYMax());
}

/*************************************************
 *************************************************
 *********************BIGROCK************************
 *************************************************
 ************************************************/

/*************************************************
 * ROCK :: CONSTRUCTOR
 *      set dead to true in the beginning so it
 *      does not just appear.
 ************************************************/
BigRock :: BigRock(Point point)
{
   start = point;
   rockSize = 25;
}

/*************************************************
 * ROCK : DRAW
 * Draw the stuff
 ************************************************/
void BigRock::draw() 
{
   // drawing the bird at each new location.

   drawCircle(vector.getPoint(), rockSize, 4, 25 );
}

/**************************************************
 *BIRD : ADVANCE
 *************************************************/
void BigRock :: advance()
{
	wrap();
   // move the bird across the screen. 
   vector.getPoint().addX(vector.getDx()); 
   vector.getPoint().addY(vector.getDy());
}

/*************************************************
 * BIRD : REGEN
 *      Draw the stuff after the bird has been
 *      killed
 ************************************************/
void BigRock::regen()
{
   
   vector.getPoint().setX(start.getX()); 
   vector.getPoint().setY(start.getY());

   

   vector.setDx(random(-4,4));
   vector.setDy(random(-4,4));

   // move even or down if the random location is
   // grater than 0
   
 
   
     
}

/**************************************************
 * BIRD : KILL
 *  DIE DIE DIE
 *************************************************/
void BigRock :: kill()
{

   vector.getPoint().setX(-200);
   vector.getPoint().setY(0);
   vector.setDy(0);
   vector.setDx(0);
      
}

/***************************************************
 * LITTLEROCK : Wrap
 *      If you hit the edge of the screen you come out on other side
 **************************************************/
void BigRock :: wrap()
{
	if ( vector.getPoint().getX() > vector.getPoint().getXMax())
		vector.getPoint().setX(vector.getPoint().getXMin());
	if ( vector.getPoint().getY() > vector.getPoint().getYMax())
		vector.getPoint().setY(vector.getPoint().getYMin());
	if ( vector.getPoint().getX() < vector.getPoint().getXMin())
		vector.getPoint().setX(vector.getPoint().getXMax());
	if ( vector.getPoint().getY() < vector.getPoint().getYMin())
		vector.getPoint().setY(vector.getPoint().getYMax());
}

/*************************************************
 *************************************************
 *******************MEDROCK***********************
 *************************************************
 ************************************************/

/*************************************************
 * ROCK :: CONSTRUCTOR
 *      set dead to true in the beginning so it
 *      does not just appear.
 ************************************************/
MedRock :: MedRock(Point point)
{
   start = point;
   rockSize = 10;
}

/*************************************************
 * ROCK : DRAW
 * Draw the stuff
 ************************************************/
void MedRock::draw() 
{
   // drawing the bird at each new location.

   drawCircle(vector.getPoint(), rockSize, 3 , 0);
}

/**************************************************
 *BIRD : ADVANCE
 *************************************************/
void MedRock :: advance()
{
	wrap();
   // move the bird across the screen. 
   vector.getPoint().addX(vector.getDx()); 
   vector.getPoint().addY(vector.getDy());
}

/*************************************************
 * BIRD : REGEN
 *      Draw the stuff after the bird has been
 *      killed
 ************************************************/
void MedRock::regen()
{
   
  vector.getPoint().setX(start.getX());
  vector.getPoint().setY(start.getY());

   

   vector.setDx(random(-4,4));
   vector.setDy(random(-4,4));

   // move even or down if the random location is
   // grater than 0
   
 
   
     
}

/**************************************************
 * BIRD : KILL
 *  DIE DIE DIE
 *************************************************/
void MedRock :: kill()
{

   vector.getPoint().setX(-200);
   vector.getPoint().setY(0);
   vector.setDy(0);
   vector.setDx(0);
      
}

/***************************************************
 * LITTLEROCK : Wrap
 *      If you hit the edge of the screen you come out on other side
 **************************************************/
void MedRock :: wrap()
{
	if ( vector.getPoint().getX() > vector.getPoint().getXMax())
		vector.getPoint().setX(vector.getPoint().getXMin());
	if ( vector.getPoint().getY() > vector.getPoint().getYMax())
		vector.getPoint().setY(vector.getPoint().getYMin());
	if ( vector.getPoint().getX() < vector.getPoint().getXMin())
		vector.getPoint().setX(vector.getPoint().getXMax());
	if ( vector.getPoint().getY() < vector.getPoint().getYMin())
		vector.getPoint().setY(vector.getPoint().getYMax());
}

/*************************************************
 *************************************************
 *******************BULLET************************
 *************************************************
 ************************************************/


/************************************************
 * BULLET : BULLET
 *      Constructor
 ***********************************************/ 
Bullet :: Bullet()
{
	
	// starts off dead
    isDead = true;
}

/*************************************************
 * BULLET : DRAW
 *      Draw the stuff
 ************************************************/
void Bullet::draw()
{
	
   // draw the bullet in each location
   drawDot(vector.getPoint());
}

/***********************************************
 * BULLET : ADVANCE
 *      Draw the bullet if the bullet reaches
 *      the X min or the Y max.  Set the bullet
 *      to dead.
 **********************************************/
void Bullet :: advance()
{
     
	// moving bullet
	vector.getPoint().addX(vector.getDx()); 
    vector.getPoint().addY(vector.getDy());

	frames++;
   // if bullet is outside the bounds of the board.
   if (frames == 30)
   {
      isDead = true;
   }
}


/***********************************************
 * BULLET : FIRE
 *      Set the speed of the bullet and which
 *      angle it is supposed to go
 **********************************************/
void Bullet::fire(int angle, Point shipPoint)
{
   // set the speed of the bullet
	int bulletSpeed = 10;
   
   vector.getPoint().setX(shipPoint.getX());   
   vector.getPoint().setY(shipPoint.getY());
    
   vector.setDx(-sin (deg2rad(angle + 90)) * bulletSpeed);
   vector.setDy(cos(deg2rad(angle + 90)) * bulletSpeed);

   // set the direction of the bullet
    isDead = false;  
}


/**************************************************
 * BULLET : KILL
 *      Send the bullet out of bounds so it
 *      dissapears
 *************************************************/
void Bullet :: kill()
{
   // set the location of dead bullets
   vector.getPoint().setX(-200);
   vector.getPoint().setY( 200);
   vector.setDy(0);
   vector.setDx(0);
   isDead = true;
}

/**********************************************
 **********************************************
 ******************SCORE***********************
 **********************************************
 *********************************************/

/**********************************************
 **********************************************
 *****************VECTOR***********************
 **********************************************
 *********************************************/



/**********************************************
 * VECTOR : operator -
 *       
 *********************************************/
float Vector:: operator - ( Vector &rhs) 
{
   float minDist = 2000.0; 
   float distSquared;
   float xDistSquared = 0.0;
   float yDistSquared = 0.0;
   float slice = 1/ MAX(MAX(abs(rhs.dx), abs(rhs.dy)),MAX(abs(dx),abs(dy)));
   int i = 0;
   
   for (float per = 0; per < 1; per += slice)
   {
      // getting the X distance squared
      xDistSquared = (((rhs.getPoint().getX() + rhs.dx * per) -
                       (point.getX()          +     dx * per)));
     
      xDistSquared *= xDistSquared;
    
      // getting the Y distance squared
      yDistSquared = (((rhs.getPoint().getY() + rhs.dy * per) -
                       (point.getY()          +     dy * per)));
     
      yDistSquared *= yDistSquared;

      // Setting the total distance squared
      distSquared   = yDistSquared + xDistSquared;
          
      minDist = MIN(distSquared, minDist);
   }
   
   return sqrt(minDist);
}

/**********************************************
 * VECTOR : SETDX
 *      Allow others to set the dx if needed.
 *********************************************/
void Vector :: setDx(float dx)
{
   this->dx = dx;
}

/*********************************************
 * VECTOR : SET DY
 *      Allows others to set the dy if needed.
 ********************************************/
void Vector :: setDy(float dy)
{
   this->dy = dy;
}


/**********************************************
 * VECTOR : operator +
 *       
 *********************************************/
Vector Vector:: operator +( Vector &rhs) 
{
   Vector newVector;
   newVector.dx = rhs.dx + dx;
   newVector.dy = rhs.dy + dy;
   return newVector;
}

/**********************************************
 * VECTOR : operator +
 *       
 *********************************************/
Vector & Vector:: operator +=(float delta)
{
   
   dx = dx + delta;
   dy = dy + delta;
   return *this;   
}

/**********************************************
 * VECTOR : operator (a++) 
 *       
 *********************************************/
Vector Vector:: operator ++(int postFix)
{
   Vector vectorNew;
   vectorNew.dx += 1;
   vectorNew.dy += 1;
   return vectorNew;   
}

/**********************************************
 * VECTOR : operator (++a) 
 *       
 *********************************************/
Vector & Vector:: operator ++()
{
   dx += 1;
   dy += 1;
   return *this;   
}

/**********************************************
 * VECTOR : OPERATOR == 
 *       
 *********************************************/
bool Vector:: operator == (const Vector & rhs) const
{
   return (dx == rhs.dx && dy == dy);
}

/**********************************************
 * VECTOR : OPERATOR = 
 *       
 *********************************************/
Vector & Vector :: operator = (Vector & rhs) 
{
   dy = rhs.dy;
   dx = rhs.dx;
      
   return *this; 
}



