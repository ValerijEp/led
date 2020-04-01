#pragma once

#include <map>
#include <vector>

namespace util
{

static const std::vector<char> failed = {'F', 'A', 'I', 'L', 'E', 'D', '\n'};

enum class Color
{
    Red,
    Green,
    Blue
};

enum class State
{
    On,
    Off
};

using Rate = unsigned int;

const static std::map<Color, std::string> enumToStringColors
{
    {Color::Red, "red"},
    {Color::Green, "green"},
    {Color::Blue, "blue"}
};

const static std::map<std::string, Color> stringToEnumColors
{
    {"red", Color::Red},
    {"green", Color::Green},
    {"blue", Color::Blue}
};

}
