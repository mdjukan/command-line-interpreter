#include "InstructionExecutor.h"
#include "ExecutableFactory.h"
#include "exceptions/Exception.h"
#include "executables/Executable.h"

void InstructionExecutor::execute() {
    Executable* exe = nullptr;
    try {
        exe = ExecutableFactory::create_executable(m_instruction);

        if (!exe->writes_to_file()) {
            exe->set_out(m_out, false);
        }

        exe->execute();
    } catch (Exception* e) {
        (*m_out) << e->what() << std::endl;
        delete e;
    }

    delete exe;
}
