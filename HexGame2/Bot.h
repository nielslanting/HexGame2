#pragma once
#include "HexBoard.h"
#include <vector>
#include <thread>
#include <future>
#include <ctime>
#include <chrono>

struct MonteResult {
	int count;
	std::vector<int> wins;
};

class Bot
{
private:
	unsigned ConcurentThreadsSupported;
	unsigned Strength = 5000;
public:
	Bot();
	~Bot();
	int calculateBestPosition(const HexBoard & hexBoard, short player) const;
	MonteResult monteCarlo(const HexBoard & board, std::vector<short> available, short player, int timeout) const;
	void setStrength(unsigned strength);
};

