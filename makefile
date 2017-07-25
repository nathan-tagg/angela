###############################################################
# Program: Angela
# Author: Nathan Tagg
###############################################################

OS := $(shell uname)
ifeq ($(OS),Darwin)
	LFLAGS = -framework GLUT -framework OpenGL
else
	LFLAGS = -lglut -lGLU -lGL
endif

###############################################################
# Build the main game
###############################################################
a.out: driver.o game.o uiInteract.o uiDraw.o point.o velocity.o
	g++ driver.o game.o uiInteract.o uiDraw.o point.o velocity.o $(LFLAGS)

driver.o: game.h uiInteract.h driver.cpp
	g++ -c driver.cpp

game.o: game.cpp game.h 
	g++ -c game.cpp

uiInteract.o: uiInteract.cpp uiInteract.h point.h
	g++ -c uiInteract.cpp

uiDraw.o: uiDraw.cpp uiDraw.h point.h
	g++ -c uiDraw.cpp

point.o: point.cpp point.h
	g++ -c point.cpp

velocity.o: velocity.cpp velocity.h
	g++ -c velocity.cpp

###############################################################
# General rules
###############################################################
clean:
	rm a.out *.o
