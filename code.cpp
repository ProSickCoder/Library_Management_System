#include<string>
#include<vector>
#include<iostream>
#include<limits>
#include<ctime>
#include<iomanip>
#include<map>
#include<algorithm>
#include<fstream>
#include<stdexcept>
#include<regex>

class User{
    protected:
        std::string username;
        std::string password;
        bool isAdmin;
        double fines;
    
    public:
        User(std::string username, std::string password, bool isAdmin =false): username(username),password(password),isAdmin(isAdmin),fines(0.0){}

        std::string getUsername() const {return username;}

        bool checkPassword(const std::string& pwd)const{return password==pwd;}

        bool isAdministrator() const{return isAdmin;}

        double getFines() const {return fines;}
        void addFine(double amount) {fines +=amount;}
        void addFine(double amount) {fines =std::max(0.0,fines -amount);}
};

class Book{
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
        Book(std::string title, std::string author, std::string isbn, std::string category, int copies =1) : title(title),author(author), isbn(isbn), category(category), isAvailable(true), dueDate(0), totalCopies(copies), availableCopies(copies){}
        std::string getTitle() const {return title;}
        std::string getAuthor() const {return author;}
        std::string getIsbn() const {return isbn;}
        std::string getCategory() const {return category;}
        bool getAvailability() const {return availableCopies > 0;}
        std::string getBorrower() const {return borrower;}
        time_t getDueDate() const {return dueDate;}
        int getTotalCopies() const {return totalCopies;}
        int getAvailableCopies() const {return availableCopies;}

        //Calculating fine (0.50 per day overdue)
        double calculateFine() const{
            id(!isAvailable && time(nullptr) > dueDate){
                double days = difftime(time(nullptr), dueDate) /(24*60*60);
                return days*0.50;
            }
            return 0.0;
        }

        bool borrowBook(const std::string& borrowerName){
            if(availableCopies <= 0) return false;
            availableCopies--;
            if(availableCopies ==0) isAvailable =false;
            borrower = borrowerName;
            dueDate = time(nullptr)+ (14*24*60*60); //14 days loan period
            return true;
        }

        void returnBook(){
            availableCopies++;
            if(availableCopies >0) isAvailable=true;
            borrower.clear();
            dueDate =0;
        }

        void displayInfo()const{
            std::cout<<"\nTitle:"<<title
                    <<"\nAuthor:"<<author
                    <<"\nISBN:"<<isbn
                    <<"\nCategory:"<<category
                    <<"\nAvailable Copies:"<<availableCopies << "/"<< totalCopies;

            if(availableCopies <totalCopies){
                std::cout<<"\nBorrowed by:"<<borrower <<"\nDue Date:"<< ctime(&dueDate);
                double fine = calculateFine();
                if(fine > 0){
                    std::cout<<"Current Fine:₹" <<std::fixed<<std::setprecision(2)<<fine;
                }
            }
            std::cout<<"\n";
        }
};
