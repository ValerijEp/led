#include "command/command_parser.h"

#include "command/base_command.h"

#include <boost/algorithm/string.hpp>

std::unique_ptr<BaseCommand> CommandParser::parse(const std::string& command) const
{
    std::vector<std::string> command_parts;
    boost::split(command_parts, command, [](char character)
    {
        return (character == delimiter || character == new_line || character == '\0');
    });

    auto command_iterator = commands.find(command_parts.front());
    if (command_iterator == commands.end())
    {
        return nullptr;
    }
    if (command_iterator->second->fillFromParts({std::next(command_parts.begin()), command_parts.end()}) == BaseCommand::FillFromPartsResult::Failed)
    {
        return nullptr;
    }

    return command_iterator->second->clone();
}
