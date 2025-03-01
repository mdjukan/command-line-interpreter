#pragma once
#include "Executable.h"

class Truncate : public Executable {
    private:
    std::string m_file_name;

    public:
    Truncate(const std::string& instruction, std::vector<Token> tokens);
    std::string usage() override;
    void execute() override;
};
