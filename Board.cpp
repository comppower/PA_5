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
int Board::rSize=0;
int Board::cSize=0;
int Board::totalDoodleBugs=0;
int Board::finalDoodleBugs=0;
int Board::totalAnts=0;
int Board::finalAnts=0;
/**
 * This overloads the equivalence check operator for
 * the location structs
 * @param a the first location value to check
 * @param b the location being compared against a
 * @returns true if they have the same values
 */
bool operator ==(const Location& a, const Location& b){
	return(a.r==b.r && a.c==b.c);
}
/**
 * This sets up the board based on the values returned from the command
 * line
 * @param doodleBugs the number of Doodlebugs to create at the beginning
 * @param ants the number of ants to create at the start
 * @param rSize the size of the rows
 * @param cSize the size of the columns
 *
 */
void Board::Init(int doodleBugs, int ants, int rSize, int cSize){
	//board is in terms of r,c or y,x
	Board::rSize=rSize;
	Board::cSize=cSize;
	totalAnts=finalAnts=ants;
	totalDoodleBugs=finalDoodleBugs=doodleBugs;
	curBoard= new Organism**[rSize];
	for(int i=0; i<cSize; i++){
		curBoard[i]=new Organism*[cSize];
	}
	for(int i=0; i<ants; i++){
		bool placed=false;
		while(!placed){
			Location l={rand()%rSize, rand()%cSize};
			if(curBoard[l.r][l.c]==NULL){
				curBoard[l.r][l.c]=new Ant(l);
				placed=true;
			}
		}
	}
	for(int i=0; i<doodleBugs; i++){
		bool placed=false;
		while(!placed){
			Location l={rand()%rSize, rand()%cSize};
			if(curBoard[l.r][l.c]==NULL){
				curBoard[l.r][l.c]=new DoodleBug(l);
				placed=true;
			}
		}
	}
}
/**
 * This moves the specified organism on the board based
 * on the type
 * @param _curOrg the organism to move
 */
void Board::MoveOrganism(Organism *_curOrg) {
	Location moveTo = _curOrg->Move();
	Location curLoc = _curOrg->GetLoc();
	//if whatever is there is getting eaten, remove it
	if (moveTo.r == -1) {
		//adjust final counts
		if(!_curOrg->IsPrey()){
			finalDoodleBugs--;
		}
		else{
			finalAnts--;
		}
		delete _curOrg;
		curBoard[curLoc.r][curLoc.c] = 0;
	}
	else {
		if (curBoard[moveTo.r][moveTo.c] != 0 && !(curLoc == moveTo)) {
			//adjust final counts
			if (curBoard[moveTo.r][moveTo.c]->IsPrey()) {
				finalAnts--;
			}
			else {
				finalDoodleBugs--;
			}
			//delete whatever is in the target position
			delete curBoard[moveTo.r][moveTo.c];
		}
		//move the reference to the move location
		curBoard[moveTo.r][moveTo.c] = curBoard[curLoc.r][curLoc.c];
		//reset the original if needed
		if (!(curLoc == moveTo)) {
			curBoard[curLoc.r][curLoc.c] = 0;
		}
		//update the location of the organism
		curBoard[moveTo.r][moveTo.c]->SetLoc(moveTo);
		_curOrg->hasMoved = true;
	}
}
/**
 * This moves the specified organism on the board based
 * @param _curOrg the organism to spawn
 */
void Board::SpawnOrganism(Organism *_curOrg) {
	if (_curOrg != 0) {
		Organism *_toCreate = _curOrg->Reproduce();
		if (_toCreate != NULL) {
			curBoard[_toCreate->GetLoc().r][_toCreate->GetLoc().c] = _toCreate;
			if (_toCreate->IsPrey()) {
				totalAnts++;
				finalAnts++;
			} else if (!_toCreate->IsPrey()) {
				totalDoodleBugs++;
				finalDoodleBugs++;
			}
		}
	}
}
/**
 * This is where the Organisms are moved and spawn
 */
void Board::Play(){
	//Moves the DoodleBugs
	for (int r = 0; r < rSize; r++) {
		for (int c = 0; c < cSize; c++) {
			Organism *_temp = curBoard[r][c];
			if (_temp != 0 && !_temp->hasMoved&& !(_temp->IsPrey())) {
				MoveOrganism(_temp);
			}
		}
	}
	//Spawns the DoodleBugs
	for (int r = 0; r < rSize; r++) {
		for (int c = 0; c < cSize; c++) {
			Organism *_temp = curBoard[r][c];
			if (_temp != 0 && !(_temp->IsPrey())) {
				SpawnOrganism(_temp);
			}
		}
	}
	//Moves the Ants
	for (int r = 0; r < rSize; r++) {
		for (int c = 0; c < cSize; c++) {
			Organism *_temp = curBoard[r][c];
			if (_temp != 0 && !_temp->hasMoved&& _temp->IsPrey()){
				MoveOrganism(_temp);
			}
		}
	}
	//Spawns the Ants
	for (int r = 0; r < rSize; r++) {
		for (int c = 0; c < cSize; c++) {
			Organism *_temp = curBoard[r][c];
			if (_temp != 0 && _temp->IsPrey()){
				SpawnOrganism(_temp);
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
}
/**This generates a LocList for the location of
 * any things marked as prey
 * make sure to free the loclist when you're done with it
 * @param curLoc the location of the caller
 * @return The list of locations with prey
 */
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

/**This generates a LocList for the location of
 * any open spot
 * make sure to free the loclist when you're done with it
 * @param curLoc the location of the caller
 * @return The list of locations with prey
 */
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
/**
 * finds minimum of 2 numbers
 * @param a the first number
 * @param b the second number
 * @returns the max of the numbers
 */
int Board::min(int a, int b){
	if(a<b){
		return a;
	}
	return b;
}
/**
 * finds maximum of 2 numbers
 * @param a the first number
 * @param b the second number
 * @returns the min of the numbers
 */
int Board::max(int a, int b){
	if(a>b){
		return a;
	}
	return b;
}
/**
 * Prints the board
 */
void Board::BoardPrint(){
	for(int i=0; i<rSize;i++){
		for(int j=0; j<cSize; j++){
			if(curBoard[i][j]!=0){
				std::cout<<curBoard[i][j]->GetChar();
			}
			else{
				std::cout<<' ';
			}
		}
		std::cout<<std::endl;
	}
	std::cout<<"--------------"<<std::endl;
}
/**
 * @return the total no of Doodlebugs created
 */
int Board::GetTotalDoodle(){
	return totalDoodleBugs;
}
/**
 * @return the total number of ants made
 */
int Board::GetTotalAnts(){
	return totalAnts;
}
/**
 * @return the final number of ants made
 */
int Board::GetFinalAnts(){
	return finalAnts;
}
/**
 * @returns the final number of Doodlebugs made
 */
int Board::GetFinalDoodle(){
	return finalDoodleBugs;
}


