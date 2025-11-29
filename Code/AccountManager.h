#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include "Client.h"
#include <vector>
#include <string>
using namespace std;

class AccountManager {
private:
    vector<Client*> clients;

public:
    void registerClient(Client* c) {
        clients.push_back(c);
    }

    vector<Client*> getAllClients() const { return clients; }

    Client* findByAccID(const string& accID) {
        for (auto c : clients) {
            if (c->getAccID() == accID) return c;
        }
        return nullptr;
    }

    bool isUsernameTaken(const string& uname) const {
        for (auto c : clients) {
            if (c->getUsername() == uname) return true;
        }
        return false;
    }

    bool isPhoneTaken(const string& ph) const {
        for (auto c : clients) {
            if (c->getPhone() == ph) return true;
        }
        return false;
    }
};

#endif
