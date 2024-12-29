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

