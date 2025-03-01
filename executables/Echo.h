#pragma once
#include "Executable.h"

class Echo : public Executable {
    public:
    Echo(const std::string& instruction, std::vector<Token> tokens);
    std::string usage() override;
    void execute() override;
};
