#pragma once

#include <sstream>

class Log final
{
public:
    ~Log();
    template<class T>
    Log& operator<<(const T& data)
    {
        buffer << data;
        return *this;
    }

private:
    std::stringstream buffer;
};
