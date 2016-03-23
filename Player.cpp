#include <iostream>
#include "Player.h"

std::string Player::generateNumber(){
	std::cout << "Think of a number of 4 digits, but with no digits repeated" << std::endl<< "that the computer will try to guess."<<std::endl;
	std::string str = "";
	std::cin >> str;
	return str;
}

