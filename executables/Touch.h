#pragma once
#include "Executable.h"

class Touch : public Executable {
    private:
    std::string m_file_name;

    public:
    Touch(const std::string& instruction, std::vector<Token> tokens);
    std::string usage() override;
    void execute() override;
};
