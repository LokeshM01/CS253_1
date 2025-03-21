#include "Student.h"
#include <iostream>

void Student::borrowBook() {
    std::cout << name << " is borrowing a book." << std::endl;
}

void Student::returnBook(int overdueDays) {
    std::cout << name << " is returning a book." << std::endl;
    if (overdueDays > 15) {
        int fine = (overdueDays - 15) * 10;  // 10 rupees per day
        addFine(fine);
        std::cout << "Fine for overdue: " << fine << " rupees." << std::endl;
    }
}

void Student::displayInfo() const {
    std::cout << "Student ID: " << userId << ", Name: " << name << std::endl;
}

void Student::payFine() {
    std::cout << "Fine has been paid. You can now borrow books again." << std::endl;
    fineAmount = 0;  // Reset the fine amount to 0
}