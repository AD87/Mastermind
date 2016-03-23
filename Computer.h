#pragma once

#include <string>
#include "GenericPlayer.h"

class Computer :public GenericPlayer{
public:
	virtual std::string generateNumber() override;
private:
};