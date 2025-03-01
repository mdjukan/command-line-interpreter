#pragma once
#include "Executable.h"

class Remove : public Executable {
    private:
    std::string m_file_name;

    public:
    Remove(const std::string& instruction, std::vector<Token> tokens);
    std::string usage() override;
    void execute() override;
};
