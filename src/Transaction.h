#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "User.h"
#include "Book.h"
#include <chrono>
#include <iostream>

class Transaction {
private:
    User* user;  // Pointer to the user who borrowed the book
    Book* book;  // Pointer to the borrowed book
    std::chrono::system_clock::time_point borrowDate;  // Borrow date

public:
    Transaction(User* user, Book* book)
        : user(user), book(book), borrowDate(std::chrono::system_clock::now()) {}

    User* getUser() const { return user; }
    Book* getBook() const { return book; }
    std::chrono::system_clock::time_point getBorrowDate() const { return borrowDate; }

    void displayTransactionInfo() const {
        auto borrowTime = std::chrono::system_clock::to_time_t(borrowDate);
        std::cout << "User: " << user->getName() << " borrowed \""
                  << book->getTitle() << "\" on " << std::ctime(&borrowTime);
    }
};

#endif
