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
int Board::numDoodleBugs=0;
int Board::numAnts=0;
bool operator ==(const Location& a, const Location& b){
	return(a.r==b.r && a.c==b.c);
}
void Board::Init(int ants, int doodleBugs, int rSize, int cSize){
//TODO create an "empty organism" so we can make a pointer to it for the array
	//board is in terms of r,c or y,x
	Board::rSize=rSize;
	Board::cSize=cSize;
	numAnts=ants;
	numDoodleBugs=doodleBugs;
	curBoard= new Organism**[rSize];
	nextBoard=new Organism**[rSize];
	for(int i=0; i<cSize; i++){
		curBoard[i]=new Organism*[cSize];
		nextBoard[i]=new Organism*[cSize];
	}
	curBoard[1][0]=new Ant(Location{1,0});
	curBoard[1][1]=new DoodleBug(Location{1,1});
	//curBoard[1][1]=new Ant(Location{1,1});
	curBoard[0][1]=new Ant(Location{0,1});
	curBoard[1][2]=new Ant(Location{1,2});
	curBoard[2][1]=new Ant(Location{2,1});

	/*LocList test=GetOpen(Location{1,1});
	for(int i=0; i<test.length;i++){
		std::cout<<test.Locs[i].r<<", "<<test.Locs[i].c<<std::endl;
	}
	BoardPrint();*/

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
				if(moveTo.r==-1){
					delete _temp;
					curBoard[curLoc.r][curLoc.c]=0;
				}
				else{
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
	}
	//check for spawns
	for (int r = 0; r < rSize; r++) {
		for (int c = 0; c < cSize; c++) {
			Organism *_temp= curBoard[r][c];
			if(_temp != 0){
				Organism *_toCreate=_temp->Reproduce();
				if(_toCreate != NULL){
					curBoard[_toCreate->GetLoc().r][_toCreate->GetLoc().c]
													=_toCreate;
					if(_toCreate->IsPrey()){
						numAnts++;
					}
					else if(!_toCreate->IsPrey()){
						numDoodleBugs++;
					}
				}
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
//This generates a LocList for the location of
//any bois marked as prey
//make sure to free the loclist when youre done with it
LocList Board::GetPrey(Location curLoc){
	int count=0;
	for (int i = 0; i < NUMDIR; i++) {
		Organism *_temp = curBoard[Board::max(0, curLoc.r - 1)][curLoc.c];
		switch ((Dir) i) {
		case up:
			_temp = curBoard[Board::max(0, curLoc.r - 1)][curLoc.c];
			break;
		case left:
			_temp = curBoard[curLoc.r][Board::max(0, curLoc.c - 1)];
			break;
		case down:
			_temp = curBoard[Board::min(rSize - 1, curLoc.r + 1)][curLoc.c];
			break;
		case right:
			_temp = curBoard[curLoc.r][Board::min(cSize - 1, curLoc.c + 1)];
			break;
		}
		if(_temp!=0&&_temp->IsPrey()){
			count++;
		}
	}

	LocList locs = LocList{(Location*)malloc(sizeof(Location)*count), count};
	count=0;

	for (int i = 0; i < NUMDIR; i++) {
		Organism *_temp = curBoard[Board::max(0, curLoc.r - 1)][curLoc.c];
		switch ((Dir) i) {
		case up:
			_temp = curBoard[Board::max(0, curLoc.r - 1)][curLoc.c];
			break;
		case left:
			_temp = curBoard[curLoc.r][Board::max(0, curLoc.c - 1)];
			break;
		case down:
			_temp = curBoard[Board::min(rSize - 1, curLoc.r + 1)][curLoc.c];
			break;
		case right:
			_temp = curBoard[curLoc.r][Board::min(cSize - 1, curLoc.c + 1)];
			break;
		}
		if(_temp!=0&&_temp->IsPrey()){
			locs.Locs[count]=_temp->GetLoc();
			count++;
		}
	}
	return locs;
}

//this moves the looking location one to the
LocList Board::GetOpen(Location curLoc) {
	//init count
	int count = 0;
	for (int i = 0; i < NUMDIR; i++) {
		Organism *_temp = curBoard[Board::max(0, curLoc.r - 1)][curLoc.c];
		switch ((Dir) i) {
		case up:
			_temp = curBoard[Board::max(0, curLoc.r - 1)][curLoc.c];
			break;
		case left:
			_temp = curBoard[curLoc.r][Board::max(0, curLoc.c - 1)];
			break;
		case down:
			_temp = curBoard[Board::min(rSize - 1, curLoc.r + 1)][curLoc.c];
			break;
		case right:
			_temp = curBoard[curLoc.r][Board::min(cSize - 1, curLoc.c + 1)];
			break;
		}
		if (_temp==0) {
			count++;
		}
	}

	LocList locs =
			LocList { (Location*) malloc(sizeof(Location) * count), count };
	count = 0;
	//find the organisms
	for (int i = 0; i < NUMDIR; i++) {
		Organism *_temp = curBoard[Board::max(0, curLoc.r - 1)][curLoc.c];
		Location loc={max(0, curLoc.r - 1),curLoc.c};
		switch ((Dir) i) {
		case up:
			_temp = curBoard[Board::max(0, curLoc.r - 1)][curLoc.c];
			loc={max(0, curLoc.r - 1),curLoc.c};
			break;
		case left:
			_temp = curBoard[curLoc.r][Board::max(0, curLoc.c - 1)];
			loc={curLoc.r,Board::max(0, curLoc.c - 1)};
			break;
		case down:
			_temp = curBoard[Board::min(rSize - 1, curLoc.r + 1)][curLoc.c];
			loc={Board::min(rSize - 1, curLoc.r + 1),curLoc.c};
			break;
		case right:
			_temp = curBoard[curLoc.r][Board::min(cSize - 1, curLoc.c + 1)];
			loc={curLoc.r,Board::min(cSize - 1, curLoc.c + 1)};
			break;
		}
		if (_temp==0) {
			locs.Locs[count] = loc;
			count++;
		}
	}
	return locs;
}

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

int Board::GetNumDoodle(){
	return numDoodleBugs;
}

int Board::GetNumAnts(){
	return numAnts;
}

/*Location Board::GetFromSearchDir(Location curLoc){
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
}*/
//gets the min of two numbers
