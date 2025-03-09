#include <iostream>
#include <string>
#include "Library.h"
#include "Student.h"
#include "Faculty.h"
#include "Librarian.h"

// Function to show the main menu based on the user's role
void showMenu(User* currentUser) {
    std::cout << "\nLibrary Management System\n";
    std::cout << "1. View Books\n";
    std::cout << "2. View Users\n";

    if (currentUser->getRole() == "Librarian") {
        std::cout << "3. Add Book\n";
        std::cout << "4. Remove Book\n";
        std::cout << "5. Add User\n";
        std::cout << "6. Remove User\n";
    }

    if (currentUser->getRole() == "Student" || currentUser->getRole() == "Faculty") {
        std::cout << "7. Borrow Book\n";
        std::cout << "8. Return Book\n";
        std::cout << "9. Pay Fine\n";
    }

    std::cout << "10. Switch User Role\n";
    std::cout << "11. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    Library library;
    
    // Load existing data when the program starts
    library.loadData();

    int choice;
    bool exitFlag = false;

    User* currentUser = nullptr;  // Pointer to track the current user

    // Default user for testing (you can modify this)
    currentUser = new Student(1, "Alice");

    while (!exitFlag) {
        showMenu(currentUser);  // Display the menu based on the user's role
        std::cin >> choice;

        switch (choice) {
            case 1:
                // View all books
                library.displayBooks();
                break;

            case 2:
                // View all users
                library.displayUsers();
                break;

            case 3: {
                // Add a new book (Librarian only)
                if (currentUser->getRole() != "Librarian") {
                    std::cout << "You do not have permission to add books.\n";
                    break;
                }

                std::string title, author, publisher, isbn;
                int year;
                std::cin.ignore();  // Ignore any leftover newline characters
                std::cout << "Enter book title: ";
                std::getline(std::cin, title);
                std::cout << "Enter author: ";
                std::getline(std::cin, author);
                std::cout << "Enter publisher: ";
                std::getline(std::cin, publisher);
                std::cout << "Enter year: ";
                std::cin >> year;
                std::cout << "Enter ISBN: ";
                std::cin >> isbn;
                Book newBook(title, author, publisher, year, isbn);
                library.addBook(newBook);
                std::cout << "Book added successfully!\n";
                break;
            }

            case 4: {
                // Remove a book by title (Librarian only)
                if (currentUser->getRole() != "Librarian") {
                    std::cout << "You do not have permission to remove books.\n";
                    break;
                }

                std::string title;
                std::cin.ignore();
                std::cout << "Enter book title to remove: ";
                std::getline(std::cin, title);
                library.removeBook(title);
                break;
            }

            case 5: {
                // Add a new user (Librarian only)
                if (currentUser->getRole() != "Librarian") {
                    std::cout << "You do not have permission to add users.\n";
                    break;
                }

                std::string name, role;
                std::cin.ignore();
                std::cout << "Enter user name: ";
                std::getline(std::cin, name);
                std::cout << "Enter role (Student, Faculty, Librarian): ";
                std::getline(std::cin, role);
                User* newUser = nullptr;
                if (role == "Student") {
                    newUser = new Student(1, name);
                } else if (role == "Faculty") {
                    newUser = new Faculty(2, name);
                } else if (role == "Librarian") {
                    newUser = new Librarian(3, name);
                }
                if (newUser != nullptr) {
                    library.addUser(newUser);
                    std::cout << "User added successfully!\n";
                } else {
                    std::cout << "Invalid role.\n";
                }
                break;
            }

            case 6: {
                // Remove a user by name (Librarian only)
                if (currentUser->getRole() != "Librarian") {
                    std::cout << "You do not have permission to remove users.\n";
                    break;
                }

                std::string name;
                std::cin.ignore();
                std::cout << "Enter user name to remove: ";
                std::getline(std::cin, name);
                library.removeUser(name);
                break;
            }

            case 7: {
                // Borrow a book (Student and Faculty only)
                if (currentUser->getRole() != "Student" && currentUser->getRole() != "Faculty") {
                    std::cout << "You do not have permission to borrow books.\n";
                    break;
                }

                std::string title;
                std::cout << "Enter the title of the book you want to borrow: ";
                std::cin.ignore();
                std::getline(std::cin, title);

                bool found = false;
                for (auto& book : library.getBooks()) {
                    if (book.getTitle() == title && book.isAvailable()) {
                        library.recordTransaction(currentUser, &book);
                        found = true;
                        std::cout << "Book borrowed successfully!\n";
                        break;
                    }
                }
                if (!found) {
                    std::cout << "Book not available or not found.\n";
                }
                break;
            }

            case 8: {
                // Return a book (Student and Faculty only)
                if (currentUser->getRole() != "Student" && currentUser->getRole() != "Faculty") {
                    std::cout << "You do not have permission to return books.\n";
                    break;
                }

                std::string title;
                std::cout << "Enter the title of the book you want to return: ";
                std::cin.ignore();
                std::getline(std::cin, title);

                bool found = false;
                for (auto& book : library.getBooks()) {
                    if (book.getTitle() == title) {
                        bool returned = library.returnBook(currentUser, &book);
                        if (!returned) {
                            std::cout << "You have an outstanding fine. Please pay the fine to return the book.\n";
                            std::cout << "Do you want to pay the fine now? (yes/no): ";
                            std::string response;
                            std::cin >> response;
                            if (response == "yes") {
                                currentUser->payFine();
                                std::cout << "Fine paid. Attempting to return the book again...\n";
                                returned = library.returnBook(currentUser, &book);
                                if (returned) {
                                    std::cout << "Book returned successfully after paying the fine.\n";
                                } else {
                                    std::cout << "Failed to return the book.\n";
                                }
                            } else {
                                std::cout << "Fine not paid. Book cannot be returned.\n";
                            }
                        }
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    std::cout << "Book not found.\n";
                }
                break;
            }

            case 9: {
                // Pay Fine (Student and Faculty only)
                if (currentUser->getRole() != "Student" && currentUser->getRole() != "Faculty") {
                    std::cout << "You do not have permission to pay fines.\n";
                    break;
                }

                currentUser->payFine();
                break;
            }

            case 10: {
                // Switch user role
                std::cout << "Enter user name to switch to: ";
                std::string name;
                std::cin.ignore();
                std::getline(std::cin, name);

                // Find the user in the library
                bool userFound = false;
                for (auto& user : library.getUsers()) {
                    if (user->getName() == name) {
                        currentUser = user;
                        std::cout << "Switched to user: " << currentUser->getName() << "\n";
                        userFound = true;
                        break;
                    }
                }

                if (!userFound) {
                    std::cout << "User not found.\n";
                }
                break;
            }

            case 11: {
                // Save data before exiting
                library.saveData();
                std::cout << "Exiting program.\n";
                exitFlag = true;
                break;
            }

            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}