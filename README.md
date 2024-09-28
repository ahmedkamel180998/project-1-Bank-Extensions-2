# Bank Management System Extension 2
This project is a simple **Bank Management System Extension 2** written in C++ that A user authentication feature is implemented, requiring users to log in with their credentials to access the system, allows users to manage client data, perform transactions such as deposits and withdrawals, and keep track of client balances. The program works by reading and writing client data from a text file (`clients.txt`) and writing users data from a text file (`users.txt`), providing various menu options for easy interaction.

## Table of Contents
- [Project Information](#Project-Information)
- [Live Demo](#Live-Demo)
- [Features](#features)
- [Project Flow](#Project-Flow)
- [File Structure](#File-Structure)

## Project Information
This C++ simple console-based Bank Management System project was created at the end of the [8th course](https://programmingadvices.com/p/08-algorithms-problem-solving-level-4) from the Roadmap for General Foundation in Programming @ [Programming Advices](https://programmingadvices.com/).

## Live Demo
https://github.com/user-attachments/assets/f4b1d297-3907-4adb-be44-cfac0a50aa8e

## Features
- **Login System**: A user authentication feature is implemented, requiring users to log in with their credentials to access the system.
- **User Management**: Manage the list of users allowed to access the system. Admins can add, update, or delete users.
- **Data Persistence:** All users information is saved to and retrieved from a file (`users.txt`).
- **Client List:** Display a list of all clients, including account number, pin code, name, phone, and account balance.
- **Add New Client:** Add new client information such as account number, pin code, name, phone, and balance.
- **Delete Client:** Remove a client from the system by account number.
- **Update Client Info:** Modify the details of an existing client.
- **Find Client:** Search for a client by account number and display their details.
- **Data Persistence:** All client information is saved to and retrieved from a file (`clients.txt`).
- **Transaction System**: Perform deposits, withdrawals, and view total balances.
- **File-Based Storage**: Store and retrieve client data from a text file.
- **Simple Menu Interface**: Navigate through different functionalities using the main and transaction menus.

## Project Flow
1. **Login Screen**:
   - What Happens in the Login Screen: The user is first met with the login screen where they must input their username and password.
   - This step is crucial to prevent unauthorized access to sensitive client and financial information.
   - Validation: The system checks the input against stored data in users.txt, and only on a successful match can users proceed to the main menu.
   - Security: The login system ensures that only authorized personnel can access the system, making this an important security feature.
   - When the application starts, the **Login Screen** is the first interface the user interacts with.
   - Users are prompted to enter their **username** and **password**, which are checked against the stored credentials in the `users.txt` file.
   - If the login credentials are correct, the user is granted access to the main system. Otherwise, the system will prompt the user to try again.
   - Only authorized users can access the various menus and features, ensuring secure control over the application’s operations.

2. **Main Menu**:
   - After successful login, users will be directed to the main menu, where they can:
     - Manage clients: Add, update, delete, or search for client information.
     - Perform transactions: Make deposits or withdrawals for any client.
     - Manage users: Admins can add or remove users from the system.
     - Logout: The user can log out and return to the login screen.

3. **Client Operations**:
   - **Adding a Client**: The system will prompt for client details (account number, name, phone, PIN, and initial balance) and store this information in the `clients.txt` file.
   - **Searching for a Client**: Enter an account number to quickly locate a client's information.
   - **Updating Client Information**: The system will display the current details of the client and allow for updates to be made.
   - **Deleting a Client**: Mark a client for deletion by entering their account number.

4. **Transaction Management**:
   - **Deposit**: Enter the amount to deposit into a client’s account, and the system will update the balance in the `clients.txt` file.
   - **Withdrawal**: Similarly, the system will prompt for the amount to withdraw and ensure the balance is updated accordingly.

5. **File Handling**:
   - **Loading Data**: Upon startup, the system loads all clients and users from their respective text files.
   - **Saving Data**: After each transaction or update, the system writes the changes back to the text files, ensuring persistent storage.

6. **Security**:
   - **User Login**: The system requires users to log in with valid credentials, which are verified against the data in `users.txt`.
   - **Access Control**: Only authorized users can perform actions within the system, enhancing security by limiting access to sensitive operations like client management and transactions.

## File Structure
### `project-1-Bank-Extensions-2.cpp`: The main program file containing the source code for the Bank Management System.
### `clients.txt`: The data file where client information is stored.
### `users.txt`: The data file where user information is stored.
