/*
 * Ant.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: klibby
 */
#include "Ant.h"
#include "Board.h"
#include <stdlib.h>
Ant::Ant(Location initLoc):Organism(initLoc){
	hasMoved=true;
	curLoc=initLoc;
	moveCount=0;
}
//this info is pulled by the program to move it on the
//board, and then sets the curLoc
//to the location returned
Location Ant::Move(){
	LocList lList=Board::GetOpen(this->curLoc);
	//this checks if there is an open and
	//has the Doodlebug die if it has starved
	Location moveTo=this->curLoc;
	if(lList.length>0){
		int index=rand()%lList.length;
		moveTo=lList.Locs[index];
	}
	delete lList.Locs;
	moveCount++;
	return moveTo;
}
void Ant::SetLoc(Location loc){
	curLoc=loc;
}
Organism *Ant::Reproduce(){
	Organism *_toMake=NULL;
	if(moveCount>=toBreed){
		moveCount=0;
		LocList lList=Board::GetOpen(this->curLoc);
		//this checks if there is an open and
		//has the Doodlebug die if it has starved
		if(lList.length>0){
			int index=rand()%lList.length;
			//_toMake=new Ant(lList.Locs[index]);
			delete lList.Locs;
		}
	}
	return _toMake;
}
bool Ant::IsPrey(){
	return true;
}
Location Ant::GetLoc(){
	return curLoc;
}
char Ant::GetChar(){
	return 'o';
}
Ant::~Ant(){

}


