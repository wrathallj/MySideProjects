###############################################################
# Program:
#     Project 02, Skeet
#     Brother Helfrich, CS165
# Author:
#     Jared Wrathall
#     Greg Harston
# Summary:
#     Birds will randomly come out from the left and you kill 
#     them with bullets.
# EXTRA CREDIT:
#     Bird increases size if you miss and decreases size if you 
#     hit.
#     By hitting the right arrow there is a spread shot of all 
#     five bullets
#
#     Estimated:  40.0 hrs
#     Actual:     60.0 hrs
#       Was the minimum distance and implementing it.
###############################################################

###############################################################
# Programs:
#   Skeet: 
###############################################################
skeet  : uiDraw.o uiInteract.o game.o skeet.o point.o
	g++ -o skeet game.o skeet.o uiInteract.o uiDraw.o point.o -lglut -lGLU

###############################################################
# Individual files
#    uiDraw.o      Draw polygons on the screen and do all OpenGL graphics
#    uiInteract.o  Handles input events
#    point.o       The position on the screen
###############################################################
uiInteract.o : uiInteract.cpp uiInteract.h point.h
	g++ -c uiInteract.cpp

uiDraw.o : uiDraw.cpp uiDraw.h point.h
	g++ -c uiDraw.cpp

point.o : point.cpp point.h
	g++ -c point.cpp

game.o  : game.cpp uiDraw.h uiInteract.h point.h skeet.h
	g++ -c game.cpp

skeet.o :skeet.cpp uiDraw.h uiInteract.h point.h skeet.h game.cpp
	g++ -c skeet.cpp 

###############################################################
# General rules
###############################################################
clean :
	rm uiTest pong *.o *.tar

all :  uiTest pong

