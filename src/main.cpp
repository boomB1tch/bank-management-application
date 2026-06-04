#include "Bank.h"
#include "Utils.h"
#include <iostream>
#include <limits>
#include <string>

// ── Helper input readers ───────────────────────────────────────────────────

static int readInt(const std::string& prompt) {
    int val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) { std::cin.ignore(); return val; }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  [!] Invalid input. Try again.\n";
    }
}

static double readDouble(const std::string& prompt) {
    double val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) { std::cin.ignore(); return val; }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  [!] Invalid input. Try again.\n";
    }
}

static std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

// ── Feature screens ────────────────────────────────────────────────────────

void createAccountMenu(Bank& bank) {
    Utils::printHeader("CREATE NEW ACCOUNT");
    std::string name = readLine("  Full Name       : ");
    if (!Utils::isValidName(name)) {
        std::cout << "  [!] Invalid name. Only letters and spaces allowed.\n";
        Utils::pauseScreen(); return;
    }

    std::cout << "  PIN (4-6 digits) : ";
    std::string pin = Utils::maskInput();
    if (!Utils::isValidPin(pin)) {
        std::cout << "  [!] PIN must be 4-6 digits.\n";
        Utils::pauseScreen(); return;
    }

    double deposit = readDouble("  Initial Deposit  : INR ");
    if (!Utils::isValidAmount(deposit)) {
        std::cout << "  [!] Deposit must be positive.\n";
        Utils::pauseScreen(); return;
    }

    std::cout << "  Account Type (1=Savings  2=Current) : ";
    int typeChoice = readInt("");
    std::string type = (typeChoice == 2) ? "current" : "savings";

    int accNo = bank.createAccount(name, pin, deposit, type);
    std::cout << "\n  [✓] Account created successfully!\n";
    std::cout << "  Your Account Number: " << accNo << "\n";
    Utils::pauseScreen();
}

void depositMenu(Bank& bank) {
    Utils::printHeader("DEPOSIT");
    int accNo = readInt("  Account Number : ");
    if (!bank.accountExists(accNo)) {
        std::cout << "  [!] Account not found.\n";
        Utils::pauseScreen(); return;
    }
    double amount = readDouble("  Amount (INR)   : ");
    if (bank.deposit(accNo, amount))
        std::cout << "  [✓] Deposit of INR " << amount << " successful.\n";
    else
        std::cout << "  [!] Deposit failed. Check the amount.\n";
    Utils::pauseScreen();
}

void withdrawMenu(Bank& bank) {
    Utils::printHeader("WITHDRAW");
    int accNo = readInt("  Account Number : ");
    if (!bank.accountExists(accNo)) {
        std::cout << "  [!] Account not found.\n";
        Utils::pauseScreen(); return;
    }
    std::cout << "  PIN            : ";
    std::string pin = Utils::maskInput();
    double amount = readDouble("  Amount (INR)   : ");
    if (bank.withdraw(accNo, pin, amount))
        std::cout << "  [✓] Withdrawal of INR " << amount << " successful.\n";
    else
        std::cout << "  [!] Failed. Check PIN, balance, or amount.\n";
    Utils::pauseScreen();
}

void balanceMenu(Bank& bank) {
    Utils::printHeader("BALANCE INQUIRY");
    int accNo = readInt("  Account Number : ");
    std::cout << "  PIN            : ";
    std::string pin = Utils::maskInput();
    bank.checkBalance(accNo, pin);
    Utils::pauseScreen();
}

void transferMenu(Bank& bank) {
    Utils::printHeader("FUND TRANSFER");
    int from = readInt("  From Account   : ");
    std::cout << "  PIN            : ";
    std::string pin = Utils::maskInput();
    int to     = readInt("  To Account     : ");
    double amt = readDouble("  Amount (INR)   : ");
    if (bank.transfer(from, pin, to, amt))
        std::cout << "  [✓] Transfer of INR " << amt << " successful.\n";
    else
        std::cout << "  [!] Transfer failed. Check details.\n";
    Utils::pauseScreen();
}

void viewAccountMenu(Bank& bank) {
    Utils::printHeader("VIEW ACCOUNT");
    int accNo = readInt("  Account Number : ");
    bank.displayAccount(accNo);
    Utils::pauseScreen();
}

void deleteAccountMenu(Bank& bank) {
    Utils::printHeader("DELETE ACCOUNT");
    int accNo = readInt("  Account Number : ");
    std::cout << "  PIN            : ";
    std::string pin = Utils::maskInput();
    if (bank.deleteAccount(accNo, pin))
        std::cout << "  [✓] Account deleted.\n";
    else
        std::cout << "  [!] Failed. Wrong PIN or account not found.\n";
    Utils::pauseScreen();
}

void adminMenu(Bank& bank) {
    Utils::printHeader("ADMIN — ALL ACCOUNTS");
    bank.displayAllAccounts();
    Utils::pauseScreen();
}

// ── Main menu ──────────────────────────────────────────────────────────────

int main() {
    // Ensure data directory exists
    system("mkdir -p data");

    Bank bank("data/accounts.dat");

    while (true) {
        Utils::printHeader("BANK MANAGEMENT SYSTEM");
        std::cout << "  [1]  Create Account\n"
                  << "  [2]  Deposit\n"
                  << "  [3]  Withdraw\n"
                  << "  [4]  Check Balance\n"
                  << "  [5]  Fund Transfer\n"
                  << "  [6]  View Account Details\n"
                  << "  [7]  Delete Account\n"
                  << "  [8]  Admin — View All Accounts\n"
                  << "  [0]  Exit\n\n";

        int choice = readInt("  Enter choice : ");

        switch (choice) {
            case 1: createAccountMenu(bank); break;
            case 2: depositMenu(bank);       break;
            case 3: withdrawMenu(bank);      break;
            case 4: balanceMenu(bank);       break;
            case 5: transferMenu(bank);      break;
            case 6: viewAccountMenu(bank);   break;
            case 7: deleteAccountMenu(bank); break;
            case 8: adminMenu(bank);         break;
            case 0:
                Utils::printHeader("GOODBYE");
                std::cout << "  Thank you for using the Bank Management System.\n\n";
                return 0;
            default:
                std::cout << "  [!] Invalid choice.\n";
                Utils::pauseScreen();
        }
    }
}
