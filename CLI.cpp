#include "CLI.h"
#include "InstructionExecutor.h"
#include "Utils.h"
#include <iostream>
#include <string>

std::string CLI::prompt = "$";

// TODO resavanje problema ispisa novog reda nakon instrukcije
// sta sa onim koje same ispisu novi red, u tom slucaju cu imati jedan novi red viska
// to je manji problem nego da imam novi red
// TODO problem novog reda se odnosi na ispis gresaka
void CLI::run() {
    while (true) {
        std::cout << prompt << " ";

        std::string instruction;
        Utils::read_instruction(&std::cin, instruction);

        InstructionExecutor ie(instruction, &std::cout);
        ie.execute();
    }
}
