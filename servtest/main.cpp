#include "Server.h"
#include "BookContainer.h"
#include <fstream>
#include <iostream>

std::pair<std::string, int> LoadConfig(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file) {
        throw std::runtime_error("Could not open config file.");
    }

    std::string ip;
    int port;
    std::string line;

    while (std::getline(file, line)) {
        if (line.find("IP=") == 0) {
            ip = line.substr(3);
        } else if (line.find("PORT=") == 0) {
            port = std::stoi(line.substr(5));
        }
    }

    if (ip.empty() || port == 0) {
        throw std::runtime_error("Invalid config file.");
    }

    return {ip, port};
}

int main() {
    try {
        auto [ip, port] = LoadConfig("config.env");

        BookContainer container;
        Server server(ip, port, container);

        server.Start();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
