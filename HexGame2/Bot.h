#pragma once
#include "HexBoard.h"
#include <vector>
#include <thread>
#include <future>
#include <ctime>

class Bot
{
private:
	unsigned ConcurentThreadsSupported;
public:
	Bot();
	~Bot();
	int calculateBestPosition(const HexBoard& hexBoard, int player) const;
	std::vector<int> monteCarlo(const std::vector<HexBoard*>& board, unsigned boardsPerThread, int player, int c, int winSize) const;
};

