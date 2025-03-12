#pragma once
#include <string>

class Exception {
    protected:
    // public ?
    std::string m_message;

    public:
    Exception(const std::string& message) : m_message(message) {
    }
    virtual ~Exception() = default;
    // TODO error_message
    virtual std::string what() = 0;
};
