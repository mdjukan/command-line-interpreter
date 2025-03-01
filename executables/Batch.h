#pragma once
#include "Executable.h"

class Batch : public Executable {
    public:
    Batch(const std::string& instruction, std::vector<Token> tokens);
    std::string usage() override;
    void execute() override;
};
