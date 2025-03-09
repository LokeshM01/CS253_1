//Library.cpp
#include "Library.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Student.h"   // Include the Student header
#include "Faculty.h"   // Include the Faculty header
#include "Librarian.h" // Include the Librarian header
#include <algorithm>

// Constructor
Library::Library() {}

void Library::removeBook(const std::string& title) {
    auto it = std::remove_if(books.begin(), books.end(),
                             [&title](const Book& book) { return book.getTitle() == title; });
    if (it != books.end()) {
        books.erase(it, books.end());
        std::cout << "Book \"" << title << "\" has been removed.\n";
    } else {
        std::cout << "Book \"" << title << "\" not found.\n";
    }
}

// Add a book to the library
void Library::addBook(const Book& book) {
    books.push_back(book);
}

void Library::removeUser(const std::string& name) {
    auto it = std::remove_if(users.begin(), users.end(),
                             [&name](User* user) { return user->getName() == name; });
    if (it != users.end()) {
        users.erase(it, users.end());
        std::cout << "User \"" << name << "\" has been removed.\n";
    } else {
        std::cout << "User \"" << name << "\" not found.\n";
    }
}

// Add a user to the library
void Library::addUser(User* user) {
    users.push_back(user);
}

// Display books
void Library::displayBooks() const {
    for (const auto& book : books) {
        book.displayInfo();  // Display each book's info
    }
}

// Display users
void Library::displayUsers() const {
    for (const auto& user : users) {
        user->displayInfo();  // Display each user's info
    }
}

// Save library data (books and users) to files
void Library::saveData() {
    // Save books to a file
    std::ofstream bookFile("data/books.txt");
    if (bookFile.is_open()) {
        for (const auto& book : books) {
            Book::saveToFile(bookFile, book);  // Call the static saveToFile method
        }
        bookFile.close();
        std::cout << "Books data saved successfully!" << std::endl;
    } else {
        std::cout << "Failed to open books file for saving!" << std::endl;
    }

    // Save users to a file (using getName() to fetch user names)
    std::ofstream userFile("data/users.txt");
    if (userFile.is_open()) {
        for (const auto& user : users) {
            userFile << user->getRole() << ","
                     << user->getName() << std::endl;  // Get name of the user
        }
        userFile.close();
        std::cout << "Users data saved successfully!" << std::endl;
    } else {
        std::cout << "Failed to open users file for saving!" << std::endl;
    }

    // Save transactions to a file
    std::ofstream transactionFile("data/transactions.txt");
    if (transactionFile.is_open()) {
        for (const auto& transaction : transactions) {
            auto borrowTime = std::chrono::system_clock::to_time_t(transaction.getBorrowDate());
            transactionFile << transaction.getUser()->getName() << ","
                            << transaction.getBook()->getTitle() << ","
                            << std::ctime(&borrowTime) << std::endl;
        }
        transactionFile.close();
    } else {
        std::cout << "Failed to open transactions file for saving!" << std::endl;
    }
}

void Library::recordTransaction(User* user, Book* book) {
    Transaction transaction(user, book);
    transactions.push_back(transaction);
    book->borrowBook();  // Mark the book as borrowed
}

void Library::displayTransactions() const {
    for (const auto& transaction : transactions) {
        transaction.displayTransactionInfo();
    }
}

// Load library data (books and users) from files
void Library::loadData() {
    // Load books from a file
    std::ifstream bookFile("data/books.txt");
    std::string line;  // Declare line for books
    if (bookFile.is_open()) {
        Book book("", "", "", 0, "");
        while (Book::loadFromFile(bookFile, book)) {
            books.push_back(book);
        }
        bookFile.close();
        std::cout << "Books data loaded successfully!" << std::endl;
    } else {
        std::cout << "Failed to open books file for loading!" << std::endl;
    }

    // Load users from a file (use a different variable name for line)
    std::ifstream userFile("data/users.txt");
    std::string userLine;  // Use a different variable name for users
    if (userFile.is_open()) {
        while (getline(userFile, userLine)) {
            std::stringstream ss(userLine);
            std::string role, name;
            
            getline(ss, role, ',');
            getline(ss, name, ',');
            
            User* user = nullptr;
            if (role == "Student") {
                user = new Student(1, name);
            } else if (role == "Faculty") {
                user = new Faculty(2, name);
            } else if (role == "Librarian") {
                user = new Librarian(3, name);
            }
            
            if (user != nullptr) {
                users.push_back(user);
            }
        }
        userFile.close();
        std::cout << "Users data loaded successfully!" << std::endl;
    } else {
        std::cout << "Failed to open users file for loading!" << std::endl;
    }

    // Load transactions (use a different variable name for transactions)
    std::ifstream transactionFile("data/transactions.txt");
    std::string transactionLine;  // Use a different variable name for transactions
    if (transactionFile.is_open()) {
        while (std::getline(transactionFile, transactionLine)) {
            std::stringstream ss(transactionLine);
            std::string userName, bookTitle, borrowDateStr;
            std::getline(ss, userName, ',');
            std::getline(ss, bookTitle, ',');
            std::getline(ss, borrowDateStr);

            // Find the user and the book by their names and titles
            User* user = nullptr;
            Book* book = nullptr;
            for (auto& u : users) {
                if (u->getName() == userName) {
                    user = u;
                    break;
                }
            }
            for (auto& b : books) {
                if (b.getTitle() == bookTitle) {
                    book = &b;
                    break;
                }
            }

            if (user && book) {
                // Create the transaction from the file data
                Transaction transaction(user, book);
                transactions.push_back(transaction);
            }
        }
        transactionFile.close();
    } else {
        std::cout << "Failed to open transactions file for loading!" << std::endl;
    }
}

void Library::returnBook(User* user, Book* book) {
    // Find the transaction for the book being returned
    Transaction* transaction = nullptr;
    for (auto& t : transactions) {
        if (t.getUser() == user && t.getBook() == book) {
            transaction = &t;
            break;
        }
    }

    if (transaction == nullptr) {
        std::cout << "Transaction not found! This book was not borrowed by the user." << std::endl;
        return;
    }

    // Calculate overdue days
    int overdueDays = transaction->calculateOverdueDays();

    // Determine the maximum allowed borrowing period based on the user's role
    int maxBorrowingPeriod = 0;
    if (user->getRole() == "Student") {
        maxBorrowingPeriod = 15;
    } else if (user->getRole() == "Faculty") {
        maxBorrowingPeriod = 30;
    }

    // Calculate fines if the book is overdue
    int fine = 0;
    if (overdueDays > maxBorrowingPeriod) {
        fine = (overdueDays - maxBorrowingPeriod) * 10;  // 10 rupees per day
        std::cout << "Book is overdue by " << (overdueDays - maxBorrowingPeriod) << " days. Fine: " << fine << " rupees." << std::endl;
    } else {
        std::cout << "Book returned on time. No fine incurred." << std::endl;
    }

    // Update the book status
    book->returnBook();

    // Update the user's account
    user->returnBook(overdueDays);

    // Remove the transaction from the list
    auto it = std::remove(transactions.begin(), transactions.end(), *transaction);
    if (it != transactions.end()) {
        transactions.erase(it, transactions.end());
        std::cout << "Book returned successfully!" << std::endl;
    } else {
        std::cout << "Error: Transaction not found!" << std::endl;
    }
}


// Getter method to access books
const std::vector<Book>& Library::getBooks() const {
    return books;
}

// Getter method to access books (non-const version)
std::vector<Book>& Library::getBooks() {
    return books;
}

const std::vector<User*>& Library::getUsers() const {
    return users;
}
