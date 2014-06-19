/***********************************************************************
 * Program:
 *    Project  01, Procedural Chess
 *    Brother Helfrich, CS165
 * Author:
 *    Jared Wrathall
 * Summary: 
 *    
 *    This program will create the game chess.  This game will have no
 *    rules though.  Players will insert their moves by putting in 
 *    smith notation.
 *    
 *
 *    Estimated:  25.0 hrs   
 *    Actual:     4.0 hrs
 *      
 ************************************************************************/

#include <string>      // string class used throughout
#include <cassert>     // for asserts
#include <iostream>    // cin and cout
#include <stdio.h>
#include <ctype.h>
using namespace std;

#define NO_PIECE ' '   // There is no piece on this location of the board
#define INVALID 127    // invalid row or column value
#define BLACK 0 
#define RED 12 // 4 is dark red 
#define WHITE 15
/********************************************
 * COORD
 * A single r,c coordinate
 *******************************************/
struct Coord
{
   char r;   // row, from 0..7
   char c;   // col, from 0..7
};

/*********************************************
 * MOVE
 * A single move, including the textual description
 * and what it breaks down to
 ********************************************/
struct Move
{
   string text;           // textual description of the move
   char   piece;          // unknown piece
   bool   capture;        // did a capture happen this move?
   Coord  source;         // where the move originated from
   Coord  dest;           // where the move finished
   bool   enpassant;      // Enpassant pawn capture
   bool   castleK;        // kingside castle
   bool   castleQ;        // queenside castle
   bool   promote;        // promote to move.piece
};


/**************************************************************
 * MOVE PARSE
 * Accept the user's input in algebra notation and determine
 * if it is valid
 *    INPUT  move.text    The Smith Notation of the move
 *           board[][]    The current state of the board
 *    OUTPUT move.*       All the fields of the move filled in
 *           EXCEPTION    String of error message
 *************************************************************/
void moveParse(Move & move, char board[][8]) throw(string);

/**************************************************************
 * DISPLAY
 * Accept the user's input in algebra notation and determine
 * Displays the board
 *     INPUT Board[][]    The current state of the board
 *************************************************************/
void display(char board[][8]);

/**************************************************************
 * SET BOARD
 * 
 * 
 * 
 *************************************************************/
void setBoard(char board[][8]);

/**************************************************************
 * MOVE EXECUTE
 * 
 * 
 * 
 *************************************************************/
void moveExecute(char board[][8], Move move);

/**************************************************************
 * INTERACT
 * 
 * 
 * 
 *************************************************************/
bool interact(char board[][8], Move move, bool & test);

/**************************************************************
 * READ
 * 
 * 
 * 
 *************************************************************/
void read();

/**************************************************************
 * TEST DISPLAY
 * Accept the user's input in algebra notation and determine
 * Displays the board in test mode
 *     INPUT Board[][]    The current state of the board
 *************************************************************/
void testDisplay(char board [][8]);

void changeColor(WORD foreground, WORD background);
/**********************************************************************
 * Add text here to describe what the function "main" does. Also don't forget
 * to fill this out with meaningful text or YOU WILL LOSE POINTS.
 ***********************************************************************/
int main()
{
   bool test = false;
   bool isGameOver = false;
   bool isWhiteTurn = true;
   char board[8][8];

   // setup the board
   setBoard(board);

   // display board for first time
   display(board);

   // looping game until isGameOver is false
   for(;;)
   {
      Move move;

      // prompt switchs between white and black
      if (isWhiteTurn == true)
      {
         cout << "(White):";
         cin  >> move.text;
         isWhiteTurn = false;
      }
      else
      {      
         cout << "(Black):";
         cin  >> move.text;
         isWhiteTurn = true;
      }

      // goes through the list of options and determins if end of game
      isGameOver = interact(board, move, test);         

      // end the game
      if (isGameOver == true)
         return 0;

      // what board to display
      if (test != true)
         display(board);
      else
      {
         cout << "test\n";
         testDisplay(board);
      }
   }  
   return 0;
}

/************************************************ * Change Color * 
Set the foreground and background color
***********************************************/ 
void changeColor(WORD foreground, WORD background)
{ 
	WORD color = _rotl(background, 4) | foreground;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}
/**********************************************************************
 * Add text here to describe what the function "main" does. Also don't forget
 * to fill this out with meaningful text or YOU WILL LOSE POINTS.
 ***********************************************************************/
void read()
{
   // well this is a lie right now
   cout << "File Read";
}

/**********************************************************************
 * Add text here to describe what the function "main" does. Also don't forget
 * to fill this out with meaningful text or YOU WILL LOSE POINTS.
 ***********************************************************************/
void showOptions()
{
   // here are the options
   cout << "Options:"  << endl;
   cout << "?       " << "Display these options\n";
   cout << "b2b4    " << "Specify a move using the Smith Notation\n";
   cout << "read    " << "Read a saved game from a file\n";
   cout << "test    " << "Simple display for test purposes\n";
   cout << "quit    " << "Leave the game. You will be prompted to save\n";
   
}

/**********************************************************************
 * Add text here to describe what the function "main" does. Also don't forget
 * to fill this out with meaningful text or YOU WILL LOSE POINTS.
 ***********************************************************************/
bool interact(char board[][8], Move move, bool & test)
{
   int option;

   // changes the prompt to a int so it can be used in switch
   if (move.text == "?")
      option = 1;
   else if (move.text == "read")
      option = 2;
   else if (move.text == "test")
      option = 3;
   else if (move.text == "quit")
      option = 4;
   else
      option = 100;

   // goes through all options
   switch (option)
   {
      case 1:
         showOptions();
         cout << endl;
         break;
      case 2:
         read();
         cout << endl;
         break;
      case 3:
         test = true;
         break;
      case 4:
         return true;
         break;
      default:
         try
         {
            // figure out what this move is
            moveParse(move, board);
         }
         catch (string s)
         {
            cout << "Error message: " << s << endl;
         
         }
         // time to move that piece
         moveExecute(board, move);
   }
      
            
   return false;            
}

/**********************************************************************
 * Add text here to describe what the function "main" does. Also don't forget
 * to fill this out with meaningful text or YOU WILL LOSE POINTS.
 ***********************************************************************/
void setBoard(char board[][8])
{

   char originalBoard[8][8] =
      {
         { 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r' },
         { 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p' },
         { NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
           NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE },
         { NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
           NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE },
         { NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
           NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE },
         { NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
           NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE },
         { 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P' },
         { 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R' }
      };

   // copy the original board setup into current board
   for (int r = 0; r <= 7; r++)
      for (int c = 0; c <= 7; c++)
         board[r][c] = originalBoard[r][c];

}

/**********************************************************************
 * Add text here to describe what the function "main" does. Also don't forget
 * to fill this out with meaningful text or YOU WILL LOSE POINTS.
 ***********************************************************************/
void moveExecute(char board[][8], Move move)
{
   move.source.r = 7 - move.source.r;
   move.dest.r = 7 - move.dest.r;
  
   // if castle move
   if (move.castleK)
   {
      board[move.dest.r][7] = ' ';
      board[move.dest.r][6] = 'K';
      board[move.dest.r][5] = 'R';
      board[move.dest.r][4] = ' ';
   }
   if (move.castleQ)
   {
      board[move.dest.r][0] = ' ';
      board[move.dest.r][1] = ' ';
      board[move.dest.r][2] = 'K';
      board[move.dest.r][3] = 'R';
      board[move.dest.r][4] = ' ';
   }
   
   board[move.dest.r][move.dest.c] =
      board[move.source.r][move.source.c];
   board[move.source.r][move.source.c] = ' ';
   
         
}


/**********************************************************************
 * Add text here to describe what the function "main" does. Also don't forget
 * to fill this out with meaningful text or YOU WILL LOSE POINTS.
 ***********************************************************************/
void write()
{
}

/**************************************************************
 * MOVE PARSE
 * Accept the user's input in algebra notation and determine
 * if it is valid
 *    INPUT  move.text    The Smith Notation of the move
 *           board[][]    The current state of the board
 *    OUTPUT move.*       All the fields of the move filled in
 *           EXCEPTION    String of error message
 *************************************************************/
void moveParse(Move & move, char board[][8]) throw(string)
{
   // initialize the move.  What we know up to this point is... nothing!
   move.piece     = NO_PIECE;
   move.capture   = false;
   move.source.r  = INVALID;
   move.source.c  = INVALID;
   move.dest.r    = INVALID;
   move.dest.c    = INVALID;
   move.enpassant = false;
   move.castleK   = false;
   move.castleQ   = false;
   move.promote   = false;

   //
   // from square
   //

   // column: a-h
   if (move.text[0] < 'a' || move.text[0] > 'h')
      throw string("Invalid format of source coordinates");
   move.source.c = move.text[0] - 'a';
   assert(move.source.c >= 0 && move.source.c <= 7);

   // row: 1-8
   if (move.text[1] < '1' || move.text[1] > '8')
      throw string("Invalid format of source coordinates");
   move.source.r = move.text[1] - '1';
   assert(move.source.r >= 0 && move.source.r <= 7);

   // if there is nothing to move, we have an error
   move.piece = tolower(board[move.source.r][move.source.c]);
   if (move.piece == NO_PIECE)
      throw string("No piece in the source coordinates position");
   
   //
   // to square
   //

   // column: a-h
   if (move.text[2] < 'a' || move.text[2] > 'h')
      throw string("Invalid format of destination coordinates");
   move.dest.c = move.text[2] - 'a';
   assert(move.dest.c >= 0 && move.dest.c <= 7);

   // row: 1-8
   if (move.text[3] < '1' || move.text[3] > '8')
      throw string("Invalid format of destination coordinates");
   move.dest.r = move.text[3] - '1';
   assert(move.dest.r >= 0 && move.dest.r <= 7);

   // capture if there is something there
   if (board[move.dest.r][move.dest.c] != NO_PIECE)
      move.capture = true;
   
   //
   // capture and promotion
   //

   for (int i = 4; i < move.text.size(); i++)
   {
      switch(move.text[i])
      {
         case 'p':   // capture a pawn
         case 'n':   // capture a knight
         case 'b':   // capture a bishop
         case 'r':   // capture a rook
         case 'q':   // capture a queen
         case 'k':   // !! you can't capture a king you silly!
            move.capture = true;
         break;

         case 'c':  // short castling or kings castle
            move.castleK = true;
            break;
         case 'C':  // long castling or queen castle
            move.castleQ = true;
            break;
         case 'E':  // En-passant
            move.enpassant = true;
            break;

         case 'N':  // Promote to knight
         case 'B':  // Promote to Bishop
         case 'R':  // Promote to Rook
         case 'Q':  // Promote to Queen
            move.piece = tolower(move.text[i]);
         move.promote = true;
         break;

         default:
            // unknown piece
            throw string("Unknown promotion piece specification");
      }
   }

   // if we made it this far, we are successful
   return;
}

/**************************************************************
 * TEST DISPLAY
 * Accept the user's input in algebra notation and determine
 * Displays the board for testbed
 *     INPUT Board[][]    The current state of the board
 *************************************************************/
void testDisplay(char board [][8])
{
   cout << " abcdefgh" << endl;
   for (int r = 0; r <= 7; r++)
   {
      cout << 8 - r;
      for (int c = 0; c <=7; c++)
      {
         // add row to column determine if even or odd
         if (((c + r) % 2) == 0)
         {
            if (isupper(board[r][c]))
            {
               // black pawns turn lowercase
               if (board[r][c] == 'P')
                  board[r][c] = 'p';
               
               //  white square, black piece
               cout << board[r][c];

               // revert piece
               if (board[r][c] == 'p')
                  board[r][c] = 'P';
            }
            else
            {
               // white pawns stay lowercase
               if (board[r][c] == 'p')
                  ;
               else
                  board[r][c] = (char)toupper(board[r][c]);
               
               //  white square, white piece
               cout <<  board[r][c];

               //revert piece  
               board[r][c] = (char)tolower(board[r][c]);
            }
         }
            
         else
         {
            if (isupper(board[r][c]))
            {
               // black pawns turn lowercase
               if (board[r][c] == 'P')
                  board[r][c] = 'p';
               
               // black square, black piece      
               cout << board[r][c] ;
               
               // revert piece
               if (board[r][c] == 'p')
                  board[r][c] = 'P';
            }
            else
            {
               // white pawns stay lower case
               if (board[r][c] == 'p')
                  ;
               else
                  board [r][c] = (char)toupper(board[r][c]);
               
               // black square, white piece
               cout <<  board[r][c] ;

               //revert piece
               board[r][c] = (char)tolower(board[r][c]);
            } 
            
         }
         if (c == 7)
            cout << endl;
      }
   }
}

/**************************************************************
 * DISPLAY
 * Accept the user's input in algebra notation and determine
 * Displays the board
 *     INPUT Board[][]    The current state of the board
 *************************************************************/
void display(char board [][8])
{
   cout << "  a  b  c  d  e  f  g  h" << endl;
   for (int r = 0; r <= 7; r++)
   {
      cout << 8 - r;
      for (int c = 0; c <=7; c++)
      {
         // add row to column determine if even or odd
         if (((c + r) % 2) == 0)
         {
            if (isupper(board[r][c]))
            {
               // black pawns turn lowercase
               if (board[r][c] == 'P')
                  board[r][c] = 'p';
               
			   changeColor(WHITE, BLACK)
               //  white square, black piece
               cout << " " << board[r][c] << " ";

               // revert piece
               if (board[r][c] == 'p')
                  board[r][c] = 'P';
            }
            else
            {
               // white pawns stay lowercase
               if (board[r][c] == 'p')
                  ;
               else
                  board[r][c] = (char)toupper(board[r][c]);
               
               //  white square, white piece
               cout << "\E[31;47m" << " " << board[r][c] << " " << "\E[0m";

               //revert piece  
               board[r][c] = (char)tolower(board[r][c]);
            }
         }
            
         else
         {
            if (isupper(board[r][c]))
            {
               // black pawns turn lowercase
               if (board[r][c] == 'P')
                  board[r][c] = 'p';
               
               // black square, black piece      
               cout << "\E[30;41m" << " " << board[r][c] << " " << "\E[0m";
               
               // revert piece
               if (board[r][c] == 'p')
                  board[r][c] = 'P';
            }
            else
            {
               // white pawns stay lower case
               if (board[r][c] == 'p')
                  ;
               else
                  board [r][c] = (char)toupper(board[r][c]);
               
               // black square, white piece
               cout << "\E[37;41m" << " " << board[r][c] << " " << "\E[0m";

               //revert piece
               board[r][c] = (char)tolower(board[r][c]);
            } 
            
         }
         if (c == 7)
            cout << endl;
      }
   }
}

