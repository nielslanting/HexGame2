#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <fcntl.h>
#include "Memento.h"

class main
{
public:
	main();
	~main();
};

class Main
{
private:
	std::vector<HexGame*> UndoQueue;
	std::vector<HexGame*> RedoQueue;
public:
	Main();
	~Main();
};

