#pragma once
#include "executable.h"

class Touch :public Executable {
public:
	void exec() override;
	std::string arg;
	Touch(std::string arg);
	
};
