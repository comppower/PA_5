/*
 * Board.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: klibby
 */

#include "Board.h"
#include "DoodleBug.h"
#include "EmptyBug.h"
#include <stdlib.h>

EmptyBug ***Board::curBoard=NULL;
EmptyBug ***Board::nextBoard=NULL;
int Board::turn=0;

void Board::Init(int ants, int doodleBugs, int xSize, int ySize){
//TODO create an "empty organism" so we can make a pointer to it for the array
	curBoard= new EmptyBug**[ySize];
	for(int i=0; i<ySize; i++){
		curBoard[i]=new EmptyBug*[xSize];
	}
	for(int i=0; i<ySize; i++){
		for(int j=0; j<xSize; j++){
			curBoard[i][j]=new EmptyBug();
		}
	}
}
