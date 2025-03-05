#include "Account.h"
#include <algorithm>  // for std::find

void Account::borrowBook(Book* book) {
    if (book->isAvailable()) {
        borrowedBooks.push_back(book);
        book->borrowBook();
    } else {
        std::cout << "Book is not available!" << std::endl;
    }
}

void Account::returnBook(Book* book, int overdueDays) {
    // Search for the book in the borrowedBooks vector
    auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), book);
    if (it != borrowedBooks.end()) {
        borrowedBooks.erase(it);  // Remove the book from the borrowed list
        book->returnBook();       // Return the book (change its status)
        if (overdueDays > 0) {
            fineAmount += overdueDays * 10;
            std::cout << "Fine for overdue: " << fineAmount << " rupees." << std::endl;
        }
    } else {
        std::cout << "This book was not borrowed!" << std::endl;
    }
}

void Account::payFine() {
    fineAmount = 0;
    std::cout << "Fine paid. Thank you!" << std::endl;
}

void Account::displayAccountInfo() const {
    std::cout << "Total fine: " << fineAmount << " rupees." << std::endl;
}
