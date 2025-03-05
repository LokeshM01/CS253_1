#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User {
protected:
    int userId;
    std::string name;
    int fineAmount;  // To track fines (if any)

public:
    User(int id, std::string n) : userId(id), name(n), fineAmount(0) {}

    virtual void borrowBook() = 0;  
    virtual void returnBook(int overdueDays) = 0;  
    virtual void displayInfo() const = 0;
    virtual void payFine() = 0;

    virtual std::string getRole() const = 0;  // Virtual method to get the role

    // Getter method for user name
    std::string getName() const {
        return name;
    }

    virtual ~User() = default;  // Virtual destructor
};

#endif
