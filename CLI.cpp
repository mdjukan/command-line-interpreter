#include "CLI.h"
#include "InstructionExecutor.h"
#include "Utils.h"
#include <iostream>
#include <string>

std::string CLI::prompt = "$";

void CLI::run() {
    while (true) {
        std::cout << prompt << " ";

        std::string instruction;
        Utils::read_instruction(&std::cin, instruction);

        InstructionExecutor ie(instruction, &std::cout);
        ie.execute();
    }
}
