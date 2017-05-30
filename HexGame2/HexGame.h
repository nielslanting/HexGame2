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

	HexGame::HexGame(const HexGame& other);
	HexGame(int dimension);
	HexGame(int dimension, bool turn, bool pieRule);
	~HexGame();

	bool HexGame::applyPieRule();
	void HexGame::draw();
	bool HexGame::input(const std::string &input);
};

