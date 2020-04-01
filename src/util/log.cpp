#include "util/log.h"

#include <iostream>

Log::~Log()
{
    buffer << std::endl;
    std::cerr << buffer.str();
}
