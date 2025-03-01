#include "Echo.h"
#include "../Token.h"
#include "../Utils.h"
#include "../exceptions/InstructionError.h"
#include "../exceptions/RuntimeError.h"
#include "Executable.h"
#include <sstream>

Echo::Echo(const std::string& instruction, std::vector<Token> tokens)
    : Executable(instruction, tokens) {
    tokens.erase(tokens.begin());

    if (!tokens.empty() && tokens.front().type == TokenType::WORD) {
        redirect_in(tokens.front().get_value(instruction));
        tokens.erase(tokens.begin());
    } else if (!tokens.empty() && tokens.front().type == TokenType::STRLIT) {
        set_in(Utils::strlit_to_sstream(instruction, tokens.front()));
        tokens.erase(tokens.begin());
    }

    handle_redirects(instruction, tokens);
}

std::string Echo::usage() { return "echo [argument]"; }

void Echo::execute() {
    std::string line;
    while (std::getline(*m_in, line)) {
        (*m_out) << line << std::endl;
    }
}
