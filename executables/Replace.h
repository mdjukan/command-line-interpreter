#pragma once
#include "Executable.h"

class Replace : public Executable {
    private:
    std::string m_what;
    std::string m_with;

    public:
    Replace(const std::string& instruction, std::vector<Token> tokens);
    std::string usage() override;
    void execute() override;
};
