#include "PieRuleCommand.h"

PieRuleCommand::PieRuleCommand()
{

}

PieRuleCommand::~PieRuleCommand()
{

}

void PieRuleCommand::execute()
{
	std::cout << "execute";
}

void PieRuleCommand::undo()
{
	std::cout << "undo";
}

void PieRuleCommand::redo()
{
	std::cout << "redo";
}