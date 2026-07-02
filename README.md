# Bank Management System

A console-based bank management system built with C++ that supports full client management and transactions via file storage.

## Features

### Main Menu
- **Show Client List**: displays all clients stored in `Clients.txt`
- **Add New Client**: prompts for account number (checks for duplicates), pin code, full name, phone number, and balance. Option to add multiple clients in one session
- **Delete Client**: searches by account number, shows client details, and asks for confirmation before deleting
- **Update Client Info**: searches by account number and allows editing all fields except the account number
- **Find Client**: searches and displays a client's details by account number
- **Transactions**: opens an ATM screen with the following options:
  - Deposit: adds amount to client balance
  - Withdraw: deducts amount with balance validation
  - Total Balances: displays all clients with a total balance sum
  - Back to Main Menu
- **Exit**

## File Storage
Client data is stored and retrieved from `Clients.txt` using a custom `#//# ` separator between fields.

## Dependencies
Uses a personal utility library `MyLib.h` for string splitting operations.

## How to Run
1. Place `MyLib.h` in the same directory as the source file
2. Compile with any C++ compiler:
```
```
## Technologies
C++, File Handling (fstream), Structs, Enums, Vectors
