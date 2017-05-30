#include "Bot.h"

Bot::Bot()
{
}


Bot::~Bot()
{
}

int Bot::calculateBestPosition(const HexBoard& hexBoard, int player) const
{
	std::vector<short> availableMoves = hexBoard.getAvailableMoves();

	// Store the results
	std::vector<int> wins;
	std::vector<HexBoard*>boards;

	// Create a board for each posible move, and set the available move
	for (std::vector<short>::iterator it = availableMoves.begin(); it != availableMoves.end(); ++it) {
		HexBoard* newBoard = new HexBoard(hexBoard);
		newBoard->makeMove(player, *it);
		boards.push_back(newBoard);
		wins.push_back(0);
	}

	for (int i = 0; i < availableMoves.size(); i++) {
		for (int j = 0; j < 50; j++) {
			HexBoard* newBoard = new HexBoard(*boards[i]);
			newBoard->fillBoardRandom();

			if (newBoard->calculateWinner() && player == 1) wins[i]++;
			else if (!newBoard->calculateWinner() && player == 2) wins[i]++;
		}
	}


	int pos = std::distance(wins.begin(), std::max_element(wins.begin(), wins.end()));

	return availableMoves.at(pos);
}
