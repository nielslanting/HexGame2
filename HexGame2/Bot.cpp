#include "Bot.h"

Bot::Bot()
{
	ConcurentThreadsSupported = std::thread::hardware_concurrency();
	if (ConcurentThreadsSupported < 4) ConcurentThreadsSupported = 4;
}


Bot::~Bot()
{
}

int Bot::calculateBestPosition(const HexBoard& hexBoard, short player) const
{
	std::cout << "Calculating move..." << std::endl;
	std::cout << "Running on: " << ConcurentThreadsSupported << " threads." << std::endl;

	std::vector<short> available = hexBoard.getAvailableMoves();

	// Store the results
	std::vector<int> wins(available.size(), 0);

	std::clock_t begin = clock();
	std::vector<std::future<MonteResult>> results;

	for (auto i = 0; i < ConcurentThreadsSupported; i++) {
		results.push_back(std::async(std::launch::async, &Bot::monteCarlo, this, hexBoard, available, player, Strength));			
	}

	// Merge the results
	int sum = 0;

	for (auto&& future : results) {
		MonteResult result = future.get();

		sum += result.count;
		for (auto i = 0; i < result.wins.size(); i++) {
			wins[i] += result.wins[i];
		}
	}

	clock_t end = clock();
	double diff = double(end - begin) / CLOCKS_PER_SEC;
	double timePerCalculation = (diff / sum) * 1000;
	double calculationsPerMs = sum / (diff * 1000);

	std::cout << "Calculation time: " << diff << std::endl;
	std::cout << "Calculations done: " << sum << std::endl;
	std::cout << "Time per calculation: " << timePerCalculation << " ms" << std::endl;
	std::cout << "Calculations per ms: " << calculationsPerMs << std::endl;

	int pos = std::distance(wins.begin(), std::max_element(wins.begin(), wins.end()));

	std::cout << "Position: " << pos << std::endl;

	return available.at(pos);
}

MonteResult Bot::monteCarlo(const HexBoard& board, std::vector<short> available, short player, int timeout) const
{
	int counter = 0;

	auto begin_time = std::chrono::high_resolution_clock::now();

	std::vector<int> wins(available.size(), 0);

	while (true) {


		// Check the elapsed time
		auto current_time = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - begin_time).count();
		if (elapsed > timeout) {
			break;
		}

		for (auto i = 0; i < available.size(); i++) {
			HexBoard newBoard(board);
			newBoard.makeMove(player, available[i]);
			newBoard.fillBoardRandom();

			auto winner = newBoard.calculateWinner();

			if (player == 1) {
				if (winner) wins[i]++;
				else wins[i]--;
			}
			else {
				if (!winner) wins[i]++;
				else wins[i]--;
			}

			counter++;
		}
	}

	MonteResult result;
	result.count = counter;
	result.wins = wins;

	return result;
}

void Bot::setStrength(unsigned strength)
{
	Strength = strength;
}

