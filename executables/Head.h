#pragma once
#include "Executable.h"

class Head : public Executable {
    private:
    const std::size_t COUNT_LEN_LIMIT = 5;
    std::size_t m_count;

    public:
    Head(const std::string& instruction, std::vector<Token> tokens);
    void execute() override;
    std::string usage() override;
    bool valid_option(const std::string& option);
};
