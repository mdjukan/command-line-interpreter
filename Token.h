#pragma once
#include <string>

enum TokenType {
    WORD,   // instructionukcija ili ime fajla, moze da sadrzi [a-zA-Z0-9], . , _
    STRLIT, // string literal "...", unutar navodnika sta god
    OPTION, // opcija, crtica i nakon [a-zA-Z0-9] , npr. -w, -c, -n267, ...
    PIPE,   // |
    LT,     // <
    GT,     // >
    GGT,    // >>
};

struct Token {
    enum TokenType type;
    std::size_t start_idx;
    std::size_t end_idx;

    Token(enum TokenType type, std::size_t start_idx, std::size_t end_idx)
        : type(type), start_idx(start_idx), end_idx(end_idx) {}

    std::string get_value(const std::string& instruction) const {
        return instruction.substr(start_idx, end_idx - start_idx + 1);
    }
};
