#pragma once
#include <string>

class Exception {
    protected:
    std::string m_message;

    public:
    Exception(const std::string& message) : m_message(message) {}
    virtual ~Exception()       = default;
    virtual std::string what() = 0;
};
