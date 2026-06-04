#pragma once
#include <string>

namespace Utils {
    void clearScreen();
    void pauseScreen();
    void printHeader(const std::string& title);
    void printDivider();
    std::string maskInput();          // reads password without echo
    bool isValidAmount(double amount);
    bool isValidName(const std::string& name);
    bool isValidPin(const std::string& pin);
}
