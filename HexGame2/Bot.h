#pragma once
#include "HexBoard.h"
#include <vector>

class Bot
{
public:
	Bot();
	~Bot();
	int calculateBestPosition(const HexBoard& hexBoard, int player) const;
};

