#include "command/get_led_state_command.h"

#include "util/constants.h"
#include "util/led.h"

std::string GetLedStateCommand::getCommand() const
{
    return std::string(command_name) + '\n';
}

BaseCommand::FillFromPartsResult GetLedStateCommand::fillFromParts(const std::vector<std::string>& parts)
{
    return BaseCommand::FillFromPartsResult::Successed;
}

std::vector<char> GetLedStateCommand::run(LED& led)
{
    std::vector<char> result = {'O', 'K', ' '};
    const std::string state = (led.state == util::State::On ? "on" : "off");
    result.insert(result.end(), state.begin(), state.end());
    result.push_back('\n');
    return result;
}

std::unique_ptr<BaseCommand> GetLedStateCommand::clone() const
{
    return std::make_unique<GetLedStateCommand>(*this); 
}
