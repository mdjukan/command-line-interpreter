#pragma once
#include "Executable.h"

class Date : public Executable {
    public:
    Date(const std::string& instruction, std::vector<Token> tokens);
    std::string current_date();
    std::string usage() override;
    void execute() override;
};
