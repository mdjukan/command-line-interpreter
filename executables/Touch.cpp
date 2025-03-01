#include "Touch.h"
#include "../exceptions/InstructionError.h"
#include "../exceptions/RuntimeError.h"
#include "Executable.h"
#include <filesystem>
#include <fstream>

Touch::Touch(const std::string& instruction, std::vector<Token> tokens)
    : Executable(instruction, tokens) {
    tokens.erase(tokens.begin());

    if (tokens.empty() || tokens.front().type != TokenType::WORD) {
        incorrect_usage_error();
    }

    m_file_name = tokens.front().get_value(instruction);
    tokens.erase(tokens.begin());

    handle_redirects(instruction, tokens);
}

std::string Touch::usage() { return "touch argument"; }

void Touch::execute() {
    if (std::filesystem::exists(m_file_name)) {
        throw new RuntimeError("Error - file " + m_file_name + " already exists");
    } else {
        std::ofstream ofs(m_file_name);
    }
}
