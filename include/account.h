#pragma once
#include <string>

class Account {
private:
int accountNumber;
std::string holderName;
std::string pin; // stored as plain string (hashed in real systems)
double balance;
std::string accountType; // "savings" or "current"

public:
// Constructors
Account();
Account(int accNo, const std::string& name, const std::string& pin,
double initialBalance, const std::string& type);

// Getters
int getAccountNumber() const;
std::string getHolderName() const;
double getBalance() const;
std::string getAccountType() const;

// Operations
bool validatePin(const std::string& inputPin) const;
bool deposit(double amount);
bool withdraw(double amount);
void displayInfo() const;

// File serialization
std::string serialize() const;
static Account deserialize(const std::string& line);
};
