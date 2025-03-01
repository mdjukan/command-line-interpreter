#include "Utils.h" //TODO da li ovaj fajl treba da includuje header gde je deklarisan namespace
#include <iostream>
// da li cpp fajl u kojem su definisani metodi treba da includuje header fajl u kojem
// je deklarisana klasa

std::istream& Utils::read_instruction(std::istream* in, std::string& instruction) {
    std::getline(*in, instruction);
    instruction = instruction.substr(0, INSTRUCTION_LENGTH);
    return *in;
}

std::stringstream* Utils::strlit_to_sstream(const std::string& instruction, const Token& token) {
    const std::string& token_value = token.get_value(instruction);
    return new std::stringstream(token_value.substr(1, token_value.size() - 2));
}

std::string Utils::strlit_to_string(const std::string& instruction, const Token& token) {
    const std::string& token_value = token.get_value(instruction);
    return token_value.substr(1, token_value.size() - 2);
}

// TODO prepraviti da ispisuje token, tip i vrednost
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
