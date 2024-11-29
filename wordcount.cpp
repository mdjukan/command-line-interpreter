#include "wordcount.h"
#include <sstream>
#include <fstream>
#include <iostream>

WordCount::WordCount(COUNT_OPTION co) : co(co) {
	input = nullptr;
}

WordCount::WordCount(COUNT_OPTION co, std::string arg) : co(co) {
	if (arg[0]=='"') {
		input = new std::stringstream(arg.substr(1, arg.size()-2));
	} else {
		input = new std::ifstream(arg);
	}
}

size_t WordCount::count_chars() {
	char c;
	size_t num_char = 0;
	while (true) {
		c = input->get();
		if (input->eof()) {
			break;
		}

		num_char += 1;
	}

	return num_char;
}

size_t WordCount::count_words() {
	char c;
	size_t num_word = 0;
	bool last_is_space = true;
	while (true) {
		c = input->get();
		if (input->eof()) {
			break;
		}

		if (std::isspace(c)) {
			last_is_space = true;
		} else {
			if (last_is_space) {
				num_word += 1;
			}

			last_is_space = false;
		}
	}

	return num_word;
}

//TODO input i output promeni na in i out?
void WordCount::exec() {
	if (input==nullptr) { //zeli da citam sa cin-a dok se unese EOF
		std::string line;
		std::string lines;
		while (true) {
			std::getline(std::cin, line);
			if (line=="EOF") {
				break;
			}

			lines += line + '\n';
		}

		input = new std::stringstream(lines);
	}

	std::ifstream *file_stream = dynamic_cast<std::ifstream*>(input);
	if (file_stream!=nullptr) {
		if (!file_stream->is_open()) {
			(*output) << "Can't open file!" << std::endl;
			return;
		}
	}

	if (co==WORDS) {
		(*output) << count_words() << std::endl;
	} else {
		(*output) << count_chars() << std::endl;
	}
}
