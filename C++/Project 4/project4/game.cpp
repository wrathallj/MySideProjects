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
	bomb = false;
	bombSize = 0;
	over ="GAME OVER";
	char * x;
			 x = (char*)over.c_str();

			
			 text[0] = &x[0];
	frame2 = 0;
	hits = 0;
	Point point;
	Point gameOver;
	gameOver.setX(-150);
	gameOver.setY(-10);
	lives = 3;
	frame = 0;
		point.setX(random(-600, 600));
		point.setY(random(-350,350));

		object.push_back(new BigRock (point));
	
		
		point.setX(random(-600, 600));
		point.setY(random(-350,350));

		object.push_back(new BigRock (point));
		
		point.setX(random(-600, 600));
		point.setY(random(-350,350));

		object.push_back(new BigRock (point));

		point.setX(random(-600, 600));
		point.setY(random(-350,350));

		object.push_back(new BigRock (point));

		point.setX(random(-600, 600));
		point.setY(random(-350,350));

		object.push_back(new BigRock (point));

		point.setX(random(-600, 600));
		point.setY(random(-350,350));

		object.push_back(new BigRock (point));

		point.setX(random(-600, 600));
		point.setY(random(-350,350));

		object.push_back(new Shield (point));
		object.push_back(new Bomb (point));
}


/**************************************************
 * Asteroid : ADVANCE
 *      Just move the game along.
 *************************************************/
void Asteroid :: advance()
{
	Point temp;
	
	if (spawner.getRespawn() == true)
		{
				object.push_back(new BigRock (spawner.getPoint()));
							object.push_back(new BigRock (spawner.getPoint()));
							object.push_back(new BigRock (spawner.getPoint()));
							object.push_back(new BigRock (spawner.getPoint()));
							object.push_back(new BigRock (spawner.getPoint()));
							object.push_back(new BigRock (spawner.getPoint()));
							
		}
	if(bomb)
		bombSize++;
	else
		bombSize = 0;
	alienShip.advance(ship.getVector());
	if(shield.getIsOn())
	shield.advance(ship.getVector());

	spawner.advance();
	if(ship.getIsDead())
	frame++;
	
	if(alienShip.getIsDead())
	frame2++;

	if(frame2 >= 150)
		{
			
			frame2 = 0;
		
				alienShip.respawn();
		}	
	
	if(frame >= 150 && lives >= 0)
		{
			
			frame = 0;
			if(lives > 0)
			{
				lives--;
				ship.respawn();
				shield.setIsOn(true);
			}
			
		}

	if(ship.getIsDead() == false)
	ship.advance();

	for(int i = 0; i < 9; i++)
	{
			bullet[i].advance();
	}

	for(int i = 0; i < 9; i++)
	{
		if(bullet[i].getIsDead() == false)
		{
			if( 10 > bullet[i].getVector() - ship.getVector())
				ship.setIsDead(true);
			else if( 10 > bullet[i].getVector() - alienShip.getVector())
				{
					if(alienShip.getIsDead())
					hits +=10;
					alienShip.setIsDead(true);
				}
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
			
			if ( 25 > (ship.getVector() -object[i]->getVector()) && object[i]->getType() == 'B')
					 {
							ship.setIsDead(true);
						object.push_back(new MedRock (object[i]->getVector().getPoint()));
						object.push_back(new MedRock (object[i]->getVector().getPoint()));
						object.push_back(new MedRock (object[i]->getVector().getPoint()));
						
						
						 object.erase(object.begin() + i);
						  if( i > 0)
						i--;
						}
			if ( 25 > (alienShip.getVector() -object[i]->getVector()) && object[i]->getType() == 'B')
					 alienShip.setIsDead(true);
					
			if( 25 + shield.getSize() >  shield.getVector()- object[i]->getVector() && object[i]->getType() == 'B' && shield.getIsOn() )
				{
					shield.setIsHit(true);
					object.erase(object.begin() + i); 
						 if( i > 0)
						i--;
						
				}
			if ( 15 > (ship.getVector() -object[i]->getVector()) && object[i]->getType() == 'M')
						{
							ship.setIsDead(true);
						object.push_back(new LittleRock (object[i]->getVector().getPoint()));
						object.push_back(new LittleRock (object[i]->getVector().getPoint()));
						object.push_back(new LittleRock (object[i]->getVector().getPoint()));
						
						
						 object.erase(object.begin() + i);
						  if( i > 0)
						i--;
						}
			if ( 15 > (alienShip.getVector() -object[i]->getVector()) && object[i]->getType() == 'M')
						 alienShip.setIsDead(true);
					
		    if( 15 + shield.getSize()> (shield.getVector() - object[i]->getVector()) && object[i]->getType() == 'M' && shield.getIsOn()  )
				{
					shield.setIsHit(true);
						 object.erase(object.begin() + i); 
						 if( i > 0)
						i--;
				}
			if (  8 > (ship.getVector() -object[i]->getVector()) && object[i]->getType() == 'L')
						 ship.setIsDead(true);
			if (  8 > (alienShip.getVector() -object[i]->getVector()) && object[i]->getType() == 'L')
						 alienShip.setIsDead(true);

		    if( 8 + shield.getSize() > (shield.getVector() - object[i]->getVector()) && object[i]->getType() == 'L' && shield.getIsOn())
				{
					shield.setIsHit(true); 
						 object.erase(object.begin() + i); 
						 if( i > 0)
						i--;
						 
				}

			for(int j = 0; j <  9; j++)
				{
					if(bullet[j].getIsDead() == false)
					{
					
						if (15 > (bullet[j].getVector() - object[i]->getVector()) && object[i]->getType() == 'M' )
						{
						bullet[j].setIsDead(true);
						object.push_back(new LittleRock (object[i]->getVector().getPoint()));
						object.push_back(new LittleRock (object[i]->getVector().getPoint()));
						object.push_back(new LittleRock (object[i]->getVector().getPoint()));
						
						
						 object.erase(object.begin() + i); 
						  if(!(bullet[j].getIsAlien()))
						     hits++;
						  else 
							 bullet[j].setIsAlien(false);
						 if( i > 0)
						i--;
						
					  
						}
					}
					if (14 > (ship.getVector() - object[i]->getVector()) && object[i]->getType() == 'S')
						{
							object[i]->setIsDead(true);
						
							if( i > 0)
							i--;
							shield.setIsOn(true);
							
						}
					if (14 > (ship.getVector() - object[i]->getVector()) && object[i]->getType() == 'Q')
						{
							object[i]->setIsDead(true);
							if( i > 0)
							i--;
							bomb = true;	
							bombVector = ship.getVector();
								
							}
																
						
						
				
				}		
		}
	}
		for (int i = 0; i < object.size(); i++)
		{
			if(object[i]->getIsDead() == false)
			{
			
			for(int j = 0; j < 9; j++)
				{
					if(bullet[j].getIsDead() == false)
					{
					
						if ( 25 > (bullet[j].getVector() - object[i]->getVector())  && object[i]->getType() == 'B')
						{
						bullet[j].setIsDead(true);
						object.push_back(new MedRock (object[i]->getVector().getPoint()));
						object.push_back(new MedRock (object[i]->getVector().getPoint()));
						object.push_back(new MedRock (object[i]->getVector().getPoint()));
				
						
						 object.erase(object.begin() + i);
						 
					if(!(bullet[j].getIsAlien()))
					 hits++;
				    else 
					 bullet[j].setIsAlien(false);
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
			
			for(int j = 0; j < 9; j++)
				{
					if(bullet[j].getIsDead() == false)
					{
					
						if ( 9 > (bullet[j].getVector() - object[i]->getVector()) && object[i]->getType() == 'L')
					{
						bullet[j].setIsDead(true);
					   

						 if(!(bullet[j].getIsAlien()))
						hits++;
						 else 
							 bullet[j].setIsAlien(false);
						object.erase(object.begin() + i);
						 if( i > 0)
						i--;
						 
					} 

					}			
				}		
			}

		}
	
		if(alienShip.getFrames() % 60 == 0 && alienShip.getIsDead() == false)
	     {
		  ammo.push_back(1);
		  bullet[ammo.size() + 1].alienFire(alienShip.getAngle(), alienShip.getPoint());
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
		shield.setStart(false);
		ammo.push_back(1);
	if(ammo.size() <= 8 )
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
      
	    
      for (int j = 0; j <= 8; j++)
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
	drawCircle( ship.getPoint(), bombSize, 10,0);
		for (int i = 0; i < object.size(); i++)
	{
		
			object[i]->draw();
			
	}
		if(ship.getIsDead() == false)
		ship.draw();
	
	for (int i = 0; i< 9; i++)
	{
		if (bullet[i].getIsDead() == false)
		 bullet[i].draw();
			
	}
	spawner.draw();

	if(shield.getIsOn())
		shield.draw();
	score.draw(lives ,hits);

	if(alienShip.getIsDead() == false)
		alienShip.draw();
	if(ship.getIsDead() && lives == 0)
	{
		
		drawText1(gameOver, *text);
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
		angle += 7;
	}
	else if(right)
	{	
		
		angle -= 7;
	}

	// if pressing up and not above max speed
	if(up && speed < 60)
	{
		// the game has begun
		start = true;

		// accelerate speed
		speed += 15;

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
 * SHIP :: CONSTRUCTOR
 ************************************************/
void Ship :: respawn()
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
 *************************************************
 *******************ALIEN*************************
 *************************************************
 ************************************************/

/*************************************************
 * SHIP :: CONSTRUCTOR
 ************************************************/
AlienShip :: AlienShip() 
{
	isDead = false;
	speed = 0;
	randomAngle = 0;
	angle = 0;
   // set the location in the beginning
   vector.getPoint().setX(random(vector.getPoint().getXMin(), vector.getPoint().getXMax()));
   vector.getPoint().setY(random(vector.getPoint().getYMin(), vector.getPoint().getYMax()));
   vector.setDx(0);	
   vector.setDy(0);		

   int frames = 0;
}

/*************************************************
 * SHIP : ADVANCE
 *      Change the points of the ship
 ************************************************/
void AlienShip::advance(Vector ship)
{

	frames++;
	if (frames % 10 == 0)
	randomAngle = random(-10,10);
  
	angle += randomAngle;
	

		// accelerate speed
		speed = 60;

		// set the new x speed and y speed
		vector.setDx(-sin(deg2rad(angle + 90)) * speed / 15);
		vector.setDy( cos(deg2rad(angle + 90)) * speed / 15);

	vector.getPoint().addX(vector.getDx());
	vector.getPoint().addY(vector.getDy());
	
	
	wrap();
}

/*************************************************
 * SHIP : DRAW
 *      Draw the ship
 ************************************************/
void AlienShip::draw()
{
	
	// ship draw
   drawAlienShip(vector.getPoint(), angle);


}


/***************************************************
 * SHIP : Wrap
 *      If you hit the edge of the screen you come out on other side
 **************************************************/
void AlienShip :: wrap()
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
 * SHIP :: CONSTRUCTOR
 ************************************************/
void AlienShip :: respawn()
{
	isDead = false;
	speed = 0;
	angle = 0;
   // set the location in the beginning
	vector.getPoint().setX(random(vector.getPoint().getXMin(), vector.getPoint().getXMax()));
   vector.getPoint().setY(random(vector.getPoint().getYMin(), vector.getPoint().getYMax()));
   vector.setDx(0);	
   vector.setDy(0);	
   
    int frames = 0;
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
   rockSize = 7;
   rotation = 0;
}

/*************************************************
 * ROCK : DRAW
 * Draw the stuff
 ************************************************/
void LittleRock::draw() 
{
   // drawing the bird at each new location.

   drawCircle(vector.getPoint(), rockSize, 4, rotation += rotationSpeed);
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


   rotationSpeed = random(1, 4);


   vector.setDx(random(-4,4));
   vector.setDy(random(-4,4));

      if(vector.getDx() == 0)
   {
	    vector.setDx(random(-4,4));
		vector.setDy(random(-4,4));
   }

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
   rotation = 0;
}

/*************************************************
 * ROCK : DRAW
 * Draw the stuff
 ************************************************/
void BigRock::draw() 
{
   // drawing the bird at each new location.
	
	drawCircle1(vector.getPoint(), rockSize, 7, rotation += rotationSpeed );
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

   rotationSpeed = random(1, 4);

   vector.setDx(random(-4,4));
   vector.setDy(random(-4,4));

   if(vector.getDx() == 0)
   {
	    vector.setDx(random(-4,4));
		vector.setDy(random(-4,4));
   }
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
   rotation = 0;
}

/*************************************************
 * ROCK : DRAW
 * Draw the stuff
 ************************************************/
void MedRock::draw() 
{
   // drawing the bird at each new location.

	drawCircle2(vector.getPoint(), rockSize, 3 , rotation += rotationSpeed);
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

   rotationSpeed = random(1, 4);
   
   vector.setDx(random(-4,4));
   vector.setDy(random(-4,4));

      if(vector.getDx() == 0)
   {
	    vector.setDx(random(-4,4));
		vector.setDy(random(-4,4));
   }
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
 ****************LITTLEROCK***********************
 *************************************************
 ************************************************/

/*************************************************
 * Shield :: CONSTRUCTOR
 *      set dead to true in the beginning so it
 *      does not just appear.
 ************************************************/
Shield :: Shield(Point point)
{
	start.setX(random(-600, 600));
	start.setY(random(-350, 350));
	text = "S";
	frames = 0;
}

/*************************************************
 * ROCK : DRAW
 * Draw the stuff
 ************************************************/
void Shield::draw() 
{
	if(frames > 100)
	{
   // drawing the bird at each new location.
	char * x;
			 x = (char*)text.c_str();

			char * text[256];
			 text[0] = &x[0];
			 circle.setX(vector.getPoint().getX() + 4);
				  circle.setY(vector.getPoint().getY() + 5);
   drawCircle(circle,13,20,0);
   
   drawText(vector.getPoint(), *text);
	}
}

/**************************************************
 *BIRD : ADVANCE
 *************************************************/
void Shield :: advance()
{
	frames++;
	wrap();
   // move the bird across the screen. 
   vector.getPoint().addX(vector.getDx()); 
   vector.getPoint().addY(vector.getDy());

   if (frames % 180 == 0)
   {
	      vector.setDx(random(-4,4));
   vector.setDy(random(-4,4));

      if(vector.getDx() == 0)
   {
	    vector.setDx(random(-2,2));
		vector.setDy(random(-2,2));
   }
	  
   }
   if (frames == 100)
	   isDead = true;
   if (frames == 500)
	   {
		   isDead = false;
		   frames = 0;
	   }
}

/*************************************************
 * BIRD : REGEN
 *      Draw the stuff after the bird has been
 *      killed
 ************************************************/
void Shield::regen()
{
   
  vector.getPoint().setX(start.getX());
  vector.getPoint().setY(start.getY());


   vector.setDx(random(-2,2));
   vector.setDy(random(-2,2));

      if(vector.getDx() == 0)
   {
	    vector.setDx(random(-4,4));
		vector.setDy(random(-4,4));
   }

   // move even or down if the random location is
   // grater than 0
   
 
   
     
}

/**************************************************
 * BIRD : KILL
 *  DIE DIE DIE
 *************************************************/
void Shield :: kill()
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
void Shield :: wrap()
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
 ****************LITTLEROCK***********************
 *************************************************
 ************************************************/

/*************************************************
 * Shield :: CONSTRUCTOR
 *      set dead to true in the beginning so it
 *      does not just appear.
 ************************************************/
Bomb :: Bomb(Point point)
{
	start.setX(random(-600, 600));
	start.setY(random(-350, 350));
	text = "B";
	frames = 0;
}

/*************************************************
 * ROCK : DRAW
 * Draw the stuff
 ************************************************/
void Bomb::draw() 
{
	if(frames > 100)
	{
   // drawing the bird at each new location.
	char * x;
			 x = (char*)text.c_str();

			char * text[256];
			 text[0] = &x[0];
			 circle.setX(vector.getPoint().getX() + 4);
				  circle.setY(vector.getPoint().getY() + 5);
   drawCircle(circle,13,20,0);
   
   drawText(vector.getPoint(), *text);
	}
}

/**************************************************
 *BIRD : ADVANCE
 *************************************************/
void Bomb :: advance()
{
	frames++;
	wrap();
   // move the bird across the screen. 
   vector.getPoint().addX(vector.getDx()); 
   vector.getPoint().addY(vector.getDy());

   if (frames % 180 == 0)
   {
	      vector.setDx(random(-4,4));
   vector.setDy(random(-4,4));

      if(vector.getDx() == 0)
   {
	    vector.setDx(random(-2,2));
		vector.setDy(random(-2,2));
   }
	  
   }
   if (frames == 100)
	   isDead = true;
   if (frames == 500)
	   {
		   isDead = false;
		   frames = 0;
	   }
}

/*************************************************
 * BIRD : REGEN
 *      Draw the stuff after the bird has been
 *      killed
 ************************************************/
void Bomb::regen()
{
   
  vector.getPoint().setX(start.getX());
  vector.getPoint().setY(start.getY());


   vector.setDx(random(-2,2));
   vector.setDy(random(-2,2));

      if(vector.getDx() == 0)
   {
	    vector.setDx(random(-4,4));
		vector.setDy(random(-4,4));
   }

   // move even or down if the random location is
   // grater than 0
   
 
   
     
}

/**************************************************
 * BIRD : KILL
 *  DIE DIE DIE
 *************************************************/
void Bomb :: kill()
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
void Bomb :: wrap()
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
	isAlien = false;
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
   if (frames == 60)
   {
	   
		  isDead = true;
   }

   wrap();
}


/***********************************************
 * BULLET : FIRE
 *      Set the speed of the bullet and which
 *      angle it is supposed to go
 **********************************************/
void Bullet::fire(int angle, Point shipPoint)
{
   // set the speed of the bullet
	int bulletSpeed = 15;
   
   vector.getPoint().setX(shipPoint.getX());   
   vector.getPoint().setY(shipPoint.getY());
    
   vector.setDx(-sin (deg2rad(angle + 90)) * bulletSpeed);
   vector.setDy(cos(deg2rad(angle + 90)) * bulletSpeed);

   // set the direction of the bullet
    isDead = false;  
}

/***********************************************
 * BULLET : FIRE
 *      Set the speed of the bullet and which
 *      angle it is supposed to go
 **********************************************/
void Bullet::alienFire(int angle, Point shipPoint)
{
   // set the speed of the bullet
	int bulletSpeed = 15;
   
   vector.getPoint().setX(shipPoint.getX());   
   vector.getPoint().setY(shipPoint.getY());
    
   vector.setDx(-sin (deg2rad(angle + 90)) * bulletSpeed);
   vector.setDy(cos(deg2rad(angle + 90)) * bulletSpeed);

   // set the direction of the bullet
    isDead = false;
	isAlien = true;
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

/***************************************************
 * LITTLEROCK : Wrap
 *      If you hit the edge of the screen you come out on other side
 **************************************************/
void Bullet :: wrap()
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


/**********************************************
 **********************************************
 *****************SPAWNER**********************
 **********************************************
 *********************************************/

/***********************************************
 * SPAWNER : CONSTRUCTOR  
 **********************************************/
Spawner :: Spawner()
{
	isDead = true;
	point.setX(random(-200, 200));
	point.setY(random(-200, 200));
	size = 1;
	frames = 0;
	rotation = 0;
	
}

/***********************************************
 * SPAWNER : DRAW   
 **********************************************/
void Spawner :: draw()
{
	drawCircle3(point, size, 4, rotation);
	
}

/***********************************************
 * SPAWNER : FIRE
 *      Set the speed of the bullet and which
 *      angle it is supposed to go
 **********************************************/
void Spawner :: advance()
{
	

	frames++;
	if (isDead)
		{
			respawn = false;
			frames = 0;
			size = 0;
			point.setX(random(-200, 200));
			point.setY(random(-200, 200));
			isDead = false;
			rotation =0;
		}
	
	if (size == 90)
		{
			if(frames > 220)
				frames = 0;
			warn = "!";
			char * x;
			 x = (char*)warn.c_str();

			char * text[256];
			 text[0] = &x[0];
			if(!(frames % 20 == 0))
			{
				drawText(point,  *text);
				warn = "Worm Hole Opening!";
				char * x;
			 x = (char*)warn.c_str();

			char * text[256];
			 text[0] = &x[0];
			 Point temp;
			 temp.setX(-60);
			 temp.setY(0);
			 drawText(temp,  *text);
			}
			rotation += 2;
			if (frames > 100)
				isDead = true;
			else if (frames >= 80)
				if(frames % 10 == 0)
					{
						respawn = true;
						
					}
				else
					respawn = false;
		}
	else if (frames % 8 == 0)
			size++;
	
	
}



/*************************************************
 *************************************************
 *******************PowerUp Shield****************
 *************************************************
 ************************************************/



/*************************************************
 * SHIP :: CONSTRUCTOR
 ************************************************/
Powerup::Powerup() 
{
	vector.setDx(1);
	vector.setDy(1);
	vector.getPoint().setX(-1000);
	vector.getPoint().setY(-1000);

	isOn = false;
	size = 0;
	isHit = false;
	start = true;
	isMaxSize = false;
}

/*************************************************
 * SHIP : ADVANCE
 *      Change the points of the ship
 ************************************************/
void Powerup::advance(Vector shipVector)
{
	// frame count
	vector = shipVector;
	vector.setPoint(shipVector.getPoint());
 


	if(isOn && size <= 15  && !(isMaxSize))
		{
			size++;
			
		}

	if(size >= 15)
		isMaxSize = true;

	if(isOn && size <= 10 && isMaxSize)
	{
		isMaxSize = false;
		isOn = false;
		size = 0;
	}

	
	if(isHit)
	{
		size -= 1;
		isHit = false;
	}
	

}

/*************************************************
 * SHIP : DRAW
 *      Draw the ship
 ************************************************/
void Powerup::draw()
{
	if(isOn)
	drawCircle(vector.getPoint(), size, 25, 0);
}

/**********************************************
 **********************************************
 *****************SCORE***********************
 **********************************************
 *********************************************/

/***********************************************
 * SPAWNER : CONSTRUCTOR  
 **********************************************/
Score :: Score()
{
	topLeft.setX(-595);
	topLeft.setY(345);

	topRight.setX(595);
	topRight.setY(345);
	live = "Lives";
	hit = "Score";
}

/*************************************************
 * SHIP : DRAW
 *      Draw the ship
 ************************************************/
void Score::draw(int lives, int hits)
{
	char * text[256];
	char * x;
	topLeft.setX(-595);
	topLeft.setY(340);
	
	 x = (char*)live.c_str();

			
	 text[0] = &x[0];

	drawText(topLeft, *text);

	topLeft.setX(-587);
	topLeft.setY(335);
	drawNumber(topLeft, lives);	

	topRight.setX(560);
	topRight.setY(340);
	
	 x = (char*)hit.c_str();

			
	 text[0] = &x[0];

	drawText(topRight, *text);
	
	
	if(hits >= 100)
		topRight.setX(560);
	else
		topRight.setX(570);
	topRight.setY(335);
	drawNumber(topRight, hits);	


}


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



