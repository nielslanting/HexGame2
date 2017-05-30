#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <time.h>
#include <algorithm> 
#include <vector>
#include <windows.h>

class HexBoard
{
public:
	std::map<int, short> Moves;
	std::vector<short> Board;
	int Dimension;	

	HexBoard(int);
	~HexBoard(void);

	void HexBoard::draw();
	std::vector<short> HexBoard::getAvailableMoves() const;
	void HexBoard::fillBoardRandom(bool turn = false);
	bool HexBoard::makeMove(short player, int position);
	bool HexBoard::makeMove(short player, std::string move);
	bool HexBoard::invert();
	int HexBoard::calculateWinner();
	bool HexBoard::hasWon(int currentPosition, int player, int min, int max, std::map<int, bool> &visited);
};