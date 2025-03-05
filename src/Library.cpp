// Library.cpp
#include "Library.h"



Library::Library() {
    // Constructor implementation (optional)
}

void Library::addBook(const Book& book) {
    books.push_back(book);
}

void Library::addUser(User* user) {
    users.push_back(user);
}

void Library::displayBooks() const {
    for (const auto& book : books) {
        book.displayInfo();  // Display each book's info
    }
}

void Library::displayUsers() const {
    for (const auto& user : users) {
        user->displayInfo();  // Display each user's info
    }
}

// Definition of the const version of getBooks
const std::vector<Book>& Library::getBooks() const {
    return books;
}

// Definition of the non-const version of getBooks
std::vector<Book>& Library::getBooks() {
    return books;
}
