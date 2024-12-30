#include <string>
#include <vector>
#include <iostream>
#include <limits>
#include <ctime>
#include <iomanip>
#include <map>
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <regex>

class User {
protected:
    std::string username;
    std::string password;
    bool isAdmin;
    double fines;

public:
    User(std::string username, std::string password, bool isAdmin = false)
        : username(username), password(password), isAdmin(isAdmin), fines(0.0) {}

    std::string getUsername() const { return username; }
    bool checkPassword(const std::string& pwd) const { return password == pwd; }
    bool isAdministrator() const { return isAdmin; }
    double getFines() const { return fines; }
    void addFine(double amount) { fines += amount; }
    void payFine(double amount) { fines = std::max(0.0, fines - amount); }
};

class Book {
private:
    std::string title;
    std::string author;
    std::string isbn;
    std::string category;
    bool isAvailable;
    std::string borrower;
    time_t dueDate;
    int totalCopies;
    int availableCopies;

public:
    Book(std::string title, std::string author, std::string isbn, std::string category, int copies = 1)
        : title(title), author(author), isbn(isbn), category(category), 
          isAvailable(true), dueDate(0), totalCopies(copies), availableCopies(copies) {}

    // Getters
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    std::string getIsbn() const { return isbn; }
    std::string getCategory() const { return category; }
    bool getAvailability() const { return availableCopies > 0; }
    std::string getBorrower() const { return borrower; }
    time_t getDueDate() const { return dueDate; }
    int getTotalCopies() const { return totalCopies; }
    int getAvailableCopies() const { return availableCopies; }

    // Calculate fine (0.50 per day overdue)
    double calculateFine() const {
        if (!isAvailable && time(nullptr) > dueDate) {
            double days = difftime(time(nullptr), dueDate) / (24 * 60 * 60);
            return days * 0.50;
        }
        return 0.0;
    }

    bool borrowBook(const std::string& borrowerName) {
        if (availableCopies <= 0) return false;
        availableCopies--;
        if (availableCopies == 0) isAvailable = false;
        borrower = borrowerName;
        dueDate = time(nullptr) + (14 * 24 * 60 * 60); // 14 days loan period
        return true;
    }

    void returnBook() {
        availableCopies++;
        if (availableCopies > 0) isAvailable = true;
        borrower.clear();
        dueDate = 0;
    }

    void displayInfo() const {
        std::cout << "\nTitle: " << title
                  << "\nAuthor: " << author
                  << "\nISBN: " << isbn
                  << "\nCategory: " << category
                  << "\nAvailable Copies: " << availableCopies << "/" << totalCopies;
        
        if (availableCopies < totalCopies) {
            std::cout << "\nBorrowed by: " << borrower
                      << "\nDue Date: " << ctime(&dueDate);
            double fine = calculateFine();
            if (fine > 0) {
                std::cout << "Current Fine: $" << std::fixed << std::setprecision(2) << fine;
            }
        }
        std::cout << "\n";
    }
};

class Library {
private:
    std::vector<Book> books;
    std::map<std::string, User> users;
    User* currentUser ;

    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    void waitForEnter() {
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    void showAdminMenu() {
        while (true) {
            clearScreen();
            std::cout << "\n=== Admin Menu ===\n"
                      << "1. Add New Book\n"
                      << "2. Remove Book\n"
                      << "3. Add User\n"
                      << "4. View All Users\n"
                      << "5. View Overdue Books\n"
                      << "6. Return to Main Menu\n"
                      << "Choose an option: ";

            int choice;
            std::cin >> choice;

            switch (choice) {
                case 1:
                    addNewBook();
                    break;
                case 2:
                    removeBook();
                    break;
                case 3:
                    addUser ();
                    break;
                case 4:
                    viewAllUsers();
                    break;
                case 5:
                    viewOverdueBooks();
                    break;
                case 6:
                    return;
                default:
                    std::cout << "\nInvalid option.\n";
            }
            waitForEnter();
        }
    }

    void addNewBook() {
        std::string title, author, isbn, category;
        int copies;

        std::cin.ignore();
        std::cout << "Enter book title: ";
        std::getline(std::cin, title);
        std::cout << "Enter author: ";
        std::getline(std::cin, author);
        std::cout << "Enter ISBN: ";
        std::getline(std::cin, isbn);
        std::cout << "Enter category: ";
        std::getline(std::cin, category);
        std::cout << "Enter number of copies: ";
        while (!(std::cin >> copies) || copies <= 0) {
            std::cout << "Please enter a valid positive number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        books.emplace_back(title, author, isbn, category, copies);
        std::cout << "\nBook added successfully!\n";
    }

    void removeBook() {
        std::string isbn;
        std::cout << "Enter ISBN of book to remove: ";
        std::cin >> isbn;

        auto it = std::find_if(books.begin(), books.end(),
            [&isbn](const Book& book) { return book.getIsbn() == isbn; });

        if (it != books.end()) {
            books.erase(it);
            std::cout << "\nBook removed successfully!\n";
        } else {
            std::cout << "\nBook not found.\n";
        }
    }

    void addUser () {
        std ```cpp
        ::string username, password;
        char isAdmin;

        std::cin.ignore();
        std::cout << "Enter username: ";
        std::getline(std::cin, username);
        std::cout << "Enter password: ";
        std::getline(std::cin, password);
        std::cout << "Make admin? (y/n): ";
        std::cin >> isAdmin;

        users.emplace(username, User(username, password, isAdmin == 'y'));
        std::cout << "\nUser  added successfully!\n";
    }

    void viewAllUsers() {
        std::cout << "\n=== User List ===\n";
        for (const auto& user : users) {
            std::cout << "Username: " << user.first
                      << " (Admin: " << (user.second.isAdministrator() ? "Yes" : "No") << ")"
                      << " Outstanding Fines: $" << std::fixed << std::setprecision(2) 
                      << user.second.getFines() << "\n";
        }
    }

    void viewOverdueBooks() {
        std::cout << "\n=== Overdue Books ===\n";
        time_t now = time(nullptr);
        bool found = false;

        for (const auto& book : books) {
            if (!book.getAvailability() && now > book.getDueDate()) {
                book.displayInfo();
                found = true;
            }
        }

        if (!found) {
            std::cout << "No overdue books.\n";
        }
    }

    void searchBooks() const {
        std::cout << "\n=== Search Books ===\n"
                  << "1. Search by Title\n"
                  << "2. Search by Author\n"
                  << "3. Search by Category\n"
                  << "Choose search type: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        std::string searchTerm;
        std::cout << "Enter search term: ";
        std::getline(std::cin, searchTerm);

        bool found = false;
        for (const auto& book : books) {
            bool matches = false;
            switch (choice) {
                case 1:
                    matches = book.getTitle().find(searchTerm) != std::string::npos;
                    break;
                case 2:
                    matches = book.getAuthor().find(searchTerm) != std::string::npos;
                    break;
                case 3:
                    matches = book.getCategory().find(searchTerm) != std::string::npos;
                    break;
                default:
                    std::cout << "\nInvalid search option.\n";
                    return;
            }
            if (matches) {
                book.displayInfo();
                found = true;
            }
        }
        if (!found) {
            std::cout << "\nNo matching books found.\n";
        }
    }

    void loadLibraryData() {
        std::ifstream inFile("library_data.txt");
        if (!inFile) {
            std::cerr<< "Error opening file for reading.\n";
            return;
        }
        std::string title, author, isbn, category;
        int copies;
        while (inFile >> std::quoted(title) >> std::quoted(author) >> std::quoted(isbn) >> std::quoted(category) >> copies) {
            books.emplace_back(title, author, isbn, category, copies);
        }
        inFile.close();
    }

    void saveLibraryData() const {
        std::ofstream outFile("library_data.txt");
        if (!outFile) {
            std::cerr << "Error opening file for writing.\n";
            return;
        }
        for (const auto& book : books) {
            outFile << std::quoted(book.getTitle()) << " "
                    << std::quoted(book.getAuthor()) << " "
                    << std::quoted(book.getIsbn()) << " "
                    << std::quoted(book.getCategory()) << " "
                    << book.getTotalCopies() << "\n";
        }
        outFile.close();
    }

    // Utility function to read input safely
    template<typename T>
    T readInput(const std::string& prompt) {
        T input;
        std::cout << prompt;
        while (!(std::cin >> input)) {
            std::cout << "Invalid input. Please try again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the buffer
        return input;
    }

public:
    Library() : currentUser (nullptr) {
        users.emplace("admin", User("admin", "admin123", true));
        loadLibraryData();
    }

    ~Library() {
        save LibraryData();
    }

    bool login() {
        std::string username, password;
        std::cout << "Username: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::cin >> password;

        auto it = users.find(username);
        if (it != users.end() && it->second.checkPassword(password)) {
            currentUser  = &it->second;
            return true;
        }
        return false;
    }

    void runMenu() {
        while (true) {
            if (!currentUser ) {
                clearScreen();
                std::cout << "\n=== Library Login ===\n";
                if (!login()) {
                    std::cout << "\nInvalid credentials!\n";
                    waitForEnter();
                    continue;
                }
            }

            clearScreen();
            std::cout << "\n=== Library Management System ===\n"
                      << "Logged in as: " << currentUser ->getUsername() << "\n"
                      << "1. Display All Books\n"
                      << "2. Search Books\n"
                      << "3. Borrow a Book\n"
                      << "4. Return a Book\n"
                      << "5. View My Fines\n"
                      << "6. Pay Fines\n";
            
            if (currentUser ->isAdministrator()) {
                std::cout << "7. Admin Menu\n";
            }
            std::cout << "8. Logout\n"
                      << "9. Exit\n"
                      << "Choose an option: ";

            int choice = readInput<int>("Choose an option: ");

            switch (choice) {
                case 1:
                    displayAllBooks();
                    break;

                case 2:
                    searchBooks();
                    break;

                case 3: {
                    if (currentUser ->getFines() > 0) {
                        std::cout << "\nCannot borrow books while you have outstanding fines.\n";
                        break;
                    }
                    std::string isbn;
                    std::cout << "Enter ISBN: ";
                    std::cin >> isbn;
                    Book* book = findBook(isbn);
                    if (book && book->getAvailability()) {
                        if (book->borrowBook(currentUser ->getUsername())) {
                            std::cout << "\nBook borrowed successfully!\n";
                        }
                    } else {
                        std::cout << "\nBook not available or not found.\n";
                    }
                    break;
                }

                case 4: {
                    std::string isbn;
                    std::cout << "Enter ISBN: ";
                    std::cin >> isbn;
                    Book* book = findBook(isbn);
                    if (book && !book->getAvailability() && 
                        book->getBorrower() == currentUser ->getUsername()) {
                        double fine = book->calculateFine();
                        if (fine > 0) {
                            currentUser ->addFine(fine);
                            std::cout << "\nLate return fine added: $" << std::fixed 
                                     << std::setprecision(2) << fine << "\n";
                        }
                        book->returnBook();
                        std::cout << "\nBook returned successfully!\n";
                    } else {
                        std::cout << "\nBook not found or not borrowed by you.\n";
                    }
                    break;
                }

                case 5:
                    std::cout << "\nYour current fines: $" << std::fixed 
                             << std::setprecision(2) << currentUser ->getFines() << "\n";
                    break;

                case 6: {
                    double amount;
                    std::cout << "Enter amount to pay: $";
                    std::cin >> amount;
                    if (amount < 0) {
                        std::cout << "Invalid amount. Please enter a positive value.\n";
                    } else {
                        currentUser ->payFine(amount);
                        std::cout << "\nPayment processed. Remaining fine: $" << std::fixed 
                                 << std::setprecision(2) << currentUser ->getFines() << "\n";
                    }
                    break;
                }

                case 7:
                    if (currentUser ->isAdministrator()) {
                        showAdminMenu();
                    } else {
                        std::cout << "\nInvalid option.\n";
                    }
                    break;

                case 8:
                    currentUser  = nullptr;
                    std::cout << "\nLogged out successfully!\n";
                    break;

                case 9:
                    std::cout << "\nThank you for using the Library Management System!\n";
                    return;

                default:
                    std::cout << "\nInvalid option.\n";
            }
            waitForEnter();
        }
    }

    void displayAllBooks() const {
        if (books.empty()) {
            std::cout << "\nNo books in the library.\n";
            return;
        }

        std::cout << "\ ```cpp
        \n=== Library Catalog ===\n";
        for (const auto& book : books) {
            book.displayInfo();
            std::cout << "-------------------";
        }
    }

    Book* findBook(const std::string& isbn) {
        for (auto& book : books) {
            if (book.getIsbn() == isbn) {
                return &book;
            }
        }
        return nullptr;
    }
};

int main() {
    Library library;

    // Run the library system
    library.runMenu();

    return 0;
}

