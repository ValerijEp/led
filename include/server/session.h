#pragma once

#include <boost/asio.hpp>

#include <memory>

class CommandParser;
struct LED;

class Session final : public std::enable_shared_from_this<Session>
{
public:
    Session(boost::asio::io_service& io_service,
        std::shared_ptr<CommandParser> command_parser,
        std::shared_ptr<LED> led,
        bool keep_alive = false);
    Session(const Session&) = delete;
    Session& operator=(const Session&) = delete;
    ~Session();
    
    boost::asio::ip::tcp::socket& getSocket();
    void start();

private:
    static const char delimiter = '\n';

    void handleRead(const boost::system::error_code& error, std::size_t bytes_transferred);
    void handleWrite(const boost::system::error_code& error);
    void handleTimeout(const boost::system::error_code& error);
    void handleShutdown();

    boost::asio::ip::tcp::socket socket;
    boost::asio::io_service::strand strand;
    boost::asio::deadline_timer timer;

    boost::asio::streambuf incoming_data_buffer;
    std::shared_ptr<CommandParser> command_parser;
    std::shared_ptr<LED> led;
   
    bool keep_alive;
    short keep_alive_timeout = 5; // in seconds
};
