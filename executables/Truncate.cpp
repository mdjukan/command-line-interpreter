#include "Truncate.h"
#include "../exceptions/InstructionError.h"
#include "../exceptions/RuntimeError.h"
#include "Executable.h"
#include <filesystem>
#include <fstream>

Truncate::Truncate(const std::string& instruction, std::vector<Token> tokens)
    : Executable(instruction, tokens) {
    tokens.erase(tokens.begin());

    if (tokens.empty() || tokens.front().type != TokenType::WORD) {
        incorrect_usage_error();
    }

    m_file_name = tokens.front().get_value(instruction);
    tokens.erase(tokens.begin());

    handle_redirects(instruction, tokens);
}

std::string Truncate::usage() { return "truncate argument"; }

void Truncate::execute() {
    if (std::filesystem::exists(m_file_name)) {
        std::ofstream(m_file_name, std::ios::trunc);
    } else {
        throw new RuntimeError("Error - file " + m_file_name + " doesn't exist");
    }
}
