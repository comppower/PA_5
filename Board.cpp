/*
 * Board.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: klibby
 */

#include "Board.h"
#include "DoodleBug.h"
#include <stdlib.h>

DoodleBug ***Board::curBoard=NULL;
DoodleBug ***Board::nextBoard=NULL;
int Board::turn=0;

void Board::Init(int ants, int doodleBugs, int xSize, int ySize){
//TODO create an "empty organism" so we can make a pointer to it for the array
	curBoard= new DoodleBug**[ySize];
	for(int i=0; i<ySize; i++){
		curBoard[i]=new DoodleBug*[xSize];
	}
}
