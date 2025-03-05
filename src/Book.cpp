#include "Book.h"

// Save a book's data to a file
void Book::saveToFile(std::ofstream& file, const Book& book) {
    file << book.getTitle() << ","
         << book.getAuthor() << ","
         << book.getPublisher() << ","
         << book.getYear() << ","
         << book.getIsbn() << std::endl;
}

// Load a book's data from a file
bool Book::loadFromFile(std::ifstream& file, Book& book) {
    std::string title, author, publisher, isbn;
    int year;

    // Read a line and parse the data
    std::getline(file, title, ',');
    std::getline(file, author, ',');
    std::getline(file, publisher, ',');
    file >> year;
    file.ignore();  // Ignore the comma
    std::getline(file, isbn, '\n');

    // Check if we have valid data
    if (file.fail()) {
        return false;  // Failed to read
    }

    // Create a new Book object with the loaded data
    book = Book(title, author, publisher, year, isbn);
    return true;
}
