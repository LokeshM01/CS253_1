//User.cpp
#include "User.h"
#include <iostream>

void User::displayInfo() const {
    std::cout << "User ID: " << userId << ", Name: " << name << std::endl;
}
