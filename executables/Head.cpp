#include "Head.h"
#include "../exceptions/InstructionError.h"
#include "../exceptions/RuntimeError.h"
#include "Executable.h"
#include <sstream>

Head::Head(const std::string& instruction, std::vector<Token> tokens)
    : Executable(instruction, tokens) {
    tokens.erase(tokens.begin());

    if (tokens.empty() || tokens.front().type != TokenType::OPTION) {
        incorrect_usage_error();
    }

    std::string option = tokens.front().get_value(instruction);
    if (!valid_option(option)) {
        throw new InstructionError(instruction, tokens.front().start_idx, tokens.front().end_idx,
                                   "Error - invalid option:");
    }

    std::stringstream ss(option.substr(2));
    ss >> m_count;
    tokens.erase(tokens.begin());

    if (!tokens.empty() && tokens.front().type == TokenType::WORD) {
        redirect_in(tokens.front().get_value(instruction));
        tokens.erase(tokens.begin());
    }

    handle_redirects(instruction, tokens);
}

std::string Head::usage() { return "head -ncount [argument]"; }

void Head::execute() {
    std::string line;
    std::size_t line_count = 0;
    while (std::getline(*m_in, line) && line_count < m_count) {
        (*m_out) << line << std::endl;
        line_count += 1;
    }
}

bool Head::valid_option(const std::string& option) {
    if (option.substr(0, 2) != "-n") {
        return false;
    }

    std::string num = option.substr(2);
    if (num.empty() || num.size() > COUNT_LEN_LIMIT) {
        return false;
    }

    for (std::size_t i = 0; i < num.size(); i++) {
        if (!std::isdigit(num[i])) {
            return false;
        }
    }

    return true;
}
