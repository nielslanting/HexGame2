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
	std::vector<Memento*> UndoQueue;
	std::vector<Memento*> RedoQueue;
public:
	Main();
	~Main();
};

