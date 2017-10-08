/*
[xSize]; * DoodleBug.h
 *
 *  Created on: Oct 8, 2017
 *      Author: klibby
 */

#ifndef DOODLEBUG_H_
#define DOODLEBUG_H_
#include "Organism.h"

class DoodleBug: public Organism{
public:
	//all of these override the vitrual members
	//from Organism
	Location Move();
	Location Reproduce();
	bool IsPrey();
	Location GetLoc();
	char GetChar();
	DoodleBug(Location initLoc);
	~DoodleBug();
private:
	const int toStarve=3;
};



#endif /* DOODLEBUG_H_ */
