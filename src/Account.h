#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <vector>
#include <iostream>
#include "Book.h"

class Account {
private:
    std::vector<Book*> borrowedBooks;
    int fineAmount;

public:
    Account() : fineAmount(0) {}

    void borrowBook(Book* book);
    void returnBook(Book* book, int overdueDays);
    void payFine();
    void displayAccountInfo() const;
    bool hasOutstandingFines() const { return fineAmount > 0; }
};

#endif
