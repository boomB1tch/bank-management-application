#include "Bank.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>

Bank::Bank(const std::string& filename)
    : dataFile(filename), nextAccountNumber(100001) {
    loadFromFile();
}

void Bank::loadFromFile() {
    std::ifstream file(dataFile);
    if (!file.is_open()) return; // first run — no file yet

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        try {
            Account acc = Account::deserialize(line);
            accounts.push_back(acc);
            if (acc.getAccountNumber() >= nextAccountNumber)
                nextAccountNumber = acc.getAccountNumber() + 1;
        } catch (const std::exception& e) {
            std::cerr << "[Warning] Skipping bad record: " << e.what() << "\n";
        }
    }
}

void Bank::saveToFile() const {
    std::ofstream file(dataFile, std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "[Error] Cannot open data file for writing.\n";
        return;
    }
    for (const auto& acc : accounts)
        file << acc.serialize() << "\n";
}

int Bank::findAccountIndex(int accountNumber) const {
    for (int i = 0; i < (int)accounts.size(); ++i)
        if (accounts[i].getAccountNumber() == accountNumber) return i;
    return -1;
}

bool Bank::accountExists(int accountNumber) const {
    return findAccountIndex(accountNumber) != -1;
}

// ── Account Management ─────────────────────────────────────────────────────

int Bank::createAccount(const std::string& name, const std::string& pin,
                        double initialDeposit, const std::string& type) {
    int accNo = nextAccountNumber++;
    accounts.emplace_back(accNo, name, pin, initialDeposit, type);
    saveToFile();
    return accNo;
}

bool Bank::deleteAccount(int accountNumber, const std::string& pin) {
    int idx = findAccountIndex(accountNumber);
    if (idx == -1) return false;
    if (!accounts[idx].validatePin(pin)) return false;
    accounts.erase(accounts.begin() + idx);
    saveToFile();
    return true;
}

// ── Transactions ───────────────────────────────────────────────────────────

bool Bank::deposit(int accountNumber, double amount) {
    int idx = findAccountIndex(accountNumber);
    if (idx == -1) return false;
    if (!accounts[idx].deposit(amount)) return false;
    saveToFile();
    return true;
}

bool Bank::withdraw(int accountNumber, const std::string& pin, double amount) {
    int idx = findAccountIndex(accountNumber);
    if (idx == -1) return false;
    if (!accounts[idx].validatePin(pin)) return false;
    if (!accounts[idx].withdraw(amount)) return false;
    saveToFile();
    return true;
}

bool Bank::transfer(int fromAccount, const std::string& pin,
                    int toAccount, double amount) {
    int fromIdx = findAccountIndex(fromAccount);
    int toIdx   = findAccountIndex(toAccount);
    if (fromIdx == -1 || toIdx == -1) return false;
    if (!accounts[fromIdx].validatePin(pin)) return false;
    if (!accounts[fromIdx].withdraw(amount)) return false;
    accounts[toIdx].deposit(amount);
    saveToFile();
    return true;
}

// ── Queries ────────────────────────────────────────────────────────────────

void Bank::checkBalance(int accountNumber, const std::string& pin) const {
    int idx = findAccountIndex(accountNumber);
    if (idx == -1) { std::cout << "  [!] Account not found.\n"; return; }
    if (!accounts[idx].validatePin(pin)) { std::cout << "  [!] Incorrect PIN.\n"; return; }
    std::cout << "  Balance for account " << accountNumber << ": INR "
              << std::fixed << std::setprecision(2) << accounts[idx].getBalance() << "\n";
}

void Bank::displayAccount(int accountNumber) const {
    int idx = findAccountIndex(accountNumber);
    if (idx == -1) { std::cout << "  [!] Account not found.\n"; return; }
    accounts[idx].displayInfo();
}

void Bank::displayAllAccounts() const {
    if (accounts.empty()) {
        std::cout << "  No accounts found.\n";
        return;
    }
    std::cout << "  " << std::string(50, '-') << "\n";
    std::cout << "  " << std::left << std::setw(12) << "Acc No"
              << std::setw(20) << "Name"
              << std::setw(12) << "Type"
              << std::setw(14) << "Balance (INR)" << "\n";
    std::cout << "  " << std::string(50, '-') << "\n";
    for (const auto& acc : accounts) {
        std::cout << "  " << std::left << std::setw(12) << acc.getAccountNumber()
                  << std::setw(20) << acc.getHolderName()
                  << std::setw(12) << acc.getAccountType()
                  << std::fixed << std::setprecision(2) << acc.getBalance() << "\n";
    }
    std::cout << "  " << std::string(50, '-') << "\n";
}
