//main.cpp
#include <iostream>
#include <string>
#include "Library.h"
#include "Student.h"
#include "Faculty.h"
#include "Librarian.h"

// Function to show the main menu
void showMenu() {
    std::cout << "\nLibrary Management System\n";
    std::cout << "1. View Books\n";
    std::cout << "2. View Users\n";
    std::cout << "3. Add Book\n";
    std::cout << "4. Remove Book\n";
    std::cout << "5. Add User\n";
    std::cout << "6. Remove User\n";
    std::cout << "7. Borrow Book\n";
    std::cout << "8. Return Book\n";
    std::cout << "9. Pay Fine\n";
    std::cout << "10. Switch User Role\n";
    std::cout << "11. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    Library library;
    
    // Load existing data when the program starts
    library.loadData();

    // library.addBook(Book("C++ Primer", "Lippman", "Addison-Wesley", 2012, "9780321714114"));
    // library.addBook(Book("The Great Gatsby", "F. Scott Fitzgerald", "Scribner", 1925, "9780743273565"));
    // library.addBook(Book("1984", "George Orwell", "Secker & Warburg", 1949, "9780451524935"));
    // library.addBook(Book("To Kill a Mockingbird", "Harper Lee", "J.B. Lippincott & Co.", 1960, "9780061120084"));
    // library.addBook(Book("The Catcher in the Rye", "J.D. Salinger", "Little, Brown and Company", 1951, "9780316769488"));
    // library.addBook(Book("Moby Dick", "Herman Melville", "Harper & Brothers", 1851, "9781503280786"));
    // library.addBook(Book("Pride and Prejudice", "Jane Austen", "T. Egerton", 1813, "9780486295334"));
    // library.addBook(Book("The Lord of the Rings", "J.R.R. Tolkien", "Allen & Unwin", 1954, "9780261103252"));
    // library.addBook(Book("The Hobbit", "J.R.R. Tolkien", "George Allen & Unwin", 1937, "9780261103344"));
    // library.addBook(Book("Crime and Punishment", "Fyodor Dostoevsky", "The Russian Messenger", 1866, "9780140449136"));

    // // Adding 10 users to the library
    // library.addUser(new Student(1, "Alice"));
    // library.addUser(new Faculty(2, "Dr. Smith"));
    // library.addUser(new Librarian(3, "Mr. Adams"));
    // library.addUser(new Student(4, "Bob"));
    // library.addUser(new Faculty(5, "Dr. Johnson"));
    // library.addUser(new Librarian(6, "Mrs. Lee"));
    // library.addUser(new Student(7, "Charlie"));
    // library.addUser(new Faculty(8, "Dr. Brown"));
    // library.addUser(new Librarian(9, "Mr. White"));
    // library.addUser(new Student(10, "David"));

    int choice;
    bool exitFlag = false;

    User* currentUser = nullptr;  // Pointer to track the current user

    while (!exitFlag) {
        showMenu();  // Display the menu
        std::cin >> choice;

        switch (choice) {
            case 1:
                // View all books
                library.displayBooks();  // Displays all books in the library
                break;

            case 2:
                // View all users
                library.displayUsers();  // Displays all users in the library
                break;

            case 3: {
                // Add a new book
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
                library.addBook(newBook);  // Add the book to the library
                std::cout << "Book added successfully!\n";
                break;
            }

            case 4: {
                // Remove a book by title
                std::string title;
                std::cin.ignore();
                std::cout << "Enter book title to remove: ";
                std::getline(std::cin, title);
                library.removeBook(title);  // Removes the book by title
                break;
            }

            case 5: {
                // Add a new user
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
                    library.addUser(newUser);  // Add the user to the library
                    std::cout << "User added successfully!\n";
                } else {
                    std::cout << "Invalid role.\n";
                }
                break;
            }

            case 6: {
                // Remove a user by name
                std::string name;
                std::cin.ignore();
                std::cout << "Enter user name to remove: ";
                std::getline(std::cin, name);
                library.removeUser(name);  // Removes the user by name
                break;
            }

            case 7: {
                // Borrow a book
                if (currentUser == nullptr) {
                    std::cout << "No user selected. Please select a user first.\n";
                    break;
                }
                
                std::string title;
                std::cout << "Enter the title of the book you want to borrow: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                
                bool found = false;
                for (auto& book : library.getBooks()) {
                    if (book.getTitle() == title && book.isAvailable()) {
                        // Record the transaction and update book availability
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
                // Return a book
                if (currentUser == nullptr) {
                    std::cout << "No user selected. Please select a user first.\n";
                    break;
                }
                
                std::string title;
                std::cout << "Enter the title of the book you want to return: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                
                bool found = false;
                for (auto& book : library.getBooks()) {
                    if (book.getTitle() == title) {
                        library.returnBook(currentUser, &book);  // Return the book
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
                // Pay Fine (for student only)
                if (currentUser == nullptr) {
                    std::cout << "No user selected. Please select a user first.\n";
                    break;
                }
                
                currentUser->payFine();  // Call the payFine() method of the current user
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
                        currentUser = user;  // Switch to the new user
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
                exitFlag = true;  // Exit the program
                break;
            }

            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}
