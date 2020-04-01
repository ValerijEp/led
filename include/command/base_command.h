#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <vector>

struct LED;

class BaseCommand
{
public:
    enum class FillFromPartsResult
    {
        Successed,
        Failed
    };

    virtual ~BaseCommand();

    virtual std::vector<char> run(LED& led) = 0;
    virtual std::string getCommand() const = 0;
    virtual FillFromPartsResult fillFromParts(const std::vector<std::string>& parts) = 0;
    virtual std::unique_ptr<BaseCommand> clone() const = 0;
};
