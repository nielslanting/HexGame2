#include "HexGame.h"
#include "HexBoard.h"

HexGame::HexGame(const HexGame& other)
{
	// deep copy
	Board = new HexBoard(*other.Board);

	// shallow copy (they both point to same object)
	Dimension = other.Dimension;
	Turn = other.Turn;
	PieRuleUsed = other.PieRuleUsed;
}


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
			throw std::invalid_argument("Can't use pie rule");
		}

		executed = true;
	}

	// Let the BOT make a move
	else if (input == "BOT") {
		std::cout << "BEEP BOOP";
		executed = true;
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

		executed = true;
	}

	this->calculateWinner();

	return executed;
}

int HexGame::calculateWinner()
{
	std::map<int, bool> visited = std::map<int, bool>();

	// Vertical(red) check
	for (int i = 0; i < Dimension; i++) {
		// Skip starting positions that aren't red
		if (Board->Board[i] != 1) continue;

		// Skip positions we have visited in previous itterations
		if (visited.find(i) != visited.end()) continue;

		bool redWon = hasWon(i, 1, (Dimension*Dimension) - Dimension, (Dimension*Dimension), visited);

		if (redWon) return 1;
	}

	return 0;
}

bool HexGame::hasWon(int currentPosition, int player, int min, int max, std::map<int, bool> &visited)
{
	// TODO: Do conditionals before calling the function, reducing stackframes
	// We already checked this node
	if (visited.find(currentPosition) != visited.end()) return false;
	else visited[currentPosition] = true;

	// Check if the position is within the bounds of the vector
	if (currentPosition < 0 && currentPosition > Board->Board.size()) return false;

	// Check if its the player's node
	if (Board->Board[currentPosition] != player) return false;

	// We are in the position we looked for
	if (currentPosition >= min && currentPosition <= max) {
		return true;
	}

	// Calculate the positions of other nodes
	int top1 = currentPosition - Dimension;
	int top2 = currentPosition - Dimension + 1;
	int left = currentPosition - 1;
	int right = currentPosition + 1;
	int bottom1 = currentPosition + Dimension - 1;
	int bottom2 = currentPosition + Dimension;

	// Check if the position contains the correct player
	if (hasWon(top1, player, min, max, visited)) return true;
	if (hasWon(top2, player, min, max, visited)) return true;
	if (hasWon(left, player, min, max, visited)) return true;
	if (hasWon(right, player, min, max, visited)) return true;
	if (hasWon(bottom1, player, min, max, visited)) return true;
	if (hasWon(bottom2, player, min, max, visited)) return true;

 	return false;
}
