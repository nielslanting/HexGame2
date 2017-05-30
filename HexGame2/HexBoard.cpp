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
			// Display the left guide cell
			if (x == -1) {
				
				std::cout << (char)(y + 65);
				std::cout << ' ';
				continue;
			}

			switch (Board[(y * Dimension) + x])
			{
				case 0: std::cout << '.'; break;
				case 1: std::cout << 'R'; break;
				case 2: std::cout << 'B'; break;
				case 3: std::cout << '!'; break;
			}

			std::cout << ' ';
		}
	}
	

	std::cout << std::endl;
}

std::vector<short> HexBoard::getAvailableMoves()
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

void HexBoard::fillBoardRandom()
{
	std::vector<short> available = getAvailableMoves();
	bool turn = false;
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

