#include "Utils.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

#ifdef _WIN32
  #include <conio.h>
  #include <windows.h>
#else
  #include <termios.h>
  #include <unistd.h>
#endif

namespace Utils {

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen() {
    std::cout << "\n  Press Enter to continue...";
    std::cin.ignore(1000, '\n');
    std::cin.get();
}

void printDivider() {
    std::cout << "  " << std::string(52, '=') << "\n";
}

void printHeader(const std::string& title) {
    clearScreen();
    printDivider();
    int padding = (52 - (int)title.size()) / 2;
    std::cout << "  " << std::string(padding, ' ') << title << "\n";
    printDivider();
    std::cout << "\n";
}

std::string maskInput() {
    std::string input;
#ifdef _WIN32
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!input.empty()) { input.pop_back(); std::cout << "\b \b"; }
        } else {
            input += ch;
            std::cout << '*';
        }
    }
    std::cout << "\n";
#else
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    std::getline(std::cin, input);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    std::cout << "\n";
#endif
    return input;
}

bool isValidAmount(double amount) {
    return amount > 0;
}

bool isValidName(const std::string& name) {
    if (name.size() < 2) return false;
    return std::all_of(name.begin(), name.end(), [](char c){
        return std::isalpha(c) || c == ' ';
    });
}

bool isValidPin(const std::string& pin) {
    if (pin.size() < 4 || pin.size() > 6) return false;
    return std::all_of(pin.begin(), pin.end(), ::isdigit);
}

} // namespace Utils
