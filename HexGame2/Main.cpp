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
	Memento* mem = new Memento(new HexGame(*hexGame));
	UndoQueue.push_back(mem);

	std::string input = "";	
	while (input != "QUIT") {
		// Clear the screen
		system("cls");

		std::cout << "Last input: ";
		std::cout << input << std::endl;

		if (input == "UNDO" ) {
			if (UndoQueue.size() >= 2) {
				// Pop last value from the queue
				Memento* last = UndoQueue.back();
				UndoQueue.pop_back();
				RedoQueue.push_back(last);

				// Add it to the redo queue
				Memento* mem = UndoQueue.back();
				hexGame = mem->getState();
			}
		}
		else if (input == "REDO") {
			if (RedoQueue.size() >= 1) {
				// Pop last value from the queue
				Memento* mem = RedoQueue.back();
				RedoQueue.pop_back();

				// Add it to the undo queue
				UndoQueue.push_back(mem);

				hexGame = mem->getState();
			}
		}
		else
		{
			// Send the input to the Game Instance
			if (hexGame->input(input)) {
				// Save the state
				Memento* mem = new Memento(new HexGame(*hexGame));
				UndoQueue.push_back(mem);
			}
		}

		// Draw the board
		hexGame->draw();

		// Get the new input and set it to uppercase
		std::cin >> input;
		std::transform(input.begin(), input.end(), input.begin(), ::toupper);	
	}

	delete hexGame;
}

Main::~Main()
{
}
