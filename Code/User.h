#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
protected:
    string AccID;
    string username;
    string password;
    string phone;

public:
    User() = default;
    User(string acc, string uname, string pass, string ph)
        : AccID(acc), username(uname), password(pass), phone(ph) {}

    bool login(const string& uname, const string& pass) {
        return username == uname && password == pass;
    }

    string getUsername() const { return username; }
    string getPhone() const { return phone; }
    string getAccID() const { return AccID; }
};

#endif
