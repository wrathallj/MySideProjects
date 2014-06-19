/***********************************************************************
* Program:
*    Project 2 Header, Skeet
*    Jared Wrathall, CS165
* Author:
*    JARED WRATHALL
************************************************************************/

#include <string>
#include <iostream>
#include <cassert>
#include <stdlib.h>
#include "uiInteract.h"  // interface with OpenGL   
#include "point.h"       // the ball has a position
#include "uiDraw.h"      // all the draw primitives exist here
#include <vector>
#include <math.h>
#include <cmath>
#include <queue>
#define _USE_MATH_DEFINES

using namespace std;


/****************************************
 * VECTOR
 *  direction and speed of objects.
 ***************************************/
class Vector
{
  public:
   Point & getPoint() { return point; }; // getter for the point
   float getDx() { return dx; };         // get the x speed
   float getDy() { return dy; };         // get the y speed
   void setDx(float dx);                 // use to set the x speed
   void setDy(float dy); 
   void setPoint(Point point) {this->point = point;}// use to set the y speed
   float getMag() { return sqrt(dx * dx + dy * dy); };
   float operator - (Vector & rhs);      // figures out the min distance 
   Vector operator + (Vector & rhs);     // adds the speeds together
   Vector & operator += (float delta);   // adds to the speed by delta
   Vector & operator ++ ();              // adds to the speed by one
   Vector  operator ++(int postFix);     // adds afterwards by one
   bool operator == (const Vector & rhs) const; // checks to see if they equal
   Vector & operator = (Vector & rhs);   // sets to equal

  protected:
   Point point;                          // holds the x and y coordinates
   float dx;                             // speed going horizontal
   float dy;                             // speed going verticle

};

/****************************************
 * OBJECTS CLASS
 *  
 ***************************************/
class Objects
{
 public:
	 Objects() {isDead = true; }                               // bird constructor 
	virtual void draw() = 0;
	virtual void advance() = 0;                     // moves the bird across the screen
	virtual void regen() = 0;                         // makes the bird spawn                         // puts the bird on screen
	virtual void kill() = 0;   
	virtual void wrap() = 0;
	virtual char getType() = 0;
	// bye bye birdy
	 // set the bird size
	 bool getIsDead() { return isDead; };  // gets if bird is dead
	 void setIsDead(bool isDead) { this->isDead = isDead; }; // hey I hit that one
	 Vector getVector() { return vector; }; // get the speed and points
	



protected:
	 bool isDead; 
	 Vector vector;                        // the speed is stored in here
};



/****************************************
 * SHIP CLASS
 *  
 ***************************************/
class Ship 

{
public:
	Ship() ;                         // rifle constructor
	void move(int up, int left, int right);	// moves the rifle up and down
	void draw() ;                          // puts the rifle on screen
	int getAngle() { return angle; };     // getter for angle
	Point getPoint() {return vector.getPoint();};
	void setAngle(int angle) {this->angle = angle;};
	Vector getVector() { return vector; };
	void advance();
	void wrap();
	bool getIsDead() { return isDead; };  // is the bullet gone?
    void setIsDead(bool isDead) { this->isDead = isDead; };  // sets bullet
	void respawn();
private:
	float speed;
	int angle;
    bool start;
    int frames;
    Vector vector;
    Vector back;
    Vector back2;
	bool isDead;
	

};

/****************************************
 * SHIP CLASS
 *  
 ***************************************/
class AlienShip 

{
public:
	AlienShip() ;                         // rifle constructor
	void draw() ;                          // puts the rifle on screen
	int getAngle() { return angle; };     // getter for angle
	Point getPoint() {return vector.getPoint();};
	void setAngle(int angle) {this->angle = angle;};
	void setFrames(int frames) {this->frames = frames;};
	int getFrames(){return frames;};
	Vector getVector() { return vector; };
	void advance(Vector ship);
	void wrap();
	bool getIsDead() { return isDead; };  // is the bullet gone?
    void setIsDead(bool isDead) { this->isDead = isDead; };  // sets bullet
	void respawn();
private:
	float speed;
	int randomAngle;
	int angle;
    int frames;
    Vector vector;
  	bool isDead;

};

/****************************************
 * Spawner CLASS
 *  
 ***************************************/
class Spawner 

{
public:
	Spawner() ;                         // rifle constructor
	void draw() ;                          // puts the rifle on screen
	Point getPoint() {return point;};
	void advance();
	bool getRespawn() { return respawn; };
	bool getIsDead() { return isDead; };  // is the bullet gone?
    void setIsDead(bool isDead) { this->isDead = isDead; };  // sets bullet
private:
	Point point;
	int size;
	bool isDead;
	int frames;
	int rotation;
	string warn;
	bool respawn;

};

/****************************************
 * Bird
 *  Create the bird, draw, and move it.
 *  Stores the size of the bird and whether
 *  it is dead or not.
 ***************************************/
class LittleRock : public Objects
{
 public:
	 LittleRock(Point point);   
	 virtual void draw();
	 virtual void advance();                     // moves the bird across the screen
	 virtual void regen() ;                         // makes the bird spawn                         // puts the bird on screen
	 virtual void kill();  
	 virtual void wrap();
	 virtual char getType() {return 'L';};	

   // overloaded operators
	 LittleRock operator ++(int postFix);
	 LittleRock & operator +=(float delta);
	 LittleRock operator --(int postFix);
	 LittleRock & operator -=(float delta);
   
private:
	Point start;                   // does it have a pulse?
	int rockSize;                         // size of the bird?
   int rotationSpeed;
   int rotation;
};

/****************************************
 * Bird
 *  Create the bird, draw, and move it.
 *  Stores the size of the bird and whether
 *  it is dead or not.
 ***************************************/
class MedRock : public Objects
{
 public:
	 MedRock(Point point);   
	 virtual void draw();
	 virtual void advance();                     // moves the bird across the screen
	 virtual void regen() ;                         // makes the bird spawn                         // puts the bird on screen
	 virtual void kill();  
	 virtual void wrap();
	 virtual char getType() {return 'M';};

   // overloaded operators
	 MedRock operator ++(int postFix);
	 MedRock & operator +=(float delta);
	 MedRock operator --(int postFix);
	 MedRock & operator -=(float delta);
   
private:
	Point start;                     // does it have a pulse?
	int rockSize;                         // size of the bird?
	int rotationSpeed;
	int rotation;
   
};



/****************************************
 * Bird
 *  Create the bird, draw, and move it.
 *  Stores the size of the bird and whether
 *  it is dead or not.
 ***************************************/
class BigRock : public Objects
{
 public:
	 BigRock(Point point);   
	 virtual void draw();
	 virtual void advance();                     // moves the bird across the screen
	 virtual void regen() ;                         // makes the bird spawn                         // puts the bird on screen
	 virtual void kill();  
	 virtual void wrap();
	 virtual char getType() {return 'B';};

   // overloaded operators
	 BigRock operator ++(int postFix);
	 BigRock & operator +=(float delta);
	 BigRock operator --(int postFix);
	 BigRock & operator -=(float delta);
   
private:
	Point start;                     // does it have a pulse?
	int rockSize;                         // size of the bird?
	int rotationSpeed;
	int rotation;
   
};

/****************************************
 * Bird
 *  Create the bird, draw, and move it.
 *  Stores the size of the bird and whether
 *  it is dead or not.
 ***************************************/
class Shield : public Objects
{
 public:
	 Shield(Point point);   
	 virtual void draw();
	 virtual void advance();                     // moves the bird across the screen
	 virtual void regen() ;                         // makes the bird spawn                         // puts the bird on screen
	 virtual void kill();  
	 virtual void wrap();
	 virtual char getType() {return 'S';};


private:
	Point start;                     // does it have a pulse?
	string text;                         // size of the bird?
	int frames;
	Point circle;

   
};

/****************************************
 * Bird
 *  Create the bird, draw, and move it.
 *  Stores the size of the bird and whether
 *  it is dead or not.
 ***************************************/
class Bomb : public Objects
{
 public:
	 Bomb(Point point);   
	 virtual void draw();
	 virtual void advance();                     // moves the bird across the screen
	 virtual void regen() ;                         // makes the bird spawn                         // puts the bird on screen
	 virtual void kill();  
	 virtual void wrap();
	 virtual char getType() {return 'Q';};


private:
	Point start;                     // does it have a pulse?
	string text;                         // size of the bird?
	int frames;
	Point circle;

   
};


/****************************************
 * BULLET
 *  Create the bullet, draw, move it,
 *  and kill it.
 *  
 ***************************************/
class Bullet
{
  public:
   Bullet();                             // bullet constructor
   void draw();                          // puts bullets on board
   void advance();                       // moves the bullets
   void fire(int angle, Point shipPoint);                 // fires the bullet
   bool getIsDead() { return isDead; };  // is the bullet gone?
   void setIsDead(bool isDead) { this->isDead = isDead; };// sets bullet
   void setIsAlien(bool isAlien) { this->isAlien = isAlien; };
   bool getIsAlien() { return isAlien; };  // is the bullet gone?
   void setFrames(int frames) { this->frames = frames; };
   void kill();                          // removes bullet
   Vector & getVector() { return vector; } // getter for vector
   void alienFire(int angle, Point shipPoint);
   void wrap();

  private:
   Vector vector;                         // contains the speed
   bool isDead;                           // is it in the screen?  
   int frames;
   bool isAlien;
};


/****************************************
 * BULLET
 *  Create the bullet, draw, move it,
 *  and kill it.
 *  
 ***************************************/
class Powerup
{
  public:
   Powerup();                             // bullet constructor
   void draw();                          // puts bullets on board
   void advance(Vector shipVector);  
   bool getIsHit() { return isHit; };  // is the bullet gone?
   void setIsHit(bool isHit) { this->isHit = isHit; };  // sets bullet// moves the bullets
   bool getIsOn() { return isOn; };  // is the bullet gone?
   void setIsOn(bool isOn) { this->isOn = isOn; };  // sets bullet// moves the bullets
   void setSize(float size) { this->size = size; };  // sets bullet
   float getSize() { return size; };  // is the bullet gone?
   void setStart(bool start) { this->start = start; };
   bool getStart() { return start; };  // is the bullet gone?
   Vector & getVector() { return vector; } // getter for vector
  

  private:
   Vector vector;                         // contains the speed
   bool isOn;                           // is it in the screen?  
   float size;
   bool isHit;
   bool start;
   bool isMaxSize;
};

class Score
{
  public:
   Score();                             // bullet constructor
   void draw(int lives, int hits);                          // puts bullets on board
   
private:
Point topLeft;
Point topRight;
string live;
string hit;
};

/****************************************
 * SKEET
 *  Main skeet class
 ***************************************/

class Asteroid
{
  public: 
   Asteroid();                             // skeet constructor
   void draw();                           // puts all objects on screen
   void interact(const Interface *pUI);   // handles the user interaction
   void advance();                        // moves all objects on screen 
  
   
  private:
	 vector <Objects*> object;
	 Ship ship;
	 vector <int> ammo;                      // the skeet
	 Bullet bullet[10];                      // the bullets   
	 Score score;
	 Spawner spawner;
	 Powerup shield;
	 AlienShip alienShip;
	 Point gameOver;
	 string over;
	 char * text[256];
	 int lives;
	  int frame;
	  int hits;
	  int frame2;
	  bool bomb;
	  int bombSize;
	  Vector bombVector;
	 
};




