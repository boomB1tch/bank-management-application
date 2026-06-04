#include "Account.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <stdexcept>

Account::Account()
    : accountNumber(0), holderName(""), pin(""), balance(0.0), accountType("savings") {}

Account::Account(int accNo, const std::string& name, const std::string& p,
                 double initialBalance, const std::string& type)
    : accountNumber(accNo), holderName(name), pin(p),
      balance(initialBalance), accountType(type) {}

int Account::getAccountNumber() const { return accountNumber; }
std::string Account::getHolderName() const { return holderName; }
double Account::getBalance() const { return balance; }
std::string Account::getAccountType() const { return accountType; }

bool Account::validatePin(const std::string& inputPin) const {
    return pin == inputPin;
}

bool Account::deposit(double amount) {
    if (amount <= 0) return false;
    balance += amount;
    return true;
}

bool Account::withdraw(double amount) {
    if (amount <= 0 || amount > balance) return false;
    balance -= amount;
    return true;
}

void Account::displayInfo() const {
    std::cout << std::left
              << "  Account No : " << accountNumber << "\n"
              << "  Name       : " << holderName << "\n"
              << "  Type       : " << accountType << "\n"
              << "  Balance    : INR " << std::fixed << std::setprecision(2) << balance << "\n";
}

// Format: accountNumber|holderName|pin|balance|accountType
std::string Account::serialize() const {
    std::ostringstream oss;
    oss << accountNumber << "|" << holderName << "|" << pin << "|"
        << std::fixed << std::setprecision(2) << balance << "|" << accountType;
    return oss.str();
}

Account Account::deserialize(const std::string& line) {

    std::istringstream iss(line);
    std::string token;
    std::vector<std::string> parts;
    while (std::getline(iss, token, '|'))
        parts.push_back(token);

    if (parts.size() != 5)
        throw std::runtime_error("Corrupted account record: " + line);

    return Account(
        std::stoi(parts[0]),
        parts[1],
        parts[2],
        std::stod(parts[3]),
        parts[4]
    );
}
