# Library_Management_System

<div style="display: flex; justify-content: center;">
    <img src="https://c.tenor.com/QqVMoWspo_oAAAAC/tenor.gif" alt="Fun GIF" />
</div>

## Overview

The Library Management System is a C++ application designed to facilitate the management of books and users in a library setting. It provides functionalities for both regular users and administrators, allowing them to borrow and return books, manage user accounts, and track fines for overdue books. The system is built with object-oriented principles, utilizing classes to represent users, books, and the library itself.

## Features

### User Management
- **User  Registration**: Administrators can add new users to the system, specifying whether they have administrative privileges.
- **User  Login**: Users can log in with their credentials to access the system.
- **View Users**: Administrators can view a list of all registered users along with their outstanding fines.

### Book Management
- **Add New Books**: Administrators can add new books to the library's catalog, specifying details such as title, author, ISBN, category, and number of copies.
- **Remove Books**: Administrators can remove books from the catalog using the ISBN.
- **Search Books**: Users can search for books by title, author, or category.

### Borrowing and Returning Books
- **Borrow Books**: Users can borrow available books for a period of 14 days. If a user has outstanding fines, they are prevented from borrowing new books.
- **Return Books**: Users can return borrowed books. If the book is returned late, a fine is calculated and added to the user's account.

### Fine Management
- **View Fines**: Users can view their current outstanding fines.
- **Pay Fines**: Users can pay off their fines, reducing the total amount owed.

### Overdue Management
- **View Overdue Books**: Administrators can view a list of all overdue books along with the details of the borrowers and the fines incurred.

## Technical Details

### Classes
- **User **: Represents a user of the library, containing attributes for username, password, admin status, and fines.
- **Book**: Represents a book in the library, containing attributes for title, author, ISBN, category, availability, borrower, due date, and copies.
- **Library**: Manages the collection of books and users, handling all operations related to borrowing, returning, and managing books and users.

### File Handling
- The system supports loading and saving library data to and from a text file, ensuring that the state of the library is preserved between sessions.

### User Interface
- The application provides a console-based user interface, guiding users through various options with clear prompts and feedback.

## Getting Started

To run the Library Management System:
1. Ensure you have a C++ compiler installed.
2. Copy the code into a `.cpp` file.
3. Compile the code using your preferred C++ compiler.
4. Run the executable to start the application.

## Conclusion

The Library Management System is a comprehensive solution for managing library operations, providing a user-friendly interface and robust functionality for both users and administrators. It serves as a practical example of object-oriented programming in C++ and can be further extended with additional features as needed.
