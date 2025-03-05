#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>

class Book {
private:
    std::string title;
    std::string author;
    std::string publisher;
    int year;
    std::string isbn;
    bool available;  // true if available, false if borrowed

public:
    Book(std::string t, std::string a, std::string p, int y, std::string i)
        : title(t), author(a), publisher(p), year(y), isbn(i), available(true) {}

    void borrowBook();
    void returnBook();
    bool isAvailable() const { return available; }
    void displayInfo() const;

    // Add this accessor method to return the book title
    std::string getTitle() const { return title; }
};

#endif
