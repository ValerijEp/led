#include "command/get_led_color_command.h"

#include "util/constants.h"
#include "util/led.h"
#include "util/log.h"

std::string GetLedColorCommand::getCommand() const
{
    return std::string(command_name) + '\n';
}

BaseCommand::FillFromPartsResult GetLedColorCommand::fillFromParts(const std::vector<std::string>& parts)
{
    return BaseCommand::FillFromPartsResult::Successed;
}

std::vector<char> GetLedColorCommand::run(LED& led)
{
    auto color_iterator = util::enumToStringColors.find(led.color);
    if (color_iterator == util::enumToStringColors.end())
    {
        Log() << "There is no such color in the color map";
        return util::failed;
    }
    std::vector<char> result = {'O', 'K', ' '};
    result.insert(result.end(), color_iterator->second.begin(), color_iterator->second.end());
    result.push_back('\n');
    return result;
}

std::unique_ptr<BaseCommand> GetLedColorCommand::clone() const
{
    return std::make_unique<GetLedColorCommand>(*this); 
}
