/*
 * Ant.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: klibby
 */
#include "Ant.h"

Ant::Ant(Location initLoc):Organism(initLoc){
	hasMoved=true;
	curLoc=initLoc;
	moveCount=0;
}
//this info is pulled by the program to move it on the
//board, and then sets the curLoc
//to the location returned
Location Ant::Move(){
	return curLoc;
}
void Ant::SetLoc(Location loc){
	curLoc=loc;
}
Location Ant::Reproduce(){
	return Location{0,0};
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


