#include "Book.h"
#include <limits>
using namespace std;


Book::Book(int id, const string& title, const string& author, int year, const string& genre)
    : _id(id), _title(title), _author(author), _year(year), _genre(genre) {}

Book::Book(int id) : _id(id) {}

Book::Book() {}

void Book::SetId(istream* is) {
    *is >> _id;
    is->ignore();
}

void Book::SetData(std::istream* is) {
    getline(*is, _title);
    getline(*is, _author);
    *is >> _year;
    is->ignore(numeric_limits<streamsize>::max(), '\n');
    getline(*is, _genre);
}

void Book::UpdateDataByBook(const Book* book) {
    _title = book->_title;
    _author = book->_author;
    _year = book->_year;
    _genre = book->_genre;
}

int Book::GetId() const {
    return _id;
}

std::string Book::DisplayInfo() const {
    return "ID: " + to_string(_id) +
           ", Title: " + _title +
           ", Author: " + _author +
           ", Year: " + to_string(_year) +
           ", Genre: " + _genre + "\n";
}
