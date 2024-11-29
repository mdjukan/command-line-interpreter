#pragma once
#include "executable.h"

enum COUNT_OPTION {
	WORDS,
	CHARS
};

class WordCount : public Executable {
	public:
		COUNT_OPTION co;
		WordCount(COUNT_OPTION co);
		WordCount(COUNT_OPTION co, std::string arg);
		size_t count_chars();
		size_t count_words();
		void exec() override;
		~WordCount() {
			delete input;
		}
};
