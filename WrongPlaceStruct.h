#pragma once

struct  WrongPlaceStruct{
	WrongPlaceStruct(){
		//place[] = { false, false, false, false };
		place[0] = false;
		place[1] = false;
		place[2] = false;
		place[3] = false;
		num = ' ';
	}

	bool place[4];//keep track of the wrong position, to prevent the computer to guess it in the wrong place again
	char num;//the number as a char
};