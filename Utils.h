#pragma once
#include "Token.h"
#include <iostream>
#include <sstream>
#include <string>

namespace Utils {
const int INSTRUCTION_LENGTH = 512;

std::istream& read_instruction(std::istream* in, std::string& instruction);
std::stringstream* strlit_to_sstream(const std::string& instruction, const Token& token);
std::string strlit_to_string(const std::string& instruction, const Token& token);
}; // namespace Utils
