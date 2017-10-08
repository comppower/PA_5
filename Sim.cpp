/*
 * Sim.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: klibby
 */
#include <iostream>
#include "Board.h"

int main(){
	Board::Init(3, 3, 3, 3);
	Board::BoardPrint();
	return 0;
}


