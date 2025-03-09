#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User {
protected:
    int userId;
    std::string name;
    int fineAmount;  // To track fines (if any)
    int borrowedBooksCount;  // To track the number of books borrowed

public:
    User(int id, std::string n) : userId(id), name(n), fineAmount(0), borrowedBooksCount(0) {}

    virtual void borrowBook() = 0;  
    virtual void returnBook(int overdueDays) = 0;  
    virtual void displayInfo() const = 0;
    virtual void payFine() = 0;

    virtual std::string getRole() const = 0;  // Virtual method to get the role

    // Getter method for user name
    std::string getName() const {
        return name;
    }

    // Add a fine to the user's account
    void addFine(int amount) {
        fineAmount += amount;
    }

    // Get the current fine amount
    int getFineAmount() const {
        return fineAmount;
    }

    // Get the number of books borrowed
    int getBorrowedBooksCount() const {
        return borrowedBooksCount;
    }

    // Increment the borrowed books count
    void incrementBorrowedBooksCount() {
        borrowedBooksCount++;
    }

    // Decrement the borrowed books count
    void decrementBorrowedBooksCount() {
        if (borrowedBooksCount > 0) {
            borrowedBooksCount--;
        }
    }

    virtual ~User() = default;  // Virtual destructor
};

#endif