#pragma once
#include <string>
#include <iostream>
#include "executable.h"

class CommandLineInterpreter
{
private:
	static const size_t instr_len_limit;
public:
	CommandLineInterpreter();
	void start();

private:
	std::string m_prompt;
	std::string read_instruction();
	Executable *parse_instruction(const std::string &instr);
};

