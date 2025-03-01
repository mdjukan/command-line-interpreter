#pragma once
#include <iostream>
#include <string>

class InstructionExecutor {
    private:
    std::string m_instruction;
    std::ostream* m_out;

    public:
    InstructionExecutor(const std::string& instruction, std::ostream* out)
        : m_instruction(instruction), m_out(out) {}

    void execute();
};
