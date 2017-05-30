#include "Memento.h"



Memento::Memento(HexGame* state)
{
	_state = state;
}

Memento::~Memento()
{
}

HexGame* Memento::getState()
{
	return _state;
}

void Memento::setState(HexGame* state)
{
	_state = state;
}
