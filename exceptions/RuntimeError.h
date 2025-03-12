#pragma once
#include "Exception.h"

class RuntimeError : public Exception {
    public:
    RuntimeError(const std::string& message) : Exception(message) {
    }

    std::string what() override;
};
