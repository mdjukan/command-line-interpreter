#include "echo.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

Echo::Echo() {
	input = &std::cin;
}

Echo::Echo(std::string arg)
{
	if (arg[0] == '"') {
		input = new std::stringstream(arg.substr(1, arg.size() - 2));
	} else {
		input = new std::ifstream(arg);
	}
}

void Echo::exec()
{
	if (input==&std::cin) {
		std::vector<std::string> lines;
		std::string line;
		while (true) {
			std::getline(std::cin, line); //nece u line upisati \n
			if (line=="EOF") {
				break;
			}

			lines.push_back(line);
		}

		for (std::string &line : lines) {
			(*output) << line << std::endl;
		}
	} else {
		char c;
		while (true) {
			c = input->get();
			if (input->eof()) { break; }
			(*output)<< c;  
		}
		(*output) << std::endl;
	}
}
