#pragma once
#include "Exception.h"
#include <sstream>

class InstructionError : public Exception {
    private:
    std::string m_instruction;
    std::size_t m_start_idx;
    std::size_t m_end_idx;

    public:
    InstructionError(const std::string& instruction, std::size_t start_idx, std::size_t end_idx,
                     const std::string& message)
        : Exception(message), m_instruction(instruction), m_start_idx(start_idx),
          m_end_idx(end_idx) {
    }

    std::string what() override;
};
