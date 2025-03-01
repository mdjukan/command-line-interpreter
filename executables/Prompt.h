#pragma once
#include "Executable.h"

class Prompt : public Executable {
    private:
    std::string m_prompt;

    public:
    Prompt(const std::string& instruction, std::vector<Token> tokens);
    void execute() override;
    std::string usage() override;
};
