# Banking System in C

This repository contains a robust **Banking System** implemented in C, designed to manage user accounts, handle transactions, and provide essential banking functionalities. The project demonstrates advanced usage of **file handling**, **data structures**, and **low-level I/O** in C.

## Features

- **Account Management**
  - Create new user accounts.
  - Store account details securely in individual files.
  
- **Authentication**
  - Secure login using username and password validation.

- **Transaction Management**
  - Check balance.
  - Deposit money.
  - Withdraw funds.
  - Transfer money between accounts with transaction logging.

- **Data Handling**
  - Use of structured data (`struct`) to manage user information.
  - File-based storage for account and transaction logs.

## Code Overview

### 1. `Account.h`

This header file defines the `user` struct, encapsulating all critical account-related information.

```c
typedef struct
{
    char username[50];
    char password[20];
    int date, month, year;
    char phoneNum[15];
    char ssNum[20];
    char fName[20];
    char lName[20];
    char fatherName[50];
    char motherName[50];
    char address[100];
    char accType[20];
    float balance;
} user;
```
### 2. `Main.c`

The core logic of the banking system resides in `Main.c`. This file includes:

- **Secure Input**: 
  - Implements `getch()` to capture hidden password input, ensuring privacy during account creation and login.
  
- **File Operations**:
  - Efficiently reads and writes user data to files for persistent storage.
  - Supports dynamic updates to user account files for transactions like deposits and withdrawals.

- **Banking Functionalities**:
  - A modular approach is used to handle various banking features:
    - **Account Creation**: Collects user data and securely stores it in a file.
    - **Login System**: Validates username and password from the saved account data.
    - **Transaction Management**:
      - **Deposit**: Adds a specified amount to the user's balance and logs the transaction.
      - **Withdraw**: Deducts an amount (if sufficient funds are available) and updates the balance.
      - **Check Balance**: Reads and displays the current balance from the user's file.
      - **Money Transfer**: Transfers funds between accounts, updating balances and transaction logs for both users.
  - Includes **logging capabilities** for all transactions to maintain a history of operations.

#### Notable Design Choices:
- **Input Validation**:
  - Validates password length (8–20 characters) during account creation.
  - Ensures sufficient funds before allowing withdrawals or transfers.
- **Error Handling**:
  - Handles file I/O errors gracefully to prevent crashes.
  - Ensures only valid user accounts can be accessed.
- **Security**:
  - Hides passwords during input.
  - Allows easy integration of advanced security mechanisms like encryption for production.

#### Key Functions:
- **`account()`**: Handles user account creation.
- **`login()`**: Validates credentials and retrieves user data.
- **`checkBalance()`**: Displays the user’s current account balance.
- **`deposit()`**: Adds funds to the account and logs the transaction.
- **`withdraw()`**: Deducts funds after ensuring sufficient balance.
- **`transfer()`**: Transfers funds between users and logs the activity.
- **`preTransfer()`**: Validates the recipient account before initiating a transfer.

## File Structure

```plaintext
.
├── Account.h   # Header file defining the user structure
├── Main.c      # Core logic and implementation
└── README.md   # Documentation
```
---

### Future Enhancements

```markdown
## Future Enhancements

- Implement password hashing for secure storage.
- Add multi-threading for better performance in concurrent operations.
- Introduce a database (e.g., SQLite) for scalable data management.
- Add a GUI or web-based frontend for user interaction.
```

## License

This project is licensed under the [MIT License](LICENSE).

## Acknowledgments

- Inspired by the foundational principles of banking and C programming.
- Developed to explore advanced file handling and modular programming in C.
