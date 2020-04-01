#include "command/set_led_state_command.h"

#include "util/led.h"

SetLedStateCommand::SetLedStateCommand(util::State state) : state(state)
{
}

std::string SetLedStateCommand::getCommand() const
{
    return std::string(command_name) + ' ' + (state == util::State::On ? "on" : "off") + '\n';
}

BaseCommand::FillFromPartsResult SetLedStateCommand::fillFromParts(const std::vector<std::string>& parts)
{
    if (parts.empty())
    {
        return BaseCommand::FillFromPartsResult::Failed;
    }
    if (parts.front() == "on")
    {
        state = util::State::On;
    }
    else if (parts.front() == "off")
    {
        state = util::State::Off;
    }
    else
    {
        return BaseCommand::FillFromPartsResult::Failed;
    }
    return BaseCommand::FillFromPartsResult::Successed;
}

std::vector<char> SetLedStateCommand::run(LED& led)
{
    led.state = state; 
    return {'O', 'K', '\n'};
}

std::unique_ptr<BaseCommand> SetLedStateCommand::clone() const
{
    return std::make_unique<SetLedStateCommand>(*this);
}
