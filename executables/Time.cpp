#include "Time.h"
#include "../exceptions/InstructionError.h"
#include "../exceptions/RuntimeError.h"
#include "Executable.h"
#include <ctime>
#include <iomanip>

Time::Time(const std::string& instruction, std::vector<Token> tokens)
    : Executable(instruction, tokens) {
    // -1- proverim da li je time
    // -2- sklonim time token pre poziva
    //
    tokens.erase(tokens.begin()); // prvi token je time, jer jedino tad pozivam ovaj konstruktor
    handle_redirects(instruction, tokens);
}

std::string Time::current_time() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::stringstream ss;
    ss << std::put_time(&tm, "%H:%M:%S");
    return ss.str();
}

std::string Time::usage() {
    return "time";
}

void Time::execute() {
    (*m_out) << current_time() << std::endl;
}
