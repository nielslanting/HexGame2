#include "main.h"
#include "HexGame.h"

/* Entrypoint */
int main() {
	new Main();
	return 0;
}

Main::Main()
{
	// Fetch the starting player
	std::string startInput = "";
	std::cout << "Who starts? (red|blue)" << std::endl;
	std::cin >> startInput;

	// Convert start input to boolean
	std::transform(startInput.begin(), startInput.end(), startInput.begin(), ::toupper);
	bool start = startInput == "RED" ? false : true;

	// Fetch the use of the pie rule
	std::string pieRuleInput = "";
	std::cout << "Is the pie rule allowed ? (Y|N)" << std::endl;
	std::cin >> pieRuleInput;

	// Convert start input to boolean
	std::transform(pieRuleInput.begin(), pieRuleInput.end(), pieRuleInput.begin(), ::toupper);
	bool pieRule = pieRuleInput == "N" ? false : true;

	// Create the board
	HexGame hexGame(11, start, pieRule);

	std::string input = "";	
	while (input != "QUIT") {
		// Clear the screen
		system("cls");

		std::cout << "Last input: ";
		std::cout << input << std::endl;
		std::cout << "Input: " << std::endl;;

		// Send the input to the Game Instance
		hexGame.input(input);

		// Draw the board
		hexGame.draw();

		// Get the new input and set it to uppercase
		std::cin >> input;
		std::transform(input.begin(), input.end(), input.begin(), ::toupper);
	}
}

Main::~Main()
{
}
