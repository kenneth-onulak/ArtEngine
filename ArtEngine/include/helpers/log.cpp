#include "pch.h"
#include "log.h"

namespace my_log
{

bool is_debug = true;    //!< use debug mode
std::string key = "LOG"; //!< type of log

void raw()
{
    std::cout << std::endl;
}

} // namespace log