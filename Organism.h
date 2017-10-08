/*
 * Organism.h
 *
 *  Created on: Oct 8, 2017
 *      Author: klibby
 */

#ifndef ORGANISM_H_
#define ORGANISM_H_

struct Location{
	int x;
	int y;
};

class Organism{
public:
	//this says the organism needs to know
	//WHERE its being created
	virtual Location Move() =0;
	virtual Location Reproduce()=0;
	virtual bool IsPrey()=0;
	virtual ~Organism(){;}
protected:
	//the constructor is protected becuase
	//there is no need to initialize a class
	//of this type
	Organism(Location initLoc){;}
	int moveCount;
	//this stores the position
	//of the organism, to be used to find
	//position
	Location curLoc;
private:

};



#endif /* ORGANISM_H_ */