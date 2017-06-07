#include "main.h"

/* Entrypoint */
int main() {
	new Main();
	return 0;
}

Main::Main()
{
	// Fetch the starting player
	std::string startInput = "";
	std::cout << "Does red start? (Y|N)" << std::endl;
	std::cin >> startInput;

	// Convert start input to boolean
	std::transform(startInput.begin(), startInput.end(), startInput.begin(), ::toupper);

	std::transform(startInput.begin(), startInput.end(), startInput.begin(), ::toupper);
	bool start = startInput == "N" ? false : true;

	// Fetch the use of the pie rule
	std::string pieRuleInput = "";
	std::cout << "Is the pie rule allowed? (Y|N)" << std::endl;
	std::cin >> pieRuleInput;

	// Convert start input to boolean
	std::transform(pieRuleInput.begin(), pieRuleInput.end(), pieRuleInput.begin(), ::toupper);
	bool pieRule = pieRuleInput == "N" ? false : true;

	// Create the board
	HexGame* hexGame = new HexGame(11, start, pieRule);

	// Push the initial state
	UndoQueue.push_back(new HexGame(*hexGame));

	std::string input = "";	
	while (input != "QUIT") {
		// Clear the screen
		system("cls");

		std::cout << "HexGame by Niels Lanting" << std::endl;
		std::cout << "Commands: " << std::endl;
		std::cout << "- UNDO: Undos the previous command." << std::endl;
		std::cout << "- REDO: Redos the previous command." << std::endl;
		std::cout << "- RANDOM: Fills the board randomly." << std::endl;
		std::cout << "- PIE: Applies pie rule." << std::endl;
		std::cout << "- BOT: A bot will make a move." << std::endl;
		std::cout << "- STRENGTH {number}: How long the bot can calculate(in ms)." << std::endl;
		std::cout << "- {row}{column}: (Example A1) Places a stone." << std::endl;
		std::cout << std::endl;

		std::cout << "Last input: ";
		std::cout << input << std::endl;

		if (input == "UNDO" ) {
			if (UndoQueue.size() >= 2) {
				// Pop last value from the queue
				HexGame* last = UndoQueue.back();
				UndoQueue.pop_back();
				RedoQueue.push_back(last);

				// Add it to the redo queue
				hexGame = UndoQueue.back();
			}
		}
		else if (input == "REDO") {
			if (RedoQueue.size() >= 1) {
				// Pop last value from the queue
				HexGame* mem = RedoQueue.back();
				RedoQueue.pop_back();

				// Add it to the undo queue
				UndoQueue.push_back(mem);

				hexGame = mem;
			}
		}
		else
		{
			// Send the input to the Game Instance
			if (hexGame->input(input)) {
				// Save the state
				UndoQueue.push_back(new HexGame(*hexGame));
			}
		}

		// Draw the board
		hexGame->draw();

		// Get the new input and set it to uppercase
		std::getline(std::cin, input);
		std::transform(input.begin(), input.end(), input.begin(), ::toupper);	
	}

	delete hexGame;
}

Main::~Main()
{
}
