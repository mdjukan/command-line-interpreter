#include "Replace.h"
#include "../Utils.h"
#include "../exceptions/InstructionError.h"
#include "../exceptions/RuntimeError.h"
#include "Executable.h"
#include <sstream>

Replace::Replace(const std::string& instruction, std::vector<Token> tokens)
    : Executable(instruction, tokens) {
    tokens.erase(tokens.begin());

    if (tokens.empty()) {
        incorrect_usage_error();
    }

    if (tokens.front().type == TokenType::WORD) {
        redirect_in(tokens.front().get_value(instruction));
        tokens.erase(tokens.begin());
    }

    if (!tokens.empty() && tokens.front().type == TokenType::STRLIT) {
        m_what = Utils::strlit_to_string(instruction, tokens.front());
        tokens.erase(tokens.begin());
    } else {
        incorrect_usage_error();
    }

    if (!tokens.empty() && tokens.front().type == TokenType::STRLIT) {
        m_with = Utils::strlit_to_string(instruction, tokens.front());
        tokens.erase(tokens.begin());
    }

    handle_redirects(instruction, tokens);
}

std::string Replace::usage() { return "tr [argument] what [with]"; }

void Replace::execute() {
    std::string line;
    while (std::getline(*m_in, line)) {
        std::string::size_type k = 0;
        while (true) {
            k = line.find(m_what, k);
            if (k == std::string::npos) {
                break;
            }

            line.replace(k, m_what.size(), m_with);
            k += m_with.size();
        }

        (*m_out) << line << std::endl;
    }
}
