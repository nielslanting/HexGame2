#pragma once
#include "ICommand.h"
#include <iostream>

class PieRuleCommand : public ICommand
{
public:
	PieRuleCommand();
	~PieRuleCommand();
	void execute();
	void undo();
	void redo();
};

