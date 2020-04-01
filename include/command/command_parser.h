#pragma once

#include <map>
#include <memory>
#include <string_view>
#include <type_traits>

class BaseCommand;

class CommandParser final
{
public:
    template<class CommandT, class = typename std::enable_if<std::is_base_of_v<BaseCommand, CommandT>>::type>
    void registerCommand()
    {
        commands.emplace(CommandT::getName(), std::make_unique<CommandT>());
    }

    std::unique_ptr<BaseCommand> parse(const std::string& command) const;

private:
    static const char new_line = '\n';
    static const char delimiter = ' ';

    std::map<std::string_view, std::unique_ptr<BaseCommand>> commands;
};
