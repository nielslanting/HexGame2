#pragma once
#include "HexGame.h"
class Memento
{
private:
	HexGame* _state;
public:
	Memento(HexGame* state);
	~Memento();
	HexGame* getState();
	void setState(HexGame* state);
};

