#pragma once

#include <boost/asio.hpp>

#include <string>

class BaseCommand;

class Client final
{
public:
    Client(std::string server_address, int port);
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    void send(const BaseCommand& command);
    std::string receive();

private:
    static const char delimiter = '\n';
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::socket socket;
    //boost::asio::ip::tcp::resolver resolver;
};
