# 🏦 Bank Management System (C++)

A console-based Bank Management Application built in C++ using **Object-Oriented Programming** and **File Handling** for persistent storage.

---

## Features

| Feature | Description |
|---|---|
| Create Account | Open savings or current account with PIN |
| Deposit | Add funds to any account |
| Withdraw | Secure PIN-protected withdrawal |
| Balance Check | View balance with PIN authentication |
| Fund Transfer | Transfer between two accounts |
| View Account | Display account details |
| Delete Account | Remove account with PIN confirmation |
| Admin View | List all accounts in the system |
| Persistent Storage | All data saved to `data/accounts.dat` |

---

## Project Structure

```
bank-management/
├── include/
│   ├── Account.h       # Account class declaration
│   ├── Bank.h          # Bank class declaration
│   └── Utils.h         # Utility helpers
├── src/
│   ├── Account.cpp     # Account operations & file serialization
│   ├── Bank.cpp        # Core banking logic & file I/O
│   ├── Utils.cpp       # UI helpers, masked PIN input
│   └── main.cpp        # Menu-driven entry point
├── data/               # Auto-created; stores accounts.dat
├── Makefile
└── README.md
```

---

## OOP Concepts Used

- **Encapsulation** — Private data members with public accessor methods
- **Abstraction** — `Bank` class hides file I/O; callers use clean methods
- **Separation of Concerns** — `Account`, `Bank`, `Utils` each have distinct roles
- **Constructors / Destructors** — Proper object initialization

---

## Build & Run

### Prerequisites
- `g++` with C++17 support
- Unix/Linux/macOS (or Windows with MinGW)

### Compile
```bash
make
```

### Run
```bash
./bank_app
# or shortcut:
make run
```

### Clean
```bash
make clean
```

---

## Data Storage Format

Accounts are stored in `data/accounts.dat` as pipe-delimited records:
```
100001|Alice Smith|1234|5000.00|savings
100002|Bob Jones|5678|12000.00|current
```

Each field: `AccountNo|Name|PIN|Balance|Type`

> ⚠️ In a production system, PINs should be hashed (e.g., bcrypt/SHA-256). This project stores them in plain text for educational clarity.

---

## Sample Session

```
  ====================================================
              BANK MANAGEMENT SYSTEM
  ====================================================

  [1]  Create Account
  [2]  Deposit
  [3]  Withdraw
  [4]  Check Balance
  [5]  Fund Transfer
  ...
  Enter choice : 1

  Full Name       : Alice Smith
  PIN (4-6 digits): ****
  Initial Deposit : INR 5000
  Account Type    : 1

  [✓] Account created successfully!
  Your Account Number: 100001
```

---

## License

MIT License — free to use and modify for educational purposes.
