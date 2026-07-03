# Bank Management System

A console-based bank management system built with C++ that supports full client management, user management with permissions, and a standalone ATM system — all backed by file storage.

## Login
Before accessing the main menu, users must authenticate with a username and password. Access to features is controlled by permissions assigned to each user.

## Main Menu
- **Show Client List** — displays all clients stored in `Clients.txt`
- **Add New Client** — prompts for account number (checks for duplicates), pin code, full name, phone number, and balance. Option to add multiple clients in one session
- **Delete Client** — searches by account number, shows client details, and asks for confirmation before deleting
- **Update Client Info** — searches by account number and allows editing all fields except the account number
- **Find Client** — searches and displays a client's details by account number
- **Transactions** — opens an ATM screen with the following options:
  - Deposit — adds amount to client balance
  - Withdraw — deducts amount with balance validation
  - Total Balances — displays all clients with a total balance sum
  - Back to Main Menu
- **Manage Users** — opens a user management screen with the following options:
  - List Users
  - Add New User
  - Delete User (Admin user cannot be deleted)
  - Update User
  - Find User
  - Back to Main Menu
- **Exit**

## Permissions
User permissions are managed using bitwise OR, allowing fine-grained access control over which features each user can access.

## ATM System (Standalone)
A separate ATM application that works alongside the bank system using the same client data.

### ATM Login
Authenticate using account number and pin code.

### ATM Menu
- **Quick Withdraw** — choose from preset amounts: 20, 50, 100, 200, 400, 600, 800, 1000. Confirmation required before processing
- **Normal Withdraw** — enter a custom amount with balance validation
- **Deposit** — deposit amounts must be multiples of 5
- **Check Balance** — displays current account balance
- **Logout**

## File Storage
Client data is stored in `Clients.txt` and user data in `Users.txt` using a custom `#//# ` separator between fields.

## Dependencies
Uses personal utility library `MyLib.h` .
[cpp-personal-libraries](link to your libraries repo here)

## How to Run
1. Place `MyLib.h` in the same directory as the source files
2. Compile with any C++ compiler:
3. Run `BankSystem` first to manage clients, then use `ATM` to simulate client transactions

## Technologies
C++, File Handling (fstream), Structs, Enums, Vectors, Bitwise Operations
