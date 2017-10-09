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

DoodleBug::DoodleBug(Location initLoc):Organism(initLoc){
	curLoc=initLoc;
	hasMoved=true;
	moveCount=0;
	turnsSinceEating=0;
}
//this info is pulled by the program to move it on the
//board, and then sets the curLoc
//to the location returned
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
void DoodleBug::SetLoc(Location loc){
	this->curLoc=loc;
}
Organism *DoodleBug::Reproduce(){
	Organism *_toMake=NULL;
	if(moveCount>=toBreed){
		LocList lList=Board::GetOpen(this->curLoc);
		if(lList.length>0){
			int index=rand()%lList.length;
			_toMake= new DoodleBug(lList.Locs[index]);
			delete lList.Locs;
		}
	}
	return _toMake;
}
bool DoodleBug::IsPrey(){
	return false;
}
Location DoodleBug::GetLoc(){
	return curLoc;
}
char DoodleBug::GetChar(){
	return 'x';
}
DoodleBug::~DoodleBug(){

}

/*test section for finding neighbor
Organism *_temp =GetNeighbor(Location{2,2},lookingAt);
bool found=false;
//you need to make sure it hasn't found itself
if(_temp!=0&&_temp!=curBoard[2][2]){
	found = !_temp->IsPrey();
}
int count=0;
while(!found&&count<3){
	_temp = GetNextNeighbor(curBoard[2][2]->GetLoc());
	//you need to make sure it hasn't found itself
	if(_temp!=0&&_temp!=curBoard[2][2]){
		found=!_temp->IsPrey();
	}
	count++;
}
if(_temp!=0){
	std::cout<<_temp->GetLoc().r<<_temp->GetLoc().c<<" "<<lookingAt<<std::endl;
}
else{
	std::cout<<"outta luck"<<std::endl;
}
//end test section*/
