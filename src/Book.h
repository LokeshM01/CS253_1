//Book.h
#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>
#include <fstream>  // For file handling

class Book {
private:
    std::string title;
    std::string author;
    std::string publisher;
    int year;
    std::string isbn;
    bool available;  // true if available, false if borrowed

public:
    Book(std::string t, std::string a, std::string p, int y, std::string i)
        : title(t), author(a), publisher(p), year(y), isbn(i), available(true) {}

    // Getter methods
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    std::string getPublisher() const { return publisher; }
    int getYear() const { return year; }
    std::string getIsbn() const { return isbn; }
    bool isAvailable() const { return available; }
    

    // Set the availability status
    void borrowBook() {
        if (available) {
            available = false;
            std::cout << "Book borrowed: " << title << std::endl;
        } else {
            std::cout << "Book is not available!" << std::endl;
        }
    }

    void returnBook() {
        available = true;
        std::cout << "Book returned: " << title << std::endl;
    }

    void displayInfo() const {
        std::cout << "Book: " << title << ", Author: " << author << ", Publisher: " << publisher
                  << ", Year: " << year << ", ISBN: " << isbn << ", Available: " << (available ? "Yes" : "No") << std::endl;
    }

    // I/O methods for saving and loading data
    static void saveToFile(std::ofstream& file, const Book& book);
    static bool loadFromFile(std::ifstream& file, Book& book);
};

#endif
