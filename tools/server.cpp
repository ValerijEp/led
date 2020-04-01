#include "server/server.h"
#include "command/command_parser.h"
#include "command/command.h"
#include "util/log.h"

#include <memory>
#include <string>

const std::string default_address = "127.0.0.1";
const int default_port = 6667;
const int default_threads_number = 4;

int main(int argc, char* argv[])
{
    auto address = default_address;
    auto port = default_port;
    auto threads_number = default_threads_number;
    if (argc >= 2)
    {
        address = argv[1];
    }
    if (argc >= 3)
    {
        port = std::atoi(argv[2]);
    }
    if (argc >= 4)
    {
        threads_number = std::atoi(argv[3]);
    }
    
    Log() << "address: " << address;
    Log() << "port: " << port;
    Log() << "threads number: " << threads_number;

    auto parser = std::make_unique<CommandParser>();
    parser->registerCommand<SetLedStateCommand>();
    parser->registerCommand<GetLedColorCommand>();
    parser->registerCommand<GetLedRateCommand>();
    parser->registerCommand<GetLedStateCommand>();
    parser->registerCommand<SetLedColorCommand>();
    parser->registerCommand<SetLedRateCommand>();

    Server server(address, port, threads_number, std::move(parser));
    server.Run();
    
    return 0;
}
