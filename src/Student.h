// src/Student.h
#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"

class Student : public User {
    public:
        Student(int id, std::string n) : User(id, n) {}
    
        void borrowBook() override;
        void returnBook(int overdueDays) override;
        void displayInfo() const override;
        void payFine() override;
        
        std::string getRole() const override { return "Student"; }
    };
    

#endif
