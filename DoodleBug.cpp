/*
 * DoodleBug.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: klibby
 */

#include "DoodleBug.h"
#include "Organism.h"
#include "Board.h"
#include <stdlib.h>
//DoodleBug can't move after being born
/**
 * initializes the DoodleBug and calls the super constructor
 * @param initLoc the location to create the organism
 */
DoodleBug::DoodleBug(Location initLoc):Organism(initLoc){
	curLoc=initLoc;
	hasMoved=true;
	moveCount=0;
	turnsSinceEating=0;
}
/**
 * The DoodleBug looks for a location where it can eat
 * an ant and moves there if possible. Otherwise it looks
 * for an open spot
 * @return the location to move to
 */
Location DoodleBug::Move(){
	//tell the grid that this organism has moved
	moveCount++;
	LocList lList=Board::GetPrey(this->curLoc);
	Location moveTo = Location{0,0};
	if(lList.length>0){
		turnsSinceEating=0;
		int index=rand()%lList.length;
		moveTo=lList.Locs[index];
		delete lList.Locs;
		return moveTo;
	}
	turnsSinceEating++;
	lList=Board::GetOpen(this->curLoc);
	//this checks if there is an open and
	//has the Doodlebug die if it has starved
	if(lList.length>0){
		if(turnsSinceEating>=toStarve){
			return Location{-1,-1};
		}
		int index=rand()%lList.length;
		moveTo=lList.Locs[index];
		delete lList.Locs;
		return moveTo;
	}
	//this checks if it is sitting still
	//and starved
	if(turnsSinceEating>=toStarve){
		return Location{-1,-1};
	}
	//the -1, -1 says to remove it
	return this->curLoc;
}
/*
 * Sets the location of the Doodlebug
 * @param loc the location to set
 */
void DoodleBug::SetLoc(Location loc){
	this->curLoc=loc;
}
/**
 * Creates an offspring where there is space
 * and when it has moved enough spaces
 * @return the organism to create
 */
Organism *DoodleBug::Reproduce(){
	Organism *_toMake=NULL;
	if(moveCount>=toBreed){
		LocList lList=Board::GetOpen(this->curLoc);
		if(lList.length>0){
			moveCount=0;
			int index=rand()%lList.length;
			_toMake= new DoodleBug(lList.Locs[index]);
			delete lList.Locs;
		}
	}
	return _toMake;
}
/**
 * @return false for DoodleBug
 */
bool DoodleBug::IsPrey(){
	return false;
}
/**
 * @return location of DoodleBug
 */
Location DoodleBug::GetLoc(){
	return curLoc;
}
/**
 * @return 'x' for DoodleBug
 */
char DoodleBug::GetChar(){
	return 'x';
}
DoodleBug::~DoodleBug(){

}

