#pragma once
#include "Executable.h"

class Chain : public Executable {
    private:
    std::vector<Executable*> m_executables;

    public:
    Chain(const std::string& instruction, std::vector<Token> tokens);
    std::string usage() override;
    void execute() override;
    void set_out(std::ostream* in, bool owns) override;
    void check_for_errors(const std::string& instruction, const std::vector<Token>& tokens);
    std::vector<std::vector<Token>> split_on_pipe(const std::vector<Token>& tokens);
    ~Chain();
};
