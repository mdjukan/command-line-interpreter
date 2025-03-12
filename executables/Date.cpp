#include "Date.h"
#include "../exceptions/InstructionError.h"
#include "../exceptions/RuntimeError.h"
#include "Executable.h"
#include <ctime>
#include <iomanip>

Date::Date(const std::string& instruction, std::vector<Token> tokens)
    : Executable(instruction, tokens) {
    tokens.erase(tokens.begin());
    handle_redirects(instruction, tokens);
}

std::string Date::current_date() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::stringstream ss;
    ss << std::put_time(&tm, "%d.%m.%Y.");
    return ss.str();
}

std::string Date::usage() {
    return "date";
}

void Date::execute() {
    (*m_out) << current_date() << std::endl;
}
