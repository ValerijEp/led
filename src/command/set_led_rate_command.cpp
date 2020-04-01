#include "command/set_led_rate_command.h"

#include "util/led.h"

#include <cstdlib>

SetLedRateCommand::SetLedRateCommand(util::Rate rate) : rate(rate)
{
}

std::string SetLedRateCommand::getCommand() const
{
    return std::string(command_name) + ' ' + std::to_string(rate) + '\n';
}

BaseCommand::FillFromPartsResult SetLedRateCommand::fillFromParts(const std::vector<std::string>& parts)
{
    if (parts.empty())
    {
        return BaseCommand::FillFromPartsResult::Failed;
    }
    char* end;
    rate = std::strtoul(parts.front().c_str(), &end, 10);
    if (rate > max_rate)
    {
        return BaseCommand::FillFromPartsResult::Failed;
    }
    return BaseCommand::FillFromPartsResult::Successed;
}

std::vector<char> SetLedRateCommand::run(LED& led)
{
    led.rate = rate;
    
    return {'O', 'K', '\n'};
}

std::unique_ptr<BaseCommand> SetLedRateCommand::clone() const
{
    return std::make_unique<SetLedRateCommand>(*this);
}
