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
DoodleBug::~DoodleBug(){

}
