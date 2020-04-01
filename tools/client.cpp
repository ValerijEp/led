#include "client/client.h"

#include "command/command.h"
#include "util/log.h"

#include <iostream>
#include <string>

const std::string default_ip = "127.0.0.1";
const int default_port = 6667;

void processCommand(Client& client, const BaseCommand& command);

int main(int argc, char* argv[])
{
    std::string ip = default_ip;
    int port =  default_port;
    if (argc >= 2)
    {
        ip = argv[1];
    }
    if (argc >= 3)
    {
        port = std::atoi(argv[2]);
    }
    
    Log() << "ip: " << ip;
    Log() << "port: " << port;
    Client client(ip, port);
    
    while (true)
    {
        std::cout << "Choose the command:" << std::endl;
        std::cout << "1. Get led state" << std::endl;
        std::cout << "2. Turn on" << std::endl;
        std::cout << "3. Turn off" << std::endl;
        std::cout << "4. Get led color" << std::endl;
        std::cout << "5. Set red color" << std::endl;
        std::cout << "6. Set green color" << std::endl;
        std::cout << "7. Set blue color" << std::endl;
        std::cout << "8. Get led rate" << std::endl;
        std::cout << "9. Set led rate" << std::endl;
        std::cout << "10. Exit" << std::endl;
        
        int command_number; 
        std::cin >> command_number;
        switch (command_number)
        {
            case 1:
            {
                GetLedStateCommand get_state_command;
                processCommand(client, get_state_command);
                break;
            }
            case 2:
            {
                SetLedStateCommand set_state_command(util::State::On);
                processCommand(client, set_state_command);
                break;
            }
            case 3:
            {
                SetLedStateCommand set_state_command(util::State::Off);
                processCommand(client, set_state_command);
                break;
            }
            case 4:
            {
                GetLedColorCommand get_color_command;
                processCommand(client, get_color_command);
                break;
            }
            case 5:
            {
                SetLedColorCommand set_color_command(util::Color::Red);
                processCommand(client, set_color_command);
                break;
            }
            case 6:
            {
                SetLedColorCommand set_color_command(util::Color::Green);
                processCommand(client, set_color_command);
                break;
            }
            case 7:
            {
                SetLedColorCommand set_color_command(util::Color::Blue);
                processCommand(client, set_color_command);
                break;
            }
            case 8:
            {
                GetLedRateCommand get_rate_command;
                processCommand(client, get_rate_command);
                break;
            }
            case 9:
            {
                std::cout << "Enter the rate: ";
                unsigned rate;
                std::cin >> rate;
                SetLedRateCommand set_rate_command(rate);
                processCommand(client, set_rate_command);
                break;
            }
            case 10:
            {
                return 0;
            }
            default:
            {
                // nothing to do
            }
        }
    }

    return 0;
}

void processCommand(Client& client, const BaseCommand& command)
{
    client.send(command);
    std::cout << client.receive() << std::endl;
}
