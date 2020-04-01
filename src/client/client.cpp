#include "client/client.h"

#include "command/base_command.h"
#include "util/log.h"

Client::Client(std::string server_address, int port) :
    socket(io_service)
{
    socket.connect(
        boost::asio::ip::tcp::endpoint(
            boost::asio::ip::address::from_string(
                std::move(server_address)),
                port));
}

void Client::send(const BaseCommand& command)
{
    boost::system::error_code error;
    boost::asio::write(socket, boost::asio::buffer(command.getCommand()), error);
    if (error)
    {
        Log() << "error of sending message: " << error.message();
    }
}

std::string Client::receive()
{
    boost::asio::streambuf buffer;
    boost::system::error_code error;
    boost::asio::read_until(socket, buffer, delimiter, error);
    if (error)
    {
        Log() << "error of reading message: " << error.message();
        return {};
    }
    return std::string(boost::asio::buffer_cast<const char*>(buffer.data()));
}
