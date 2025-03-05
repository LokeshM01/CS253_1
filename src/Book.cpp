#include "Book.h"

void Book::borrowBook() {
    if (available) {
        available = false;
        std::cout << "Book borrowed: " << title << std::endl;
    } else {
        std::cout << "Book is not available!" << std::endl;
    }
}

void Book::returnBook() {
    available = true;
    std::cout << "Book returned: " << title << std::endl;
}

void Book::displayInfo() const {
    std::cout << "Book: " << title << ", Author: " << author << ", Publisher: " << publisher
              << ", Year: " << year << ", ISBN: " << isbn << ", Available: " << (available ? "Yes" : "No") << std::endl;
}
