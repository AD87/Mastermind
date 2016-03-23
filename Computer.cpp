#include <algorithm>
#include "Computer.h"

std::string Computer::generateNumber(){
	std::string str;
	for (int i = 0; i < 4; i++){
		int r = rand();
		int num = r % 9;//random number between 0 and 9
		char c = (char)num + 48;//add 48, to match it to the correct character in the ascii table(conversion)
		str.push_back(c);
	}
	for (int i = 0; i < 4; i++){
		for (int j = i + 1; j < 4; j++){
			if (str[i] == str[j]) {
				str = generateNumber();//recursive function, keep calling the function until the number has not any digit repeated 
			}
		}
	}
	return str;
}