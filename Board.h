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
//this stores a list of locations
struct LocList{
	Location *Locs;
	int length;
};
typedef struct LocList LocList;

enum Dir{ up, down, left, right};

bool operator ==(const Location& a, const Location& b);
class Board{
public:
	//this continues to increment the search direction
	//to provide a random area to look
	static LocList GetPrey(Location curLoc);
	static LocList GetOpen(Location curLoc);
	//static Location GetFromSearchDir(Location curLoc);
	//actually plays a full turn on the board
	static void Play();
	//This moves the organism
	static void MoveOrganism(Organism *_curOrg);
	static void SpawnOrganism(Organism *_curOrg);
	//this will be called by the reproduce method
	//of any object
	//static void CreateAt(Location loc);
	static void Init(int doodleBugs, int ants, int xSize, int ySize);
	static void BoardPrint();
	static int GetTotalDoodle();
	static int GetTotalAnts();
	static int GetFinalDoodle();
	static int GetFinalAnts();
	static const int NUMDIR=4;
private:
	static Organism ***curBoard;
	static int min(int a, int b);
	static int max(int a, int b);
	Board();
	~Board();
	static int rSize;
	static int cSize;
	static int totalDoodleBugs, finalDoodleBugs;
	static int totalAnts, finalAnts;
	//one higher than the actual no.
	//to ensure all directions can be
	//generated
};


#endif /* BOARD_H_ */
