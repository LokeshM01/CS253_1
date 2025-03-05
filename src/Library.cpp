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
}

// Load library data (books and users) from files
void Library::loadData() {
    // Load books from a file
    std::ifstream bookFile("books.txt");
    std::string line;
    if (bookFile.is_open()) {
        while (getline(bookFile, line)) {
            std::stringstream ss(line);
            Book book("", "", "", 0, "");
            if (Book::loadFromFile(bookFile, book)) {
                books.push_back(book);
            }
        }
        bookFile.close();
        std::cout << "Books data loaded successfully!" << std::endl;
    } else {
        std::cout << "Failed to open books file for loading!" << std::endl;
    }

    // Load users from a file (similar process as books)
    std::ifstream userFile("users.txt");
    if (userFile.is_open()) {
        while (getline(userFile, line)) {
            std::stringstream ss(line);
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
