#include "Faculty.h"
#include <iostream>

void Faculty::borrowBook() {
    std::cout << name << " is borrowing a book." << std::endl;
}

void Faculty::returnBook(int overdueDays) {
    std::cout << name << " is returning a book." << std::endl;
    if (overdueDays > 0) {
        std::cout << "Faculty members do not incur fines for overdue books.\n";
    }
}

void Faculty::displayInfo() const {
    std::cout << "Faculty ID: " << userId << ", Name: " << name << std::endl;
}

void Faculty::payFine() {
    std::cout << "Faculty members do not have fines.\n";  // Display message that faculty do not have fines
}
