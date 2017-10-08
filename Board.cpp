/*
 * Board.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: klibby
 */

#include "Board.h"
#include "DoodleBug.h"
#include <stdlib.h>
#include <iostream>

Organism ***Board::curBoard=NULL;
Organism ***Board::nextBoard=NULL;
int Board::xSize=0;
int Board::ySize=0;
Dir Board::lookingAt=up;
void Board::Init(int ants, int doodleBugs, int xSize, int ySize){
//TODO create an "empty organism" so we can make a pointer to it for the array
	Board::xSize=xSize;
	Board::ySize=ySize;
	curBoard= new Organism**[ySize];
	nextBoard=new Organism**[ySize];
	for(int i=0; i<ySize; i++){
		curBoard[i]=new Organism*[xSize];
		nextBoard[i]=new Organism*[xSize];
	}
	curBoard[2][2]=new DoodleBug(Location{2,2});
	curBoard[1][2]=new DoodleBug(Location{1,2});
	nextBoard[1][2]=new DoodleBug(Location{1,2});
	//test section for finding neighbor
	int count=0;
	Dir tempdir=down;
	bool found = !(GetNeighbor(curBoard[2][2]->GetLoc(),tempdir)->IsPrey());
	Organism *_temp;
	while(!found&&count<3){
		Organism *_temp = !(GetNextNeighbor(curBoard[2][2]->GetLoc())->IsPrey());
		count++;
	}
	if(_temp!=0){
		std::cout<<_temp->GetLoc().x<<" "<<count<<std::endl;
	}
	else{
		std::cout<<"outta luck"<<std::endl;
	}
}

//this starts the search for neighbors around a certain location
//Direction must be randomized first
Organism *Board::GetNeighbor(Location curLoc, Dir dir){
	lookingAt=dir;
	switch(dir){
	case up:
		return curBoard[max(0,curLoc.y-1)][curLoc.x];
		break;
	case down:
		return curBoard[min(xSize-1,curLoc.y+1)][curLoc.x];
		break;
	case left:
		return curBoard[curLoc.y][max(0, curLoc.x-1)];
		break;
	case right:
		return curBoard[curLoc.y][max(0, curLoc.x+1)];
		break;
	}
	//the case switch covers everything so it shouldn't
	//get here
	return curBoard[curLoc.y][curLoc.x];
}

//this moves the looking location one to the
Organism *Board::GetNextNeighbor(Location curLoc){
	lookingAt++;
	if(lookingAt>=4){
		lookingAt=0;
	}
	switch(lookingAt){
	case up:
		return curBoard[max(0,curLoc.y-1)][curLoc.x];
		break;
	case down:
		return curBoard[min(xSize-1,curLoc.y+1)][curLoc.x];
		break;
	case left:
		return curBoard[curLoc.y][max(0, curLoc.x-1)];
		break;
	case right:
		return curBoard[curLoc.y][max(0, curLoc.x+1)];
		break;
	}
	//the case switch covers everything so it shouldn't
	//get here
	return curBoard[curLoc.y][curLoc.x];
}
//gets the min of two numbers
int min(int a, int b){
	if(a<b){
		return a;
	}
	return b;
}
//gets the max of two numbers
int max(int a, int b){
	if(a>b){
		return a;
	}
	return b;
}
