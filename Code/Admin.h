#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "Client.h"
#include "AccountManager.h"
#include <iostream>
using namespace std;

class Admin : public User {
public:
    Admin(string acc, string uname, string pass, string ph)
        : User(acc, uname, pass, ph) {}

    void viewClients(AccountManager& mgr) {
        cout << "\n--- All Clients ---\n";
        for (auto c : mgr.getAllClients()) {
            c->viewProfile();
            cout << "-----------------\n";
        }
    }

    Client* searchClient(AccountManager& mgr, const string& accID) {
        return mgr.findByAccID(accID);
    }

    void enableAccount(AccountManager& mgr, const string& accID) {
        Client* c = mgr.findByAccID(accID);
        if (c) {
            c->setStatus("active");
            cout << "Account enabled.\n";
        } else {
            cout << "Client not found.\n";
        }
    }

    void disableAccount(AccountManager& mgr, const string& accID) {
        Client* c = mgr.findByAccID(accID);
        if (c) {
            c->setStatus("disabled");
            cout << "Account disabled.\n";
        } else {
            cout << "Client not found.\n";
        }
    }

    void viewStatistics(AccountManager& mgr) {
        int total = mgr.getAllClients().size();
        int active = 0;
        int disabled = 0;
        for (auto c : mgr.getAllClients()) {
            if (c->getStatus() == "active") active++;
            else disabled++;
        }
        cout << "\n--- Statistics ---\n";
        cout << "Total clients: " << total
             << "\nActive: " << active
             << "\nDisabled: " << disabled << endl;
    }
};

#endif
