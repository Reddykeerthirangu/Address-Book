# Address-Book
A simple Address Book Management System developed using C programming. It allows users to store, manage, search, edit, and delete contact details such as names, phone numbers, and email addresses. This project demonstrates basic C programming concepts, including structures, functions, file handling, and data management.
# Address Book Management System

A simple and efficient Address Book Management System developed using **C programming**. It allows users to store, manage, search, edit, and delete contact details such as names, phone numbers, and email addresses with proper validation and persistent file storage.

## Features

- **Create Contact**: Add new contacts with validation for names, 10-digit phone numbers, and email formats (checking uniqueness to prevent duplicates).
- **Search Contact**: Search for contacts by **Name**, **Phone Number**, or **Email ID**.
- **Edit Contact**: Modify existing contact details securely.
- **Delete Contact**: Remove contacts from the address book dynamically.
- **List All Contacts**: View all saved contacts sorted alphabetically by name in a clean tabular format.
- **File Handling**: Automatically saves and loads contacts using a CSV file (`file.csv`) so data persists between program runs.

## Technologies Used

- Language: **C**
- Concepts: Structures, Functions, Pointers, File I/O, String Manipulation

## Project Structure

- `main.c`: Contains the main menu loop and program control flow.
- `contact.c`: Implements core functionalities (creation, search, edit, delete, listing, and validation).
- `contact.h`: Header file containing structure definitions and function declarations.
- `file.c`: Manages reading and writing contact data to files.
- `file.h`: Header file for file operations.

## How to Run

1. Clone or download the repository.
2. Compile all source files using a C compiler (like GCC):
   ```bash
   gcc main.c contact.c file.c -o address_book
