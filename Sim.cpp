/*
 * Sim.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: klibby
 */
#include <iostream>
#include "Board.h"

int main(){
	srand(time(NULL));
	Board::Init(100, 5, 20, 20);
	for(int i=0; i<1000; i++){
		Board::Play();
	}
	std::cout<<Board::GetNumAnts()<<std::endl;
	std::cout<<Board::GetNumDoodle()<<std::endl;
	return 0;
}


