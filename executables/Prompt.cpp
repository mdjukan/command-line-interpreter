#include "Prompt.h"
#include "../CLI.h"
#include "../exceptions/InstructionError.h"
#include "../exceptions/RuntimeError.h"
#include "Executable.h"

Prompt::Prompt(const std::string& instruction, std::vector<Token> tokens)
    : Executable(instruction, tokens) {
    tokens.erase(tokens.begin());

    if (tokens.empty() || tokens.front().type != TokenType::WORD) {
        incorrect_usage_error();
    }

    m_prompt = tokens.front().get_value(instruction);
    tokens.erase(tokens.begin());

    handle_redirects(instruction, tokens);
}

std::string Prompt::usage() {
    return "prompt argument";
}

void Prompt::execute() {
    CLI::prompt = m_prompt;
}
