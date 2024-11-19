#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>

using namespace std;
using boost::asio::ip::tcp;

class Book {
public:
    int id;
    string title;
    string author;
    int year;
    string genre;

    Book(int id, const string& title, const string& author, int year, const string& genre)
        : id(id), title(title), author(author), year(year), genre(genre) {}
};

class book_container {
private:
    vector<Book> books;
    int next_id;

public:
    book_container() : next_id(1) {}

    void add_book(const string& title, const string& author, int year, const string& genre) {
        books.emplace_back(next_id++, title, author, year, genre);
    }

    string list_books() const {
        string result;
        for (const auto& book : books) {
            result += "ID: " + to_string(book.id) + ", Title: " + book.title + ", Author: " + book.author + ", Year: " + to_string(book.year) + ", Genre: " + book.genre + "\n";
        }
        return result.empty() ? "No books available." : result;
    }

    bool update_book(int id, const string& title, const string& author, int year, const string& genre) {
        for (auto& book : books) {
            if (book.id == id) {
                book.title = title;
                book.author = author;
                book.year = year;
                book.genre = genre;
                return true;
            }
        }
        return false;
    }

    bool delete_book(int id) {
        auto it = remove_if(books.begin(), books.end(), [id](const Book& book) { return book.id == id; });
        if (it != books.end()) {
            books.erase(it, books.end());
            return true;
        }
        return false;
    }
};

bool read_conf(string& ip, int& port) {
    ifstream configFile("C:/Users/valer/ClionProjects/servtest/config.txt");

    if (!configFile.is_open()) {
        cerr << "Failed to open config.txt" << endl;
        return false;
    }

    string line;
    while (getline(configFile, line)) {
        if (line.find("ip=") == 0) {
            ip = line.substr(3);
        } else if (line.find("port=") == 0) {
            port = stoi(line.substr(5));
        }
    }
    configFile.close();
    return !ip.empty() && port != 0;
}

void handle_client(tcp::socket& socket, book_container& container) {
    boost::asio::streambuf buffer;
    boost::asio::read_until(socket, buffer, "\n");
    istream is(&buffer);
    string command;
    getline(is, command);

    string response;
    if (command == "ADD") {
        string title, author, genre;
        int year;
        getline(is, title);
        getline(is, author);
        is >> year;
        is.ignore();
        getline(is, genre);
        container.add_book(title, author, year, genre);
        response = "Book added successfully.\n";
    } else if (command == "LIST") {
        response = container.list_books();
    } else if (command == "UPDATE") {
        int id, year;
        string title, author, genre;
        is >> id;
        is.ignore();
        getline(is, title);
        getline(is, author);
        is >> year;
        is.ignore();
        getline(is, genre);
        if (container.update_book(id, title, author, year, genre)) {
            response = "Book updated successfully.\n";
        } else {
            response = "Book not found.\n";
        }
    } else if (command == "DELETE") {
        int id;
        is >> id;
        if (container.delete_book(id)) {
            response = "Book deleted successfully.\n";
        } else {
            response = "Book not found.\n";
        }
    } else {
        response = "Invalid command.\n";
    }
    boost::asio::write(socket, boost::asio::buffer(response));
}

int main() {
    string ip;
    int port;

    if (!read_conf(ip, port)) {
        cerr << "Error reading config file. Ensure 'config.txt' has 'ip' and 'port' entries." << endl;
        return 1;
    }

    cout << "Starting server at " << ip << ":" << port << "..." << endl;

    boost::asio::io_context io_context;
    tcp::acceptor acceptor(io_context, tcp::endpoint(boost::asio::ip::make_address(ip), port));

    book_container container;

    while (true) {
        tcp::socket socket(io_context);
        acceptor.accept(socket);
        handle_client(socket, container);
    }
}
