#include "HexGame.h"
#include "HexBoard.h"


HexGame::HexGame(int dimension) : Dimension(dimension), Board(new HexBoard(dimension))
{
}

HexGame::HexGame(int dimension, bool turn, bool pieRule) : Dimension(dimension), Turn(turn), PieRuleUsed(!pieRule), Board(new HexBoard(dimension))
{
}

HexGame::~HexGame()
{
	delete Board;
}

bool HexGame::applyPieRule() {

	if (PieRuleUsed) return false;

	int availableMoves = Dimension * Dimension;
	int emptyMoves = Board->getAvailableMoves().size();

	// Pie rule is used but it's not the first turn anymore
	if ((availableMoves - emptyMoves) > 1) return false;

	Board->invert();
	Turn = !Turn;
	PieRuleUsed = true;

	return true;
}

void HexGame::draw() {
	std::cout << std::endl;

	// Print the player who's turn it is
	std::string turn = Turn ? "BLUE" : "RED";
	std::cout << "TURN: " << turn;
	std::cout << std::endl;

	Board->draw();
}

void HexGame::input(const std::string &input)
{
	// Apply pie rule, if we can't throw an exception
	if (input == "PIE") {
		if (!this->applyPieRule()) {
			throw std::invalid_argument("Can't use pie rule");
		}
	}

	// Let the BOT make a move
	else if (input == "BOT") {
		std::cout << "BEEP BOOP";
	}

	// Default move
	else if (std::regex_match(input, std::regex("[a-zA-Z][0-9]")) || 
		std::regex_match(input, std::regex("[0-9][a-zA-Z]"))){

		// Calculate the column
		std::smatch columnMatch;
		std::regex_search(input, columnMatch, std::regex("[a-zA-Z]{1}"));
		std::string rawColumn = columnMatch[0];
		unsigned int column = rawColumn.at(0) - 'A';

		// Calculate the row
		std::smatch rowMatch;
		std::regex_search(input, rowMatch, std::regex("[0-9]"));
		std::string rawRow = rowMatch[0];
		unsigned int row = atoi(rawRow.c_str()) - 1;

		// Calculate the move
		unsigned int move = (column * Dimension) + row;
		if (Board->Board[move] == 0) {
			Board->makeMove(Turn ? 1 : 2, move);
			Turn = !Turn;
		}
	}

	
}
