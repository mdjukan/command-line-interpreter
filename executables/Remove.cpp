#include "Remove.h"
#include "../exceptions/InstructionError.h"
#include "../exceptions/RuntimeError.h"
#include "Executable.h"
#include <filesystem>

Remove::Remove(const std::string& instruction, std::vector<Token> tokens)
    : Executable(instruction, tokens) {
    tokens.erase(tokens.begin());

    if (tokens.empty() || tokens.front().type != TokenType::WORD) {
        incorrect_usage_error();
    }

    m_file_name = tokens.front().get_value(instruction);
    tokens.erase(tokens.begin());

    handle_redirects(instruction, tokens);
}

std::string Remove::usage() {
    return "rm argument";
}

void Remove::execute() {
    if (std::filesystem::exists(m_file_name)) {
        if (std::remove(m_file_name.c_str())) {
            throw new RuntimeError("Error - couldn't remove file " + m_file_name);
        }
    } else {
        throw new RuntimeError("Error - file " + m_file_name + " doesn't exist");
    }
}
