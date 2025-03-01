#pragma once
#include "Executable.h"

enum WCOption {
    WORDS,
    CHARS,
};

class WordCount : public Executable {
    private:
    WCOption m_option;

    public:
    WordCount(const std::string& instruction, std::vector<Token> tokens);
    std::string usage() override;
    void execute() override;
    std::size_t word_count();
    std::size_t char_count();
};
