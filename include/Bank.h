#pragma once
#include "Account.h"
#include <vector>
#include <string>

class Bank {
private:
    std::vector<Account> accounts;
    std::string dataFile;
    int nextAccountNumber;

    void loadFromFile();
    void saveToFile() const;
    int findAccountIndex(int accountNumber) const;

public:
    explicit Bank(const std::string& filename = "data/accounts.dat");

    // Account management
    int createAccount(const std::string& name, const std::string& pin,
                      double initialDeposit, const std::string& type);
    bool deleteAccount(int accountNumber, const std::string& pin);

    // Transactions
    bool deposit(int accountNumber, double amount);
    bool withdraw(int accountNumber, const std::string& pin, double amount);
    bool transfer(int fromAccount, const std::string& pin,
                  int toAccount, double amount);

    // Queries
    void checkBalance(int accountNumber, const std::string& pin) const;
    void displayAccount(int accountNumber) const;
    void displayAllAccounts() const;

    bool accountExists(int accountNumber) const;
};
