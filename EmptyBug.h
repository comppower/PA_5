/*
 * EmptyBug.h
 *
 *  Created on: Oct 8, 2017
 *      Author: klibby
 */

#ifndef EMPTYBUG_H_
#define EMPTYBUG_H_
#include "Organism.h"

class EmptyBug: public Organism{
public:
	//all of these override the vitrual members
	//from Organism
	Location Move();
	Location Reproduce();
	bool IsPrey();
	bool IsEmpty();
	EmptyBug();
	virtual ~EmptyBug();
private:

};




#endif /* EMPTYBUG_H_ */
