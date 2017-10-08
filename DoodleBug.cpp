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
	//randomize the starting direction
	//Dir dir = (Dir)(rand()%4);
	//start the search
	//Organism *_temp =Board::GetNeighbor(this->curLoc,dir);

	/*//you need to make sure it hasn't found itself
	if(_temp!=0&&_temp!=this){
		//if it finds prey have it move and reset its eating counter
		found = _temp->IsPrey();
		turnsSinceEating=0;
		return _temp->GetLoc();
	}*/
	//then look for a bite to eat
	/*bool found=false;
	int count=0;
	//check all 4 directions
	while(!found&&count<4){
		//you need to make sure it hasn't found itself
		if(_temp!=0&&_temp!=this){
			found= _temp->IsPrey();
			turnsSinceEating=0;
			return _temp->GetLoc();
		}
		_temp = Board::GetNextNeighbor(this->curLoc);
		count++;
	}
	//then find a blank space
	dir = (Dir)(rand()%4);
	//start the search
	_temp =Board::GetNeighbor(this->curLoc,dir);
	count=0;
	if(!found){
		//obviously it hasn't eaten this turn
		turnsSinceEating++;
		//needs to look through all four directions again
		while(!found&&count<4){
			_temp = Board::GetNextNeighbor(this->curLoc);
			if(_temp==0){
				found=true;
			}
			count++;
		}
	}
	//if it hasn't eaten in three turns it returns the location
	//of death
	//TODO switch back to 3
	if(turnsSinceEating==15){
		return Location{-1, -1};
	}
	//if it found a spot and isn't it moves there
	else if(found){
		//get the location of the blank space
		return Board::GetFromSearchDir(this->curLoc);
	}
	//otherwise stay put
	return this->curLoc;*/
	return Location{0,0};
}
void DoodleBug::SetLoc(Location loc){
	this->curLoc=loc;
}
Location DoodleBug::Reproduce(){
	return Location{0,0};
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
