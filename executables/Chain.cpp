#include "Chain.h"
#include "../ExecutableFactory.h"
#include "../Token.h"
#include "../exceptions/InstructionError.h"
#include "../exceptions/RuntimeError.h"
#include "Executable.h"
#include <sstream>

Chain::Chain(const std::string& instruction, std::vector<Token> tokens)
    : Executable(instruction, tokens) {
    check_for_errors(instruction, tokens);
    std::vector<std::vector<Token>> instructions = split_on_pipe(tokens);
    for (std::size_t i = 0; i < instructions.size(); i++) {
        m_executables.push_back(ExecutableFactory::from_tokens(instruction, instructions[i]));
    }

    for (std::size_t i = 0; i < m_executables.size() - 1; i++) {
        std::stringstream* ss = new std::stringstream();
        m_pipes.push_back(ss);

        if (m_executables[i]->out_redirected()) {
            throw new InstructionError(instruction, instructions[i].front().start_idx,
                                       instructions[i].back().end_idx,
                                       "Error - multiple redirects of output stream:");
        }

        if (m_executables[i + 1]->in_redirected()) {
            throw new InstructionError(instruction, instructions[i + 1].front().start_idx,
                                       instructions[i + 1].back().end_idx,
                                       "Error - multiple redirects of input stream:");
        }

        m_executables[i]->set_out(ss);
        m_executables[i + 1]->set_in(ss);
    }
}

std::string Chain::usage() { return ""; }

void Chain::execute() {
    if (!m_executables.back()->writes_to_file()) {
        m_executables.back()->set_out(m_out);
    }

    for (std::size_t i = 0; i < m_executables.size(); i++) {
        m_executables[i]->execute();
    }
}

void Chain::check_for_errors(const std::string& instruction, const std::vector<Token>& tokens) {
    if (tokens.front().type == TokenType::PIPE) {
        throw new InstructionError(instruction, tokens.front().start_idx, tokens.front().end_idx,
                                   "Error - pipe missing left argument:");
    }

    if (tokens.back().type == TokenType::PIPE) {
        throw new InstructionError(instruction, tokens.back().start_idx, tokens.back().end_idx,
                                   "Error - pipe missing right argument:");
    }

    for (std::size_t i = 0; i < tokens.size() - 1; i++) {
        if (tokens[i].type == TokenType::PIPE && tokens[i + 1].type == TokenType::PIPE) {
            throw new InstructionError(instruction, tokens[i].start_idx, tokens[i].end_idx,
                                       "Error - pipe missing right argument::");
        }
    }
}

std::vector<std::vector<Token>> Chain::split_on_pipe(const std::vector<Token>& tokens) {
    std::vector<std::vector<Token>> result;
    std::vector<Token> single;
    for (std::size_t i = 0; i < tokens.size(); i++) {
        if (tokens[i].type == TokenType::PIPE) {
            result.push_back(single);
            single.clear();
        } else {
            single.push_back(tokens[i]);
        }
    }

    result.push_back(single);
    return result;
}

Chain::~Chain() {
    m_executables.front()->set_out(nullptr);
    m_executables.back()->set_in(nullptr);
    for (std::size_t i = 1; i < m_executables.size() - 1; i++) {
        m_executables[i]->set_in(nullptr);
        m_executables[i]->set_out(nullptr);
    }

    for (Executable* exe : m_executables) {
        delete exe;
    }

    for (std::stringstream* ss : m_pipes) {
        delete ss;
    }
}
