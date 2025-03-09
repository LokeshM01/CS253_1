//Faculty.h
#ifndef FACULTY_H
#define FACULTY_H

#include "User.h"

class Faculty : public User {
public:
    Faculty(int id, std::string n) : User(id, n) {}

    void borrowBook() override;
    void returnBook(int overdueDays) override;
    void displayInfo() const override;
    void payFine() override;  // Declare payFine() for Faculty class
    
    std::string getRole() const override { return "Faculty"; }
};

#endif
