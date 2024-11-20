#pragma once
#include "ClientHandler.h"
#include <string>
#include <boost/asio.hpp>

class Server {
public:
    Server(const std::string& ip, int port, BookContainer& container);
    void Start();

private:
    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    ClientHandler client_handler_;
};
