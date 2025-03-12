#include "Executable.h"
#include "../Token.h"
#include "../exceptions/InstructionError.h"
#include "../exceptions/RuntimeError.h"
#include <fstream>
#include <iostream>
#include <vector>

Executable::Executable(const std::string instruction, const std::vector<Token>& tokens)
    : m_instruction(instruction) {
    m_instr_start = tokens.front().start_idx;
    m_instr_end = tokens.back().end_idx;
}

Executable::~Executable() {
    if (m_owns_in) {
        delete m_in;
    }

    if (m_owns_out) {
        delete m_out;
    }
}

void Executable::incorrect_usage_error() {
    throw new InstructionError(m_instruction, m_instr_start, m_instr_end,
                               "Error - correct usage is \"" + usage() + "\":");
}

void Executable::set_in(std::istream* in, bool owns) {
    m_in = in;
    m_owns_in = owns;
}

bool Executable::in_redirected() {
    return m_in != &std::cin;
}

void Executable::set_out(std::ostream* out, bool owns) {
    m_out = out;
    m_owns_out = owns;
}

bool Executable::out_redirected() {
    return m_out != &std::cout;
}

bool Executable::writes_to_file() {
    return dynamic_cast<std::fstream*>(m_out) != nullptr;
}

void Executable::redirect_in(const std::string& file_path) {
    std::fstream* in = new std::fstream(file_path, std::ios::in);
    if (in->is_open()) {
        m_in = in;
        m_owns_in = true;
    } else {
        delete in;
        throw new RuntimeError("Cannot open input file \"" + file_path + "\"");
    }
}

void Executable::redirect_out(const std::string& file_path) {
    std::fstream* out = new std::fstream(file_path, std::ios::out | std::ios::trunc);
    if (out->is_open()) {
        m_out = out;
        m_owns_out = true;
    } else {
        delete out;
        throw new RuntimeError("Cannot open output file \"" + file_path + "\"");
    }
}

void Executable::redirect_out_app(const std::string& file_path) {
    std::fstream* out = new std::fstream(file_path, std::ios::out | std::ios::app);
    if (out->is_open()) {
        m_out = out;
        m_owns_out = true;
    } else {
        delete out;
        throw new RuntimeError("Cannot open output file \"" + file_path + "\"");
    }
}

void Executable::handle_redirects(const std::string& instruction, std::vector<Token> tokens) {
    // < file.name
    // > file.name
    // >> file.name
    // sve sto odstupa od ovog generise gresku
    while (!tokens.empty()) {
        Token redirect_token = tokens.front();
        tokens.erase(tokens.begin());

        if (redirect_token.type != TokenType::LT && redirect_token.type != TokenType::GT &&
            redirect_token.type != TokenType::GGT) {
            throw new InstructionError(instruction, redirect_token.start_idx,
                                       redirect_token.end_idx, "Error - ivalid instruction:");
        }

        if (tokens.empty()) {
            throw new InstructionError(instruction, redirect_token.start_idx,
                                       redirect_token.end_idx,
                                       "Error - redirect missing an argument:");
        }

        if (tokens.front().type != TokenType::WORD) {
            throw new InstructionError(instruction, tokens.front().start_idx,
                                       tokens.front().end_idx,
                                       "Error - invalid argument for redirect:");
        }

        switch (redirect_token.type) {
        case TokenType::LT:
            if (in_redirected()) {
                throw new InstructionError(instruction, redirect_token.start_idx,
                                           tokens.front().end_idx,
                                           "Error - input stream already assigned:");
            }
            redirect_in(tokens.front().get_value(instruction));
            break;
        case TokenType::GT:
            if (out_redirected()) {
                throw new InstructionError(instruction, redirect_token.start_idx,
                                           tokens.front().end_idx,
                                           "Error - output stream already assigned:");
            }
            redirect_out(tokens.front().get_value(instruction));
            break;
        case TokenType::GGT:
            if (out_redirected()) {
                throw new InstructionError(instruction, redirect_token.start_idx,
                                           tokens.front().end_idx,
                                           "Error - output stream already assigned:");
            }
            redirect_out_app(tokens.front().get_value(instruction));
            break;
        }

        tokens.erase(tokens.begin());
    }
}
