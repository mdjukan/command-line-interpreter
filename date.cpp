#include "date.h"
#include <ctime>
#include <iomanip>

void Date::exec() {
	std::time_t now = std::time(nullptr);
	struct tm time_info;
	localtime_r(&now, &time_info);
	(*output) << std::put_time(&time_info, "%d %m %Y") << std::endl;
}
