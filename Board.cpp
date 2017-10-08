/*
 * Board.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: klibby
 */

#include "Board.h"
#include "DoodleBug.h"
#include "Ant.h"
#include <stdlib.h>
#include <iostream>

Organism ***Board::curBoard=NULL;
Organism ***Board::nextBoard=NULL;
int Board::rSize=0;
int Board::cSize=0;
Dir Board::lookingAt=up;
bool operator ==(const Location& a, const Location& b){
	return(a.r==b.r && a.c==b.c);
}
void Board::Init(int ants, int doodleBugs, int rSize, int cSize){
//TODO create an "empty organism" so we can make a pointer to it for the array
	//board is in terms of r,c or y,x
	Board::rSize=rSize;
	Board::cSize=cSize;
	curBoard= new Organism**[rSize];
	nextBoard=new Organism**[rSize];
	for(int i=0; i<cSize; i++){
		curBoard[i]=new Organism*[cSize];
		nextBoard[i]=new Organism*[cSize];
	}
	curBoard[1][0]=new Ant(Location{1,0});
	curBoard[1][1]=new DoodleBug(Location{1,1});
	curBoard[1][2]=new Ant(Location{1,2});


}
void Board::Play(){
	//Moves the organisms
	for (int r = 0; r < rSize; r++) {
		for (int c = 0; c < cSize; c++) {
			Organism *_temp = curBoard[r][c];
			if (_temp != 0 && !_temp->hasMoved) {
				Location moveTo=_temp->Move();
				Location curLoc=_temp->GetLoc();
				//if whatever is there is getting eaten, remove it
				if(curBoard[moveTo.r][moveTo.c]!=0&&!(curLoc==moveTo)){
					delete curBoard[moveTo.r][moveTo.c];
				}
				//move the reference to the move location
				curBoard[moveTo.r][moveTo.c]=curBoard[curLoc.r][curLoc.c];
				//reset the original if needed
				if(!(curLoc==moveTo)){
					curBoard[curLoc.r][curLoc.c]=0;
				}
				//update the location of the organism
				curBoard[moveTo.r][moveTo.c]->SetLoc(moveTo);
				_temp->hasMoved = true;
			}
		}
	}
	//resets the hasMoved
	for (int r = 0; r < rSize; r++) {
		for (int c = 0; c < cSize; c++) {
			Organism *_temp = curBoard[r][c];
			if (_temp != 0) {
				_temp->hasMoved = false;
			}
		}
	}
	//print the result
	BoardPrint();
}
//this starts the search for neighbors around a certain location
//Direction must be randomized first
Organism *Board::GetNeighbor(Location curLoc, Dir dir){
	lookingAt=dir;
	switch(lookingAt){
	case up:
		return curBoard[Board::max(0,curLoc.r-1)][curLoc.c];
		break;
	case left:
		return curBoard[curLoc.r][Board::max(0, curLoc.c-1)];
		break;
	case down:
		return curBoard[Board::min(rSize-1,curLoc.r+1)][curLoc.c];
		break;
	case right:
		return curBoard[curLoc.r][Board::min(cSize-1, curLoc.c+1)];
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
		return curBoard[curLoc.r][Board::max(0, curLoc.c-1)];
		break;
	case right:
		return curBoard[curLoc.r][Board::min(cSize-1, (curLoc.c)+1)];
		break;
	}
	//the case switch covers everything so it shouldn't
	//get here
	return curBoard[curLoc.r][curLoc.c];
}

Location Board::GetFromSearchDir(Location curLoc){
	//finds the location of where the board was
	//checking based on the current direction
	switch(lookingAt){
	case up:
		return Location{max(0,curLoc.r-1),curLoc.c};
		break;
	case down:
		return Location{min(rSize-1,curLoc.r+1),curLoc.c};
		break;
	case left:
		return Location{curLoc.r, max(0, curLoc.c-1)};
		break;
	case right:
		return Location{curLoc.r, min(cSize-1, curLoc.c+1)};
		break;
	}
	return curLoc;
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

void Board::BoardPrint(){
	for(int i=0; i<rSize;i++){
		for(int j=0; j<cSize; j++){
			if(curBoard[i][j]!=0){
				std::cout<<curBoard[i][j]->GetChar();
			}
			else{
				std::cout<<'H';
			}
		}
		std::cout<<std::endl;
	}
	std::cout<<"--------------"<<std::endl;
}
