#include "InstructionError.h"

std::string InstructionError::what() {
    std::stringstream ss;

    ss << m_message << std::endl;
    ss << m_instruction << std::endl;

    for (std::size_t i = 0; i < m_instruction.size(); i++) {
        if (m_start_idx <= i && i <= m_end_idx) {
            ss << '^';
        } else if (m_instruction[i] == '\t') {
            ss << '\t';
        } else {
            ss << ' ';
        }
    }

    return ss.str();
}
