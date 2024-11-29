#pragma once
#include "executable.h"
#include <iostream>

class Echo : public Executable {
public:
	Echo();
	Echo(std::string arg);

	~Echo()
	{
		if (input!=&std::cin) {
			delete input;
		}
	}

	void exec() override;
};
