#pragma once
#include "Book.h"
#include <vector>
#include <string>
#include <ranges>

class BookContainer {
public:
    void AddBook(std::istream* is);
    std::string DisplayBooks() const;
    bool UpdateBook(std::istream* is);
    bool DeleteBook(int id);

private:
    std::vector<Book> books;
    int current_id = 0;
};
