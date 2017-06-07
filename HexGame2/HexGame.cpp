#include "HexGame.h"
#include "HexBoard.h"

HexGame::HexGame(const HexGame& other)
{
	// Deep copy
	Board = new HexBoard(*other.Board);

	// Shallow copy (they both point to same object)
	Dimension = other.Dimension;
	Turn = other.Turn;
	PieRuleUsed = other.PieRuleUsed;
	Robot = other.Robot;
}


HexGame::HexGame(int dimension) : Dimension(dimension), Board(new HexBoard(dimension)), Robot(new Bot())
{
}

HexGame::HexGame(int dimension, bool turn, bool pieRule) : Dimension(dimension), Turn(turn), PieRuleUsed(!pieRule), Board(new HexBoard(dimension)), Robot(new Bot())
{
}

HexGame::~HexGame()
{
	delete Board;
	delete Robot;
}

bool HexGame::applyPieRule() {

	if (PieRuleUsed) return false;

	int availableMoves = Dimension * Dimension;
	int emptyMoves = Board->getAvailableMoves().size();

	// Pie rule is used but it's not the first turn anymore
	if ((availableMoves - emptyMoves) != 1) return false;

	Board->invert();
	Turn = !Turn;
	PieRuleUsed = true;

	return true;
}

void HexGame::draw() {

	std::cout << std::endl;

	// Print the player who's turn it is
	std::string turn = Turn ? "RED" : "BLUE";
	std::cout << "TURN: " << turn;
	std::cout << std::endl;

	std::string pieRuleAvailable = (!PieRuleUsed && Board->Moves.size() <= 1) ? "YES" : "NO";
	std::cout << "PIE RULE AVAILABLE: " << pieRuleAvailable;
	std::cout << std::endl;

	Board->draw();
}

bool HexGame::input(const std::string &input)
{
	bool executed = false;

	// Apply pie rule, if we can't throw an exception
	if (input == "PIE") {
		if (!this->applyPieRule()) {
			std::cout << "Can't use pie rule." << std::endl;
		}
		else {
			executed = true;
		}
	}

	// Let the BOT make a move
	else if (input == "BOT") {
		
		int player = Turn ? 1 : 2;
		int move = Robot->calculateBestPosition(*Board, player);

		Board->makeMove(player, move);
		Turn = !Turn;

		executed = true;	
	}

	// Let the BOT make a move
	else if (input == "RANDOM") {
		Board->fillBoardRandom();
		executed = true;
	}

	// Set bot strength
	else if (std::regex_match(input, std::regex("STRENGTH [0-9]+"))) {

		// Calculate the strength
		std::smatch strengthMatch;
		std::regex_search(input, strengthMatch, std::regex("[0-9]+"));
		std::string rawStrength = strengthMatch[0];
		unsigned int strength = atoi(rawStrength.c_str()) - 1;

		Robot->setStrength(strength);

		std::cout << "Robot's strength is now: " << strength << " ms." << std::endl;
	}

	// Default move
	else if (std::regex_match(input, std::regex("[a-zA-Z]+[0-9]+")) || 
		std::regex_match(input, std::regex("[0-9]+[a-zA-Z]+"))){

		// Calculate the column
		std::smatch columnMatch;
		std::regex_search(input, columnMatch, std::regex("[a-zA-Z]+"));
		std::string rawColumn = columnMatch[0];
		unsigned int column = rawColumn.at(0) - 'A';

		// Calculate the row
		std::smatch rowMatch;
		std::regex_search(input, rowMatch, std::regex("[0-9]+"));
		std::string rawRow = rowMatch[0];
		unsigned int row = atoi(rawRow.c_str());

		// Calculate the move
		unsigned int move = (column * Dimension) + row;
		if (Board->Board[move] == 0) {
			Board->makeMove(Turn ? 1 : 2, move);
			Turn = !Turn;
		}

		executed = true;
	}


	this->Board->calculateWinner();

	return executed;
}


