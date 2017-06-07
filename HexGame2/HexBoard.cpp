#include "HexBoard.h"

HexBoard::HexBoard(int dimension) : Dimension(dimension)
{
	Board = std::vector<short>((dimension*dimension), 0);
}

HexBoard::~HexBoard(void)
{
}

void HexBoard::draw()
{
	HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	std::cout << std::endl;

	// Display the top guide row
	std::cout << " ";
	for (int i = 0; i < Dimension; i++)
	{
		std::cout << std::to_string(i + 1) + ' ';
	}

	// Draw the rest of the board
	std::string buffer = "";
	for (int y = 0; y < Dimension; y++)
	{
		std::cout << std::endl;
		std::cout << buffer;
		buffer = buffer + ' ';

		for (int x = -1; x < Dimension; x++)
		{
			// Reset the color
			SetConsoleTextAttribute(hConsole, 7);

			// Display the left guide cell
			if (x == -1) {
				std::cout << (char)(y + 65);
				std::cout << ' ';
				continue;
			}
	
			switch (Board[(y * Dimension) + x])
			{
				case 0: std::cout << '.'; break;
				case 1: 
					SetConsoleTextAttribute(hConsole, 12);
					std::cout << 'R'; 
					break;
				case 2: 
					SetConsoleTextAttribute(hConsole, 11);
					std::cout << 'B'; 
					break;
				case 3: std::cout << '!'; break;
			}

			std::cout << ' ';
		}
	}
	
	// Reset the color
	SetConsoleTextAttribute(hConsole, 7);

	std::cout << std::endl;
}

std::vector<short> HexBoard::getAvailableMoves() const
{
	std::vector<short> available;
	for (int i = 0; i < Dimension*Dimension; i++)
	{
		if (Board[i] == 0)
		{
			available.push_back(i);
		}
	}

	return available;
}

void HexBoard::fillBoardRandom(bool rawTurn)
{
	bool turn = rawTurn || false;
	std::vector<short> available = getAvailableMoves();
	while (!available.empty())
	{
		turn = !turn;

		int select = rand() % available.size();
		int number = available.at(select);
		available.erase(available.begin() + select);

		if (turn)
			Board[number] = 1;
		else
			Board[number] = 2;
	}
}

bool HexBoard::makeMove(short player, int position)
{
	if (position > Dimension*Dimension) return false;
	if (position < 0) return false;
	if (Moves.find(position) != Moves.end()) return false;
	if (player > 2) return false;

	Board[position] = player;
	Moves[position] = player;

	return true;
}

bool HexBoard::makeMove(short player, std::string move)
{
	int movePosition = (int)move[0] - 65;
	movePosition += (-1 + atoi(move.substr(1, move.length() - 1).c_str())) * 11;

	if (makeMove(player, movePosition))
		return true;

	return false;
}

bool HexBoard::invert()
{
	for (std::vector<short>::iterator it = Board.begin(); it != Board.end(); ++it)
	{
		if (*it == 2) *it = 1;
		else if (*it == 1) *it = 2;
	}

	return true;
}

int HexBoard::calculateWinner()
{
	std::map<int, bool> visited = std::map<int, bool>();

	// Vertical(red) check
	for (int i = 0; i < Dimension; i++) {
		// Skip starting positions that aren't red
		if (Board[i] != 1) continue;

		// Skip positions we have visited in previous itterations
		if (visited.find(i) != visited.end()) continue;

		bool redWon = hasWon(i, 1, (Dimension*Dimension) - Dimension, (Dimension*Dimension), visited);

		if (redWon) return 1;
	}

	return 0;
}

bool HexBoard::hasWon(int currentPosition, int player, int min, int max, std::map<int, bool> &visited)
{
	// We already checked this node
	if (visited.find(currentPosition) != visited.end()) return false;
	else visited[currentPosition] = true;

	// Check if the position is within the bounds of the vector
	if (currentPosition < 0 && currentPosition > Board.size()) return false;

	// Check if its the player's node
	if (Board[currentPosition] != player) return false;

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

