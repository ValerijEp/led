#include "server/session.h"

#include "command/base_command.h"
#include "command/command_parser.h"
#include "util/constants.h"
#include "util/log.h"

Session::Session(boost::asio::io_service& io_service,
    std::shared_ptr<CommandParser> command_parser,
    std::shared_ptr<LED> led,
    bool keep_alive) :
    strand(io_service),
    socket(io_service),
    command_parser(std::move(command_parser)),
    led(std::move(led)),
    timer(io_service),
    keep_alive(keep_alive)
{
}

Session::~Session() = default;

boost::asio::ip::tcp::socket& Session::getSocket()
{
    return socket;
}

void Session::start()
{
     boost::asio::async_read_until(
        socket,
        incoming_data_buffer,
        delimiter,
        strand.wrap(std::bind(
            &Session::handleRead,
            this->shared_from_this(),
            std::placeholders::_1,
            std::placeholders::_2)));

     if (keep_alive)
     {
        timer.cancel();
        timer.expires_from_now(boost::posix_time::seconds(keep_alive_timeout));
        timer.async_wait(std::bind(&Session::handleTimeout, this->shared_from_this(), std::placeholders::_1));
     }
}

void Session::handleRead(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (error)
    {
        Log() << "error of receiving message: " << error.message();
        handleShutdown();
        return;
    }

    const std::string incoming_data = boost::asio::buffer_cast<const char*>(incoming_data_buffer.data());
    auto command = command_parser->parse(incoming_data);
    incoming_data_buffer.consume(bytes_transferred);
    
    std::vector<char> answer = util::failed;
    if (command)
    {
        answer = command->run(*led);
    }
    
    boost::asio::async_write(
        socket,
        boost::asio::buffer(answer),
        strand.wrap(std::bind(
            &Session::handleWrite,
            this->shared_from_this(),
            std::placeholders::_1)));
}

void Session::handleWrite(const boost::system::error_code& error)
{
    if (error)
    {
        Log() << "error of sending message: " << error.message();
        handleShutdown();
        return;
    }

    this->start();
}

void Session::handleTimeout(const boost::system::error_code& error)
{
    if (error != boost::asio::error::operation_aborted)
    {
        boost::system::error_code error;
        socket.cancel(error);
        handleShutdown();
    }
}

void Session::handleShutdown()
{
    boost::system::error_code error;
    socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, error);
    Log() << "socket shutdown";
}
