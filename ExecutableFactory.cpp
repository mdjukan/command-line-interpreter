#include "ExecutableFactory.h"
#include "Token.h"
#include "exceptions/InstructionError.h"
#include "exceptions/RuntimeError.h"
#include "executables/Executables.h"
#include <iostream>
#include <string>
#include <vector>

bool ExecutableFactory::is_space(char c) {
    return (c == ' ') || (c == '\t');
}

bool ExecutableFactory::valid_in_word(char c) {
    if (c == '.' || c == '_') {
        return true;
    }

    if ('0' <= c && c <= '9') {
        return true;
    }

    if ('a' <= c && c <= 'z') {
        return true;
    }

    if ('A' <= c && c <= 'z') {
        return true;
    }

    return false;
}

bool ExecutableFactory::valid_in_option(char c) {
    if ('0' <= c && c <= '9') {
        return true;
    }

    if ('a' <= c && c <= 'z') {
        return true;
    }

    if ('A' <= c && c <= 'z') {
        return true;
    }

    return false;
}

// da li prosledjujem chain-u
bool ExecutableFactory::contains_pipe(const std::vector<Token>& tokens) {
    for (const Token& token : tokens) {
        if (token.type == TokenType::PIPE) {
            return true;
        }
    }

    return false;
}

std::vector<Token> ExecutableFactory::tokenize(const std::string& instruction) {
    /* std::cout << "[INSTRUCTION]" << instruction << std::endl; */
    std::vector<Token> tokens;

    std::size_t i = 0;
    while (i < instruction.size()) {
        if (is_space(instruction[i])) {
            i += 1;
        } else if (instruction[i] == '<') {
            tokens.emplace_back(TokenType::LT, i, i);
            i += 1;
        } else if (instruction[i] == '>') {

            if (i + 1 < instruction.size() && instruction[i + 1] == '>') {
                tokens.emplace_back(TokenType::GGT, i, i + 1);
                i += 2;
            } else {
                tokens.emplace_back(TokenType::GT, i, i);
                i += 1;
            }

        } else if (instruction[i] == '|') {
            tokens.emplace_back(TokenType::PIPE, i, i);
            i += 1;
        } else if (instruction[i] == '-') {
            std::size_t start_idx = i;
            i += 1; // preskace -

            while (i < instruction.size() && !is_space(instruction[i])) {
                if (!valid_in_option(instruction[i])) {
                    throw new InstructionError(instruction, i, i, "Error - unexpected charachter:");
                }
                i += 1;
            }

            std::size_t end_idx = i - 1;
            tokens.emplace_back(TokenType::OPTION, start_idx, end_idx);
        } else if (instruction[i] == '"') {
            std::size_t start_idx = i;

            i += 1;
            //... "adjkfjasdfhkajdsfh
            while (i < instruction.size() && instruction[i] != '"') {
                i += 1;
            }

            if (i == instruction.size()) {
                throw new InstructionError(instruction, start_idx, i - 1,
                                           "Error - string literal missing closing quote:");
            }

            std::size_t end_idx = i; // i pokazuje na "
            i += 1;

            tokens.emplace_back(TokenType::STRLIT, start_idx, end_idx);
        } else {
            std::size_t start_idx = i;

            while (i < instruction.size() && !is_space(instruction[i])) {
                if (!valid_in_word(instruction[i])) {
                    throw new InstructionError(instruction, i, i, "Error - unexpected charachter:");
                }
                i += 1;
            }

            std::size_t end_idx = i - 1;
            tokens.emplace_back(TokenType::WORD, start_idx, end_idx);
        }
    }

    return tokens;
}

// debug
std::ostream& operator<<(std::ostream& out, const enum TokenType& type) {
    switch (type) {
    case TokenType::WORD:
        out << "WORD";
        break;
    case TokenType::STRLIT:
        out << "STRLIT";
        break;
    case TokenType::OPTION:
        out << "OPTION";
        break;
    case TokenType::PIPE:
        out << "PIPE";
        break;
    case TokenType::LT:
        out << "LT";
        break;
    case TokenType::GT:
        out << "GT";
        break;
    case TokenType::GGT:
        out << "GGT";
        break;
    }

    return out;
}

// debug
void ExecutableFactory::print_tokens(const std::string& instruction,
                                     const std::vector<Token>& tokens) {
    for (const Token& token : tokens) {
        std::cout << "[" << token.type << ":" << token.get_value(instruction) << "]";
    }
    std::cout << std::endl;
}

Executable* ExecutableFactory::create_executable(const std::string& instruction) {
    std::vector<Token> tokens = tokenize(instruction);
    /* print_tokens(instruction, tokens); */

    // instrukcija u kojoj je samo white space
    if (tokens.empty()) {
        throw new RuntimeError("Error - empty instruction");
    }

    if (contains_pipe(tokens)) {
        return new Chain(instruction, tokens);
    } else {
        return from_tokens(instruction, tokens);
    }
}

Executable* ExecutableFactory::from_tokens(const std::string& instruction,
                                           const std::vector<Token>& tokens) {
    if (tokens[0].type != TokenType::WORD) {
        throw new InstructionError(instruction, tokens[0].start_idx, tokens[0].end_idx,
                                   "Error - invalid command");
    }

    std::string command = tokens[0].get_value(instruction);
    // tokens.erase(tokens.begin())
    if (command == "echo") {
        return new Echo(instruction, tokens);
    } else if (command == "prompt") {
        return new Prompt(instruction, tokens);
    } else if (command == "time") {
        return new Time(instruction, tokens);
    } else if (command == "date") {
        return new Date(instruction, tokens);
    } else if (command == "touch") {
        return new Touch(instruction, tokens);
    } else if (command == "rm") {
        return new Remove(instruction, tokens);
    } else if (command == "truncate") {
        return new Truncate(instruction, tokens);
    } else if (command == "wc") {
        return new WordCount(instruction, tokens);
    } else if (command == "tr") {
        return new Replace(instruction, tokens);
    } else if (command == "head") {
        return new Head(instruction, tokens);
    } else if (command == "batch") {
        return new Batch(instruction, tokens);
    } else {
        throw new InstructionError(instruction, tokens[0].start_idx, tokens[0].end_idx,
                                   "Error - unknown command");
    }
}
