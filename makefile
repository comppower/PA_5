# Make file for PA_5
# WRITTEN BY: Kent Libby 10/10/17
# run make all to make all of the files and the doxygen stuff


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
	rm -rf *.o Sim
	rm -rf ./latex ./html

docs:
	doxygen