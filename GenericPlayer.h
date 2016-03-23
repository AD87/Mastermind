#pragma once

#include <vector>

class GenericPlayer{//base class for both players
public:
	~GenericPlayer(){}
	virtual std::string generateNumber() = 0;
protected:

};