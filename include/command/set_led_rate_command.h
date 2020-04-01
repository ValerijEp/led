#pragma once

#include "command/base_command.h"
#include "util/constants.h"

struct LED;

class SetLedRateCommand final : public BaseCommand
{
public:
    SetLedRateCommand() = default;
    SetLedRateCommand(util::Rate rate);

    virtual std::string getCommand() const override final;
    virtual BaseCommand::FillFromPartsResult fillFromParts(const std::vector<std::string>& parts) override final;
    virtual std::vector<char> run(LED& led) override final;
    virtual std::unique_ptr<BaseCommand> clone() const override final;
    static constexpr std::string_view getName()
    {
        return command_name;
    }
    
private:
    static constexpr std::string_view command_name = "set-led-rate";
    static const int max_rate = 5;
    util::Rate rate; 
};
