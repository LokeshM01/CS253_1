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
    std::cout << "3. Borrow Book\n";
    std::cout << "4. Return Book\n";
    std::cout << "5. Pay Fine\n";
    std::cout << "6. Switch User Role\n";
    std::cout << "7. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    Library library;

    // Create some initial books and users
    library.addBook(Book("C++ Primer", "Lippman", "Addison-Wesley", 2012, "9780321714114"));
    library.addBook(Book("The Great Gatsby", "F. Scott Fitzgerald", "Scribner", 1925, "9780743273565"));
    
    Student* student1 = new Student(1, "Alice");
    Faculty* faculty1 = new Faculty(2, "Dr. Smith");
    Librarian* librarian1 = new Librarian(3, "Mr. Adams");

    // Default user role is Student
    User* currentUser = student1;

    library.addUser(student1);
    library.addUser(faculty1);
    library.addUser(librarian1);

    int choice;
    bool exitFlag = false;

    while (!exitFlag) {
        showMenu();  // Display the menu
        std::cin >> choice;

        switch (choice) {
            case 1: {
                // View books
                for (const auto& book : library.getBooks()) {
                    book.displayInfo();
                }
                break;
            }
            case 2: {
                // View users
                library.displayUsers();
                break;
            }
            case 3: {
                std::cout << "Enter book title to borrow: ";
                std::string title;
                std::cin.ignore();
                std::getline(std::cin, title);
                
                currentUser->borrowBook();  // Borrowing as current user
                break;
            }
            case 4: {
                std::cout << "Enter book title to return: ";
                std::string title;
                std::cin.ignore();
                std::getline(std::cin, title);
                
                currentUser->returnBook(5);  // Return as current user
                break;
            }
            case 5: {
                currentUser->payFine();  // Pay fine as current user
                break;
            }
            case 6: {
                // Switch user role
                std::cout << "Current user is a " << currentUser->getRole() << ".\n";
                std::cout << "Choose new role:\n";
                std::cout << "1. Student\n";
                std::cout << "2. Faculty\n";
                std::cout << "3. Librarian\n";
                int newRoleChoice;
                std::cin >> newRoleChoice;

                // Switch user based on choice
                if (newRoleChoice == 1) {
                    currentUser = student1;
                } else if (newRoleChoice == 2) {
                    currentUser = faculty1;
                } else if (newRoleChoice == 3) {
                    currentUser = librarian1;
                }
                std::cout << "Switched to " << currentUser->getRole() << ".\n";
                break;
            }
            case 7: {
                std::cout << "Exiting the program.\n";
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
