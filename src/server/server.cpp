#include "server/server.h"

#include "command/base_command.h"
#include "command/command_parser.h"
#include "server/session.h"
#include "util/led.h"
#include "util/log.h"

#include <thread>

Server::Server(std::string address, int port, unsigned int requested_number_threads,
    std::shared_ptr<CommandParser> command_parser) :
    acceptor(io_service),
    command_parser(std::move(command_parser)),
    led(std::make_shared<LED>()),
    new_session(std::make_shared<Session>(io_service, this->command_parser, led))
{
    thread_pool_size = std::min(std::max(1u, std::thread::hardware_concurrency()), requested_number_threads);

    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query(std::move(address), std::to_string(port));
    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);

    acceptor.open(endpoint.protocol());
    acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor.bind(endpoint);
    acceptor.listen();

    acceptor.async_accept(new_session->getSocket(), std::bind(&Server::HandleAccept, this, std::placeholders::_1));
}

Server::~Server() = default;

void Server::HandleAccept(const boost::system::error_code& error)
{
    if (error)
    {
        Log() << error.message();
        return;
    }

    new_session->start();
    new_session = std::make_shared<Session>(io_service, command_parser, led);
    acceptor.async_accept(new_session->getSocket(), std::bind(&Server::HandleAccept, this, std::placeholders::_1));
}

void Server::Run()
{
    std::vector<std::shared_ptr<std::thread>> threads;
    for (decltype(thread_pool_size) i = 0; i < thread_pool_size; ++i)
    {
        threads.emplace_back(std::make_shared<std::thread>(
            std::bind(static_cast<size_t (boost::asio::io_service::*)()>(&boost::asio::io_service::run), &io_service)));
    }
    for (auto& thread : threads)
    {
        thread->join();
    }
}

void Server::Stop()
{
    io_service.stop();
}
