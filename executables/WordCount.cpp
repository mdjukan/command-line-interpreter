#include "WordCount.h"
#include "../Utils.h"
#include "../exceptions/InstructionError.h"
#include "../exceptions/RuntimeError.h"
#include "Executable.h"

WordCount::WordCount(const std::string& instruction, std::vector<Token> tokens)
    : Executable(instruction, tokens) {
    tokens.erase(tokens.begin());

    if (tokens.empty() || tokens.front().type != TokenType::OPTION) {
        incorrect_usage_error();
    }

    if (tokens.front().get_value(instruction) == "-w") {
        m_option = WCOption::WORDS;
    } else if (tokens.front().get_value(instruction) == "-c") {
        m_option = WCOption::CHARS;
    } else {
        throw new InstructionError(instruction, tokens.front().start_idx, tokens.front().end_idx,
                                   "Error - invalid option:");
    }

    tokens.erase(tokens.begin());

    if (!tokens.empty() && tokens.front().type == TokenType::WORD) {
        redirect_in(tokens.front().get_value(instruction));
        tokens.erase(tokens.begin());
    } else if (!tokens.empty() && tokens.front().type == TokenType::STRLIT) {
        set_in(Utils::strlit_to_sstream(instruction, tokens.front()), true);
        tokens.erase(tokens.begin());
    }

    handle_redirects(instruction, tokens);
}

std::string WordCount::usage() {
    return "wc (-w|-c) [argument]";
}

void WordCount::execute() {
    switch (m_option) {
    case WCOption::WORDS:
        (*m_out) << word_count() << std::endl;
        break;
    case WCOption::CHARS:
        (*m_out) << char_count() << std::endl;
        break;
    }
}

std::size_t WordCount::word_count() {
    std::size_t total = 0;
    bool in_word = false;
    char c;

    while (true) {
        m_in->get(c);

        if (m_in->eof()) {
            break;
        }

        if (in_word) {
            if (std::isspace(c)) {
                in_word = false;
            }
        } else {
            if (!std::isspace(c)) {
                in_word = true;
                total += 1;
            }
        }
    }

    m_in->clear();
    return total;
}

std::size_t WordCount::char_count() {
    std::size_t total = 0;
    char c;

    while (true) {
        m_in->get(c);

        if (m_in->eof()) {
            break;
        }

        total += 1;
    }

    m_in->clear();
    return total;
}
