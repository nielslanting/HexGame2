#pragma once
#include <stdexcept>
#include <regex>
#include <sstream>
#include "HexBoard.h"
#include "Bot.h"

class HexGame
{
public:
	bool Turn = false;
	bool PieRuleUsed = false;
	int Dimension;
	HexBoard* Board;
	Bot* Robot;

	HexGame::HexGame(const HexGame& other);
	HexGame(int dimension);
	HexGame(int dimension, bool turn, bool pieRule);
	~HexGame();

	bool HexGame::applyPieRule();
	void HexGame::draw();
	bool HexGame::input(const std::string &input);
};

