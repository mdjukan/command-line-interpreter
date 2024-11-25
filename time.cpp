#include "time.h"
#include <ctime>
#include <iomanip>

void Time::exec() {
	std::time_t now = std::time(nullptr);
	std::tm* local_time = std::localtime(&now);
	//TODO greska u slucaju da je output==nullptr
	(*output) << std::put_time(local_time, "%H:%M:%S") << std::endl;
}
