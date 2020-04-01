#include "command/set_led_color_command.h"

#include "util/led.h"

SetLedColorCommand::SetLedColorCommand(util::Color color) : color(color)
{
}

std::string SetLedColorCommand::getCommand() const
{
    auto color_iterator = util::enumToStringColors.find(color);
    if (color_iterator == util::enumToStringColors.end())
    {
        return {};
    }
    return std::string(command_name) + ' ' + color_iterator->second + '\n';
}

BaseCommand::FillFromPartsResult SetLedColorCommand::fillFromParts(const std::vector<std::string>& parts)
{
    if (parts.empty())
    {
        return BaseCommand::FillFromPartsResult::Failed;
    }
    
    auto color_iterator = util::stringToEnumColors.find(parts.front());
    if (color_iterator == util::stringToEnumColors.end())
    {
        return BaseCommand::FillFromPartsResult::Failed;
    }
    
    color = color_iterator->second;
    return BaseCommand::FillFromPartsResult::Successed;
}

std::vector<char> SetLedColorCommand::run(LED& led)
{
    led.color = color;
    
    return {'O', 'K', '\n'};
}

std::unique_ptr<BaseCommand> SetLedColorCommand::clone() const
{
    return std::make_unique<SetLedColorCommand>(*this);
}
