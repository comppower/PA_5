/*
 * DoodleBug.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: klibby
 */

#include "DoodleBug.h"

DoodleBug::DoodleBug(Location initLoc):Organism(initLoc){
	curLoc=initLoc;
	moveCount=0;
}

Location DoodleBug::Move(){
	return Location {0,0};
}

Location DoodleBug::Reproduce(){
	return Location{0,0};
}

bool DoodleBug::IsPrey(){
	return false;
}
DoodleBug::~DoodleBug(){

}
