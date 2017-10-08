/*
 * Ant.h
 *
 *  Created on: Oct 8, 2017
 *      Author: klibby
 */

#ifndef ANT_H_
#define ANT_H_
#include "Organism.h"
class Ant: public Organism{
public:
	//all of these override the vitrual members
	//from Organism
	Location Move();
	Location Reproduce();
	bool IsPrey();
	Location GetLoc();
	char GetChar();
	void SetLoc(Location loc);
	Ant(Location initLoc);
	~Ant();
private:
	const int toStarve=3;
};



#endif /* ANT_H_ */
