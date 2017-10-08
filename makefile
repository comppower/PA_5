# Make file for Lab Exercise 2
# WRITTEN BY: Michael Main (main@colorado.edu), Jan 11, 1997
# MODIFIED BY:  Glynis Hamel 3/2/99
# MODIFIED BY:  Glynis Hamel 3/21/02
# MODIFIED BY:  Glynis Hamel 11/14/05 Converted from C++ to C
# MODIFIED BY:  Hugh Lauer 04/06/09 Substituted $(CFLAGS) for -g
# MODIFIED BY:	Hugh Lauer 08/18/13 Added -Wall and -m32 to CFLAGS
#
# This makefile is used as follows to regenerate files for the sinewave program:
#   make intarray.o   --  Regenerates intarray.o by compiling
#   make sinewave.o   --  Regenerates sinewave.o by compiling
#   make sinewave     --  Regenerates the executable sinewave file by compiling
#   make              --  Same as "make sinewave"
#

CFLAGS = -g

all: Sim docs

Sim: Sim.o Organism.o
	g++ $(CFLAGS) -Wall Ant.o DoodleBug.o Board.o Sim.o Organism.o -o Sim 

Sim.o: Board.o Organism.h Sim.cpp
	g++ $(CFLAGS) -Wall -c Sim.cpp

Board.o: DoodleBug.o Ant.o Board.h Board.cpp
	g++ $(CFLAGS) -Wall -c Board.cpp

DoodleBug.o: Organism.o DoodleBug.h DoodleBug.cpp
	g++ $(CFLAGS) -Wall -c DoodleBug.cpp 

Ant.o: Organism.o Ant.h Ant.cpp
	g++ $(CFLAGS) -Wall -c Ant.cpp
	
Organism.o: Organism.h Organism.cpp
	g++ $(CFLAGS) -Wall -c Organism.cpp

clean:
	rm -f Organism.o Sim.o Sim
	rm -rf ./latex ./html

docs:
	doxygen