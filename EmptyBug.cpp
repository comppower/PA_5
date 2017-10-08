/*
 * EmptyBug.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: klibby
 */

#include "EmptyBug.h"
EmptyBug::EmptyBug():Organism(Location{-1,-1}){
	moveCount=0;
	curLoc=Location{-1,-1};
}

Location EmptyBug::Move(){
	return Location {-1,-1};
}

Location EmptyBug::Reproduce(){
	return Location{-1,-1};
}
bool EmptyBug::IsEmpty(){
	return true;
}
bool EmptyBug::IsPrey(){
	return false;
}
EmptyBug::~EmptyBug(){

}
