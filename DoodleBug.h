/*
[xSize]; * DoodleBug.h
 *
 *  Created on: Oct 8, 2017
 *      Author: klibby
 */

#ifndef DOODLEBUG_H_
#define DOODLEBUG_H_
#include "Organism.h"
#include "EmptyBug.h"

class DoodleBug: public EmptyBug{
public:
	//all of these override the vitrual members
	//from Organism
	Location Move();
	Location Reproduce();
	bool IsPrey();
	bool IsEmpty();
	DoodleBug(Location initLoc);
	~DoodleBug();
private:
	const int toStarve=3;
};



#endif /* DOODLEBUG_H_ */
