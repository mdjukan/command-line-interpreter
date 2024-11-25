#pragma once

#include <sstream>

class Executable {
	public:
		std::istream *input;
		std::ostream *output;
		virtual void exec() = 0;

		Executable() : input(nullptr), output(nullptr) {}
		virtual ~Executable() {}

		void setInput(std::istream *_input) {
			input = _input;
		}

		void setOutput(std::ostream *_output) {
			output = _output;
		}
};
