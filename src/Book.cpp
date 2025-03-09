#include "Book.h"
#include <sstream>
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
    std::string line;
    if (!std::getline(file, line)) return false; // Read a full line

    std::stringstream ss(line);
    std::string title, author, publisher, isbn;
    int year;

    // Extract values using stringstream
    std::getline(ss, title, ',');
    std::getline(ss, author, ',');
    std::getline(ss, publisher, ',');
    ss >> year;
    ss.ignore(); // Ignore any delimiter after year
    std::getline(ss, isbn, '\n');

    // Check if values are valid
    if (ss.fail()) {
        return false;  // Failed to parse
    }

    // Create the book object with extracted values
    book = Book(title, author, publisher, year, isbn);
    return true;
}

