#include "ClientHandler.h"
#include <boost/asio.hpp>
#include <iostream>

ClientHandler::ClientHandler(BookContainer& container) : _container(container), _response("") {
    AddCommand("ADD", [this](std::istream& is) {
        _container.AddBook(&is);
        _response = "Book added successfully.\n";
    });

    AddCommand("UPDATE", [this](std::istream& is) {
        if (_container.UpdateBook(&is)) {
            _response = "Book updated successfully.\n";
        } else {
            _response = "Book not found.\n";
        }
    });

    AddCommand("LIST", [this](std::istream&) {
        _response = _container.DisplayBooks();
    });

    AddCommand("DELETE", [this](std::istream& is) {
        int id;
        is >> id;
        if (_container.DeleteBook(id)) {
            _response = "Book deleted successfully.\n";
        } else {
            _response = "Book not found.\n";
        }
    });
}

void ClientHandler::HandleQuery(boost::asio::ip::tcp::socket& socket) {
    boost::asio::streambuf buffer;
    boost::asio::read_until(socket, buffer, "\n");
    std::istream is(&buffer);
    std::string command;
    std::getline(is, command);

    auto it = commandMap_.find(command);
    if (it != commandMap_.end()) {
        it->second(is);
    } else {
        _response = "Invalid command.\n";
    }

    boost::asio::write(socket, boost::asio::buffer(_response));
}

void ClientHandler::AddCommand(const std::string& command, std::function<void(std::istream&)> func) {
    commandMap_[command] = func;
}
