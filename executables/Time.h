#pragma once
#include "Executable.h"

class Time : public Executable {
    public:
    Time(const std::string& instruction, std::vector<Token> tokens);
    std::string current_time();
    std::string usage() override;
    void execute() override;
};
