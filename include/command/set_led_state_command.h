#pragma once

#include "command/base_command.h"
#include "util/constants.h"

struct LED;

class SetLedStateCommand final : public BaseCommand
{
public:
    SetLedStateCommand() = default;
    SetLedStateCommand(util::State state);

    virtual std::string getCommand() const override final;
    virtual BaseCommand::FillFromPartsResult fillFromParts(const std::vector<std::string>& parts) override final;
    virtual std::vector<char> run(LED& led) override final;
    virtual std::unique_ptr<BaseCommand> clone() const override final;
    static constexpr std::string_view getName()
    {
        return command_name;
    }
    
private:
    static constexpr std::string_view command_name = "set-led-state";
    util::State state; 
};
