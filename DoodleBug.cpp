/*
 * DoodleBug.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: klibby
 */

#include "DoodleBug.h"
#include "Organism.h"


DoodleBug::DoodleBug(Location initLoc):Organism(initLoc){
	curLoc=initLoc;
	moveCount=0;
}
//this info is pulled by the program to move it on the
//board, and then sets the curLoc
//to the location returned
Location DoodleBug::Move(){
	return Location {0,0};
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
