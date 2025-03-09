//Librarian.h
#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include "User.h"

class Librarian : public User {
    public:
        Librarian(int id, std::string n) : User(id, n) {}
    
        void borrowBook() override {
            std::cout << "Librarians cannot borrow books.\n";
        }
    
        void returnBook(int overdueDays) override {
            std::cout << "Librarians cannot return books.\n";
        }
    
        void displayInfo() const override {
            std::cout << "Librarian ID: " << userId << ", Name: " << name << std::endl;
        }
    
        void payFine() override {
            std::cout << "Librarians don't have fines.\n";
        }
        
        std::string getRole() const override { return "Librarian"; }
    };
    

#endif
