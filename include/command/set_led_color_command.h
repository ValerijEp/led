#pragma once

#include "command/base_command.h"
#include "util/constants.h"

struct LED;

class SetLedColorCommand final : public BaseCommand
{
public:
    SetLedColorCommand() = default;
    SetLedColorCommand(util::Color color);

    virtual std::string getCommand() const override final;
    virtual BaseCommand::FillFromPartsResult fillFromParts(const std::vector<std::string>& parts) override final;
    virtual std::vector<char> run(LED& led) override final;
    virtual std::unique_ptr<BaseCommand> clone() const override final;
    static constexpr std::string_view getName()
    {
        return command_name;
    }
    
private:
    static constexpr std::string_view command_name = "set-led-color";
    util::Color color; 
};
