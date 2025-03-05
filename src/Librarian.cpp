#include "Librarian.h"
#include <iostream>

void Librarian::borrowBook() {
    // Librarians cannot borrow books.
}

void Librarian::returnBook() {
    // Librarians cannot return books.
}

void Librarian::displayInfo() const {
    std::cout << "Librarian ID: " << userId << ", Name: " << name << std::endl;
}

void Librarian::manageBooks() {
    std::cout << "Managing books in the library." << std::endl;
}

void Librarian::manageUsers() {
    std::cout << "Managing users in the library." << std::endl;
}
