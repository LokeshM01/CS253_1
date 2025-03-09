#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include "Book.h"
#include "User.h"
#include "Transaction.h"

class Library {
private:
    std::vector<Book> books;
    std::vector<User*> users;  // List of users in the library
    std::vector<Transaction> transactions;

public:
    Library();
    void addBook(const Book& book);
    void removeBook(const std::string& title);
    void addUser(User* user);
    void removeUser(const std::string& name);
    void displayBooks() const;
    void displayUsers() const;
    void saveData();
    void loadData();
    void recordTransaction(User* user, Book* book);
    void displayTransactions() const;

    // Update the returnBook function declaration (remove overdueDays parameter)
    void returnBook(User* user, Book* book);

    // Getter methods for books and users
    const std::vector<Book>& getBooks() const;
    std::vector<Book>& getBooks();
    const std::vector<User*>& getUsers() const;  // Getter for users
};

#endif