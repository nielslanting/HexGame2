#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <time.h>
#include <algorithm> 
#include <vector>

class HexBoard
{
public:
	std::map<int, short> Moves;
	std::vector<short> Board;
	int Dimension;	

	HexBoard(int);
	~HexBoard(void);

	void HexBoard::draw();
	std::vector<short> HexBoard::getAvailableMoves();
	void HexBoard::fillBoardRandom();
	bool HexBoard::makeMove(short player, int position);
	bool HexBoard::makeMove(short player, std::string move);
	bool HexBoard::invert();
};