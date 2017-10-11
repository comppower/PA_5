/*
 * Sim.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: klibby
 */
/**
 * This contains the main method for the project
 */
#include <iostream>
#include <stdlib.h>
#include "Board.h"
#include <string>
/**
 * @return true if there is enough space in the board for every
 * organism to be created
 */
bool isValid(int doodle, int ants, int boardSize){
	if(boardSize*boardSize<(doodle+ants)){
		std::cout<<"Board to small for no. creatures specified"<<std::endl;
		std::cout<<"Stopping Execution"<<std::endl;
		return false;
	}
	return true;
}

int main(int argc, char *argv[]){
	for(int i=1; i<argc; i++){
		int arg=atoi(argv[i]);
		if(arg<0){
			std::cout<<"Invalid parameter "<<i<<" stopping execution"<<std::endl;
			return -1;
		}
	}
	int pauseVal=0;
	int steps=1000;
	switch(argc){
	case 1:
		std::cout<<"Running with default args"<<std::endl;
		std::cout<<std::endl;
		std::cout<<"-------------"<<std::endl;
		srand(1);
		Board::Init(5,100,20, 20);
		break;
	case 2:
		if(!isValid(5, 100, atoi(argv[1]))){
			return -1;
		}
		srand(1);
		Board::Init(5,100, atoi(argv[1]), atoi(argv[1]));
		break;
	case 3:
		if(!isValid(atoi(argv[2]), 100, atoi(argv[1]))){
			return -1;
		}
		srand(1);
		Board::Init(atoi(argv[2]),100, atoi(argv[1]), atoi(argv[1]));
		break;
	case 4:
		if(!isValid(atoi(argv[2]), atoi(argv[3]), atoi(argv[1]))){
			return -1;
		}
		srand(1);
		Board::Init(atoi(argv[2]),atoi(argv[3]), atoi(argv[1]), atoi(argv[1]));
		break;
	case 5:
		if(!isValid(atoi(argv[2]), atoi(argv[3]), atoi(argv[1]))){
			return -1;
		}
		steps=atoi(argv[4]);
		srand(1);
		Board::Init(atoi(argv[2]),atoi(argv[3]), atoi(argv[1]), atoi(argv[1]));
		break;
	case 6:
		if(!isValid(atoi(argv[2]), atoi(argv[3]), atoi(argv[1]))){
			return -1;
		}
		steps=atoi(argv[4]);
		if(argv[5]==0){
			srand(time(NULL));
		}
		else{
			srand(atoi(argv[5]));
		}
		Board::Init(atoi(argv[2]),atoi(argv[3]), atoi(argv[1]), atoi(argv[1]));
		break;
		//it will ignore anything 0 or below
	case 7:
		if(!isValid(atoi(argv[2]), atoi(argv[3]), atoi(argv[1]))){
			return -1;
		}
		steps=atoi(argv[4]);
		if(atoi(argv[5])==0){
			srand(time(NULL));
		}
		else{
			srand(atoi(argv[5]));
		}
		Board::Init(atoi(argv[2]),atoi(argv[3]), atoi(argv[1]), atoi(argv[1]));
		pauseVal=atoi(argv[6]);
		break;
	default:
		std::cout<<"Invalid Parameter no. Stopping execution"<<std::endl;
		return -1;
		break;
	}
	//prime the pump
	int count=0;
	std::string temp;
	//ouput the initial setup
	if(pauseVal>0){
		Board::BoardPrint();
		Board::Play();
		std::cout<<"num steps "<<count<<std::endl;
		std::cout<<"enter any character to continue"<<std::endl;
		std::cin>>temp;
	}
	//keep printing
	for(int i=1; i<steps; i++){
		Board::Play();
		if(pauseVal>0){
			if(i%pauseVal==0){
				Board::BoardPrint();
				count+=pauseVal;
				std::cout<<"num steps "<<count<<std::endl;
				std::cout<<"hit any key to continue"<<std::endl;
				std::cin>>temp;
			}
		}
	}
	//give it that last output
	Board::BoardPrint();
	std::cout<<"Steps ran "<<steps<<std::endl;
	std::cout<<"Final Doodlebug count "<<Board::GetFinalDoodle()<<std::endl;
	std::cout<<"Final Ant count "<<Board::GetFinalAnts()<<std::endl;
	std::cout<<"Total Ants made "<<Board::GetTotalAnts()<<std::endl;
	std::cout<<"Total Doodlebugs made "<<Board::GetTotalDoodle()<<std::endl;
	//call it a day
	return 0;
}



