#include "command/get_led_rate_command.h"

#include "util/led.h"

std::string GetLedRateCommand::getCommand() const
{
    return std::string(command_name) + '\n';
}

BaseCommand::FillFromPartsResult GetLedRateCommand::fillFromParts(const std::vector<std::string>& parts)
{
    return BaseCommand::FillFromPartsResult::Successed;
}

std::vector<char> GetLedRateCommand::run(LED& led)
{
    std::vector<char> result = {'O', 'K', ' '};
    const auto rate = std::to_string(led.rate);
    result.insert(result.end(), rate.begin(), rate.end());
    result.push_back('\n');
    return result;
}

std::unique_ptr<BaseCommand> GetLedRateCommand::clone() const
{
    return std::make_unique<GetLedRateCommand>(*this); 
}
