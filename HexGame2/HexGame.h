#pragma once
#include "HexBoard.h"
#include <stdexcept>
#include <regex>
#include <sstream>

class HexGame
{
public:
	bool Turn = false;
	bool PieRuleUsed = false;
	int Dimension;
	HexBoard* Board;

	HexGame(int dimension);
	HexGame(int dimension, bool turn, bool pieRule);
	~HexGame();

	bool applyPieRule();
	void draw();
	void input(const std::string &input);
};

