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
	//this continues to increment the search direction
	//to provide a random area to look
	static Organism *GetNextNeighbor(Location curLoc);
	static Organism *GetAt(Location loc);
	//this will be called by the reproduce method
	//of any object
	static void CreateAt(Location loc);
	static void EatAt(Location loc);
	static void Init(int ants, int doodleBugs, int xSize, int ySize);
	static void BoardPrint();
	//TODO make private again
	static Organism ***curBoard;
	static Organism ***nextBoard;
private:
	static int min(int a, int b);
	static int max(int a, int b);
	Board();
	~Board();
	static Dir lookingAt;
	static int rSize;
	static int ySize;
};


#endif /* BOARD_H_ */
