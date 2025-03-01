#pragma once
#include "Token.h"
#include "executables/Executable.h"
#include <string>
#include <vector>

class ExecutableFactory {
    public:
    static bool is_space(char c);
    static bool valid_in_word(char c);
    static bool valid_in_option(char c);
    static bool contains_pipe(const std::vector<Token>& tokens);
    static void print_tokens(const std::string& instruction, const std::vector<Token>& tokens);

    static std::vector<Token> tokenize(const std::string& instruction);
    static Executable* from_tokens(const std::string& instruction,
                                   const std::vector<Token>& tokens);
    static Executable* create_executable(const std::string& instruction);
};
