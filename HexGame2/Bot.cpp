#include "Bot.h"

Bot::Bot()
{
	ConcurentThreadsSupported = std::thread::hardware_concurrency();
	if (ConcurentThreadsSupported < 4) ConcurentThreadsSupported = 4;
}


Bot::~Bot()
{
}

int Bot::calculateBestPosition(const HexBoard& hexBoard, int player) const
{
	std::cout << "Calculating move..." << std::endl;
	std::cout << "Running on: " << ConcurentThreadsSupported << " threads." << std::endl;

	std::vector<short> availableMoves = hexBoard.getAvailableMoves();

	// Store the results
	std::vector<int> wins(hexBoard.Board.size(), 0);
	std::vector<std::vector<HexBoard*>>boards(ConcurentThreadsSupported);

	unsigned boardsPerThread = floor(availableMoves.size() / ConcurentThreadsSupported);
	// unsigned boardsForLastThread = availableMoves.size() - (boardsPerThread * (ConcurentThreadsSupported - 1));

	// Create a board for each posible move, and set the available move
	for (std::size_t i = 0; i != availableMoves.size(); i++) {
		unsigned section = floor(i / boardsPerThread);

		if (section >= ConcurentThreadsSupported) section--;

		HexBoard* newBoard = new HexBoard(hexBoard);
		newBoard->makeMove(player, availableMoves[i]);

		boards[section].push_back(newBoard);
	}

	// Monte carlo
	std::clock_t begin = clock();

	// Multi-threaded
	std::vector<std::future<std::vector<int>>> results;

	for (int c = 0; c < boards.size(); c++) {
		std::vector<HexBoard*> splitBoard = boards[c];

		results.push_back(std::async(std::launch::async, &Bot::monteCarlo, this, splitBoard, boardsPerThread, player, c, wins.size()));
	}

	// Merge the results
	for (auto&& future : results) {
		std::vector<int> result = future.get();	

		int lsum = 0;
		for (auto& n : result)
			lsum += n;

		std::cout << "Result size: " << result.size() << " | sum: " << lsum << std::endl;
		for (auto i = 0; i < result.size(); i++) {
			wins[i] += result[i];
		}
	}

	// Single-threaded
	/*for (int c = 0; c < boards.size(); c++) {
		std::vector<HexBoard*> splitBoard = boards[c];
		
		std::vector<int> result = monteCarlo(splitBoard, boardsPerThread, player, c, wins.size());

		int lsum = 0;
		for (auto& n : result)
			lsum += n;

		std::cout << "Result size: " << result.size() << " | sum: " << lsum << std::endl;
		for (auto i = 0; i < result.size(); i++) {
			wins[i] += result[i];
		}
	}*/

	clock_t end = clock();
	double diff = double(end - begin) / CLOCKS_PER_SEC;

	std::cout << "Calculation time: " << diff << std::endl;

	int sum = 0;
	for (auto& n : wins)
		sum += n;

	std::cout << "Calculations done: " << sum << std::endl;

	double timePerCalculation = (diff / sum) * 1000;

	std::cout << "Time per calculation: " << timePerCalculation << " ms" << std::endl;

	int pos = std::distance(wins.begin(), std::max_element(wins.begin(), wins.end()));

	return availableMoves.at(pos);
}

std::vector<int> Bot::monteCarlo(const std::vector<HexBoard*>& board, unsigned boardsPerThread, int player, int c, int winSize) const
{
	std::vector<int> wins(winSize, 0);

	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < 30; j++) {
			HexBoard* newBoard = new HexBoard(*board[i]);
			newBoard->fillBoardRandom();

			auto winner = newBoard->calculateWinner();

			if (player == 1) {
				if (winner) wins[(c * boardsPerThread) + i]++;
				else if (!winner) wins[(c * boardsPerThread) + i]--;
			}
			else {
				if (!winner) wins[(c * boardsPerThread) + i]++;
				else if (winner) wins[(c * boardsPerThread) + i]--;
			}
		}
	}

	return wins;
}
