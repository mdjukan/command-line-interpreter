#include "commandlineinterpreter.h"
#include "wordcount.h"
#include "time.h"
#include "date.h"
#include "touch.h"
#include "echo.h"
#include <vector>
#include <sstream>
#include <iostream>

const size_t CommandLineInterpreter::instr_len_limit = 512;

CommandLineInterpreter::CommandLineInterpreter() : m_prompt("$") {}

void CommandLineInterpreter::start() {
	for (;;) {
		std::cout << m_prompt << " ";

		std::string instr = read_instruction();
		Executable *exe = parse_instruction(instr);
		exe->exec();
		delete exe;
	}
}

std::string CommandLineInterpreter::read_instruction() {
	std::string instr;
	std::string par;
	//while (std::getline(std::cin, par, '\n')) { instr += par; }
	std::getline(std::cin, instr, '\n');
	return instr.substr(0, instr_len_limit);
}

std::vector<std::string> split_to_tokens(const std::string &instr) {
        std::vector<std::string> result;
        std::stringstream s(instr);
	std::string word;
	bool in_string = false;

        while (true) {
		char c = s.get();
                if (!s) {
                        break;
                }

		if (c==' ') {
			if (in_string) {
				word.push_back(c);
			} else {
				result.push_back(word);
				word.clear();
			}
		} else {
			word.push_back(c);
		}

		if (c=='"') {
			in_string = !in_string;
		}
        }

	if (word.size()!=0) {
		result.push_back(word);
	}

        return result;
}

Executable *CommandLineInterpreter::parse_instruction(const std::string &instr) {
	std::vector<std::string> tokens = split_to_tokens(instr);
	if (tokens[0]=="wc") {
		if (tokens[1]=="-w") {
			Executable *exe;
			if (tokens.size()==2) {
				exe = new WordCount(COUNT_OPTION::WORDS);
			} else {
				exe = new WordCount(COUNT_OPTION::WORDS, tokens[2]);
			}

			exe->setOutput(&std::cout);
			return exe;
		} else if (tokens[1]=="-c") {
			Executable *exe;
			if (tokens.size()==2) {
				exe = new WordCount(COUNT_OPTION::CHARS);
			} else {
				exe = new WordCount(COUNT_OPTION::CHARS, tokens[2]);
			}

			exe->setOutput(&std::cout);
			return exe;
		}
	} else if (tokens[0]=="time") {
		Executable *exe = new Time();
		exe->setOutput(&std::cout);
		return exe;
	}
	else if (tokens[0] == "date")
	{
		Executable* exe = new Date();
		exe->setOutput(&std::cout);
		return exe;

	}
	else if (tokens[0] == "echo")
	{
		Executable *exe;
		if (tokens.size()==1) { //echo bez argumenta
			exe = new Echo();
		} else { //echo sa argumentom
			exe = new Echo(tokens[1]);
		}

		exe->setOutput(&std::cout);
		return exe;

	}
	else if (tokens[0] == "touch")
	{
		Executable* exe = new Touch(tokens[1]);
		exe->setOutput(&std::cout);
		return exe;
	}

	return nullptr;
}
