//Student.cpp
#include "Student.h"
#include <iostream>

void Student::borrowBook() {
    std::cout << name << " is borrowing a book." << std::endl;
}

void Student::returnBook(int overdueDays) {
    std::cout << name << " is returning a book." << std::endl;
    if (overdueDays > 0) {
        std::cout << "Fine for overdue: " << overdueDays * 10 << " rupees." << std::endl;
    }
}

void Student::displayInfo() const {
    std::cout << "Student ID: " << userId << ", Name: " << name << std::endl;
}

// Implement the payFine method
void Student::payFine() {
    std::cout << "Fine has been paid. You can now borrow books again." << std::endl;
    // If you want to clear the fine, you could set a fine variable to zero.
    // Assuming you have a `fineAmount` variable in the User base class.
    fineAmount = 0;  // Reset the fine amount to 0
}
