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

    // Calculate the number of overdue days
    int calculateOverdueDays() const {
        auto now = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::hours>(now - borrowDate);
        int days = duration.count() / 24;  // Convert hours to days
        return days;
    }

    void displayTransactionInfo() const {
        auto borrowTime = std::chrono::system_clock::to_time_t(borrowDate);
        std::cout << "User: " << user->getName() << " borrowed \""
                  << book->getTitle() << "\" on " << std::ctime(&borrowTime);
    }

    // Define the equality operator
    bool operator==(const Transaction& other) const {
        return user == other.user && book == other.book;
    }
};

#endif