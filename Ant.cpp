/*
 * Ant.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: klibby
 */
#include "Ant.h"
#include "Board.h"
#include <stdlib.h>
/**
 * Constructor for Ant, calls the constructor for Organism
 * @param initLoc the Location to create it at
 */
Ant::Ant(Location initLoc):Organism(initLoc){
	hasMoved=true;
	curLoc=initLoc;
	moveCount=0;
}
/**
 * this info is pulled by the program to move it on the
 * board, and then sets the curLoc
 * to the location returned
 * @return the location to move to
*/
Location Ant::Move(){
	LocList lList=Board::GetOpen(this->curLoc);
	//this checks if there is an open spot
	//and randomly chooses a spot if there is
	Location moveTo=this->curLoc;
	if(lList.length>0){
		int index=rand()%lList.length;
		moveTo=lList.Locs[index];
	}
	delete lList.Locs;
	moveCount++;
	return moveTo;
}
/**
 * this sets the location of the ant
 * @param loc the location to move to.
 */
void Ant::SetLoc(Location loc){
	curLoc=loc;
}
/**
 * This return the new organsim to make
 * based on the open locations
 * @return the organism with the location set
 */
Organism *Ant::Reproduce(){
	Organism *_toMake=NULL;
	if(moveCount>=toBreed){
		LocList lList=Board::GetOpen(this->curLoc);
		//this checks if there is an open and
		//has the Doodlebug die if it has starved
		if(lList.length>0){
			moveCount=0;
			int index=rand()%lList.length;
			_toMake=new Ant(lList.Locs[index]);
			delete lList.Locs;
		}
	}
	return _toMake;
}
/**
 * This returns whether the organism is prey
 * @return true for the ant
 */
bool Ant::IsPrey(){
	return true;
}
/**
 * This gets the location of the ant
 * @return the location
 */
Location Ant::GetLoc(){
	return curLoc;
}
/**
 * This gets the character to draw for the ant
 * @return 'o' for the ant
 */
char Ant::GetChar(){
	return 'o';
}
/**
 * This is the destructor
 */
Ant::~Ant(){

}


