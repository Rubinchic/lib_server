#include "BookContainer.h"
#include <algorithm>

void BookContainer::AddBook(std::istream* is) {
    Book book(++current_id);
    book.SetData(is);
    books.push_back(book);
}

std::string BookContainer::DisplayBooks() const {
    std::string result;
    for (const auto& book : books) {
        result += book.DisplayInfo();
    }
    return result.empty() ? "No books available." : result;
}

bool BookContainer::UpdateBook(std::istream* is) {
    Book updatedBook;
    updatedBook.SetId(is);
    updatedBook.SetData(is);
    for (auto& book : books) {
        if (book.GetId() == updatedBook.GetId()) {
            book.UpdateDataByBook(&updatedBook);
            return true;
        }
    }
    return false;
}

bool BookContainer::DeleteBook(int id) {
    auto it = std::remove_if(books.begin(), books.end(),
                             [id](const Book& book) { return book.GetId() == id; });

    if (it != books.end()) {
        books.erase(it, books.end());
        return true;
    }
    return false;
}
