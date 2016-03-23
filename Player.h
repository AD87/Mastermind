#pragma once

#include <string>
#include "GenericPlayer.h"

class Player :public GenericPlayer{
public:
	virtual std::string generateNumber() override;
private:
};