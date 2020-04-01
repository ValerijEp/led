#pragma once

#include <boost/asio.hpp>

#include <memory>
#include <string>

class Session;
class CommandParser;
struct LED;

class Server final
{
public:
    Server(std::string address, int port, unsigned int requested_number_threads,
        std::shared_ptr<CommandParser> command_parser);
    ~Server();
   
    void Run();
    void Stop();

private:
    void HandleAccept(const boost::system::error_code& error);

    boost::asio::io_service io_service;
    boost::asio::ip::tcp::acceptor acceptor;

    std::shared_ptr<CommandParser> command_parser;
    std::shared_ptr<LED> led;
    std::shared_ptr<Session> new_session;
    unsigned int thread_pool_size;
};
