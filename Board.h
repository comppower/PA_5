/*
 * Board.h
 *
 *  Created on: Oct 8, 2017
 *      Author: klibby
 */

#ifndef BOARD_H_
#define BOARD_H_
#include "Organism.h"
#include "DoodleBug.h"

enum Dir{ up, down, left, right};

typedef struct Location Location;

class Board{
public:
	//the caller must specifify the location
	//and direction to look, which should be random
	static Organism *GetNeighbor(Location curLoc, Dir dir);
	static Organism *GetAt(Location loc);
	//this will be called by the reproduce method
	//of any object
	static void CreateAt(Location loc);
	static void EatAt(Location loc);
	static void Init(int ants, int doodleBugs, int xSize, int ySize);
	static void BoardPrint();
	//TODO make private again
	static DoodleBug ***curBoard;
	static DoodleBug ***nextBoard;
private:
	Board();
	~Board();
	static int turn;
};


#endif /* BOARD_H_ */
