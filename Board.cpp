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
int Board::rSize=0;
int Board::ySize=0;
Dir Board::lookingAt=up;
void Board::Init(int ants, int doodleBugs, int rSize, int cSize){
//TODO create an "empty organism" so we can make a pointer to it for the array
	//board is in terms of r,c or y,x
	Board::rSize=rSize;
	Board::ySize=cSize;
	curBoard= new Organism**[cSize];
	nextBoard=new Organism**[cSize];
	for(int i=0; i<cSize; i++){
		curBoard[i]=new Organism*[rSize];
		nextBoard[i]=new Organism*[rSize];
	}
	curBoard[2][2]=new DoodleBug(Location{2,2});
	curBoard[2][1]=new DoodleBug(Location{1,2});
	nextBoard[1][2]=new DoodleBug(Location{1,2});
	//test section for finding neighbor
	int count=0;
	Dir tempdir=down;

	Organism *_temp =GetNeighbor(Location{2,2},tempdir);
	bool found=false;
	if(_temp!=0){
		found = !_temp->IsPrey();
	}
	while(!found&&count<3){
		_temp = GetNextNeighbor(curBoard[2][2]->GetLoc());
		if(_temp!=0){
			found=!_temp->IsPrey();
		}
		count++;
	}
	if(_temp!=0){
		std::cout<<_temp->GetLoc().c<<" "<<lookingAt<<std::endl;
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
		return curBoard[Board::max(0,curLoc.r-1)][curLoc.c];
		break;
	case down:
		return curBoard[Board::min(rSize-1,curLoc.r+1)][curLoc.c];
		break;
	case left:
		return curBoard[curLoc.r][Board::max(0, curLoc.c-1)];
		break;
	case right:
		return curBoard[curLoc.c][Board::max(0, curLoc.c+1)];
		break;
	}
	//the case switch covers everything so it shouldn't
	//get here
	return curBoard[curLoc.r][curLoc.c];
}

//this moves the looking location one to the
Organism *Board::GetNextNeighbor(Location curLoc){
	lookingAt=(Dir)((int)(lookingAt+1));
	if(lookingAt>=4){
		lookingAt=(Dir)0;
	}
	switch(lookingAt){
	case up:
		return curBoard[Board::max(0,curLoc.r-1)][curLoc.c];
		break;
	case down:
		return curBoard[Board::min(rSize-1,curLoc.r+1)][curLoc.c];
		break;
	case left:
		return curBoard[curLoc.c][Board::max(0, curLoc.r-1)];
		break;
	case right:
		return curBoard[curLoc.c][Board::max(0, (curLoc.r)+1)];
		break;
	}
	//the case switch covers everything so it shouldn't
	//get here
	return curBoard[curLoc.r][curLoc.c];
}
//gets the min of two numbers
int Board::min(int a, int b){
	if(a<b){
		return a;
	}
	return b;
}
//gets the max of two numbers
int Board::max(int a, int b){
	if(a>b){
		return a;
	}
	return b;
}
