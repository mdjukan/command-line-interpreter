#include "Batch.h"
#include "../InstructionExecutor.h"
#include "../Token.h"
#include "../Utils.h"
#include "Executable.h"

Batch::Batch(const std::string& instruction, std::vector<Token> tokens)
    : Executable(instruction, tokens) {
    tokens.erase(tokens.begin());

    if (!tokens.empty() && tokens.front().type == TokenType::WORD) {
        redirect_in(tokens.front().get_value(instruction));
        tokens.erase(tokens.begin());
    }

    handle_redirects(instruction, tokens);
}

std::string Batch::usage() { return "batch [argument]"; }

void Batch::execute() {
    std::string instruction;
    while (Utils::read_instruction(m_in, instruction)) {
        InstructionExecutor ie(instruction, m_out);
        ie.execute();
    }
}
