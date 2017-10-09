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
	Board::Init(3, 3, 2, 2);
	for(int i=0; i<25; i++){
		Board::Play();
	}
	return 0;
}


