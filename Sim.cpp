/*
 * Sim.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: klibby
 */
#include <iostream>
#include <stdlib.h>
#include "Board.h"

int main(int argc, char *argv[]){
	for(int i=1; i<argc; i++){
		int arg=atoi(argv[i]);
		if(arg<0){
			std::cout<<"Invalid parameter "<<i<<" stopping execution"<<std::endl;
			return -1;
		}
	}
	int pauseVal=0;
	int steps=0;
	switch(argc){
	case 1:
		std::cout<<"Running with default args"<<std::endl;
		std::cout<<std::endl;
		std::cout<<"-------------"<<std::endl;
		Board::Init(5,100,20, 20);
		srand(1);
		break;
	case 2:
		Board::Init(5,100, atoi(argv[1]), atoi(argv[1]));
		srand(1);
		break;
	case 3:
		Board::Init(atoi(argv[2]),100, atoi(argv[1]), atoi(argv[1]));
		srand(1);
		break;
	case 4:
		Board::Init(atoi(argv[2]),atoi(argv[3]), atoi(argv[1]), atoi(argv[1]));
		srand(1);
		break;
	case 5:
		Board::Init(atoi(argv[2]),atoi(argv[3]), atoi(argv[1]), atoi(argv[1]));
		steps=atoi(argv[4]);
		srand(1);
		break;
	case 6:
		Board::Init(atoi(argv[2]),atoi(argv[3]), atoi(argv[1]), atoi(argv[1]));
		steps=atoi(argv[4]);
		if(argv[5]==0){
			srand(time(NULL));
		}
		else{
			srand(atoi(argv[5]));
		}
		break;
		//it will ignore anything 0 or below
	case 7:
		Board::Init(atoi(argv[2]),atoi(argv[3]), atoi(argv[1]), atoi(argv[1]));
		steps=atoi(argv[4]);
		if(argv[5]==0){
			srand(time(NULL));
		}
		else{
			srand(atoi(argv[5]));
		}
		pauseVal=atoi(argv[6]);
		break;
	default:
		std::cout<<"Invalid Parameter no. Stopping execution"<<std::endl;
		return -1;
		break;
	}
	int count=0;
	for(int i=0; i<steps; i++){
		Board::Play();
		if(pauseVal>0){
			if(i%pauseVal==0){
				Board::BoardPrint();
				count+=5;
				std::cout<<"num steps "<<count<<std::endl;
			}
		}
	}
	Board::BoardPrint();
	std::cout<<Board::GetNumAnts()<<std::endl;
	std::cout<<Board::GetNumDoodle()<<std::endl;
	return 0;
}


