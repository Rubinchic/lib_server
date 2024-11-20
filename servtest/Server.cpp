#include "Server.h"
#include <iostream>

Server::Server(const std::string& ip, int port, BookContainer& container)
    : acceptor_(io_context_, boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(ip), port)),
      client_handler_(container) {
    std::cout << "Starting server at " << ip << ":" << port << "..." << std::endl;
}

void Server::Start() {
    while (true) {
        boost::asio::ip::tcp::socket socket(io_context_);
        acceptor_.accept(socket);
        client_handler_.HandleQuery(socket);
    }
}
