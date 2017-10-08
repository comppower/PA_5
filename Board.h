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
bool operator ==(const Location& a, const Location& b);
class Board{
public:
	//the caller must specifify the location
	//and direction to look, which should be random
	static Organism *GetNeighbor(Location curLoc, Dir dir);
	//this continues to increment the search direction
	//to provide a random area to look
	static Organism *GetNextNeighbor(Location curLoc);
	static Organism *GetAt(Location loc);
	static Location GetFromSearchDir(Location curLoc);
	//actually plays a full turn on the board
	static void Play();
	//this will be called by the reproduce method
	//of any object
	static void CreateAt(Location loc);
	static void Init(int ants, int doodleBugs, int xSize, int ySize);
	static void BoardPrint();
	//TODO make private again
	static Organism ***curBoard;
	static Organism ***nextBoard;
	static const int numDir=4;
private:
	static int min(int a, int b);
	static int max(int a, int b);
	Board();
	~Board();
	static Dir lookingAt;
	static int rSize;
	static int cSize;
	//one higher than the actual no.
	//to ensure all directions can be
	//generated
};


#endif /* BOARD_H_ */
