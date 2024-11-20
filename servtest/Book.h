#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;


class Book {
public:
    Book(int id, const string& title, const string& author, int year, const string& genre);
    Book(int id);
    Book();

    void SetId(istream* is);
    void SetData(istream* is);
    void UpdateDataByBook(const Book* book);

    int GetId() const;
    string DisplayInfo() const;

private:
    int _id;
    string _title;
    string _author;
    int _year;
    string _genre;
};
