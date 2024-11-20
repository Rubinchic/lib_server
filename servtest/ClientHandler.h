#pragma once
#include "BookContainer.h"
#include <unordered_map>
#include <functional>
#include <boost/asio.hpp>

class ClientHandler {
public:
    explicit ClientHandler(BookContainer& container);

    void HandleQuery(boost::asio::ip::tcp::socket& socket);

private:
    BookContainer& _container;
    std::string _response;
    std::unordered_map<std::string, std::function<void(std::istream&)>> commandMap_;

    void AddCommand(const std::string& command, std::function<void(std::istream&)> func);
};
