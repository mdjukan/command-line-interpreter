#include "RuntimeError.h"

std::string RuntimeError::what() {
    return m_message;
}
