#include <iostream>
#include <vector>
#include <conio.h>
#include "Admin.h"
#include "Client.h"
#include "AccountManager.h"
using namespace std;

int showHighlightMenu(const vector<string>& options) {
    int highlight = 0, key;
    while (true) {
        system("cls");
        cout << "Use UP/DOWN arrows and Enter to select:\n\n";
        for (int i = 0; i < options.size(); i++) {
            if (i == highlight)
                cout << "\033[1;31m> " << options[i] << "\033[0m\n";
            else
                cout << "  " << options[i] << "\n";
        }

        key = getch();
        if (key == 224) {
            key = getch();
            if (key == 72) highlight = (highlight - 1 + options.size()) % options.size();
            else if (key == 80) highlight = (highlight + 1) % options.size();
        } else if (key == 13) { // Enter
            system("cls");
            return highlight;
        } else if (key == 27) { // ESC
            system("cls");
            return -1;
        }
    }
}

void clientMenu(Client* c, AccountManager& mgr) {
    vector<string> menu = {"View Profile", "Transfer Money", "View Transactions", "Logout"};
    int choice;
    do {
        choice = showHighlightMenu(menu);
        if (choice == 0) { system("cls"); c->viewProfile(); system("pause"); }
        else if (choice == 1) {
            system("cls");
            string target; double amount;
            cout << "Enter target AccID: "; cin >> target;
            cout << "Amount: "; cin >> amount;
            Client* receiver = mgr.findByAccID(target);
            if (!receiver) cout << "Target account not found.\n";
            else { c->transferOut(target, amount); receiver->addIncoming(c->getAccID(), amount); }
            system("pause");
        }
        else if (choice == 2) { system("cls"); c->viewTransactions(); system("pause"); }
    } while (choice != 3 && choice != -1);
}

void adminMenu(Admin* a, AccountManager& mgr) {
    vector<string> menu = {"View All Clients","Search Client","Enable Account","Disable Account","Statistics","Logout"};
    int choice;
    do {
        choice = showHighlightMenu(menu);
        if (choice == 0) { system("cls"); a->viewClients(mgr); system("pause"); }
        else if (choice == 1) {
            system("cls"); string accID;
            cout << "Enter AccID: "; cin >> accID;
            Client* c = a->searchClient(mgr, accID);
            if(c) c->viewProfile(); else cout << "Client not found.\n";
            system("pause");
        }
        else if (choice == 2) { system("cls"); string accID; cout << "Enter AccID to enable: "; cin >> accID; a->enableAccount(mgr, accID); system("pause"); }
        else if (choice == 3) { system("cls"); string accID; cout << "Enter AccID to disable: "; cin >> accID; a->disableAccount(mgr, accID); system("pause"); }
        else if (choice == 4) { system("cls"); a->viewStatistics(mgr); system("pause"); }
    } while (choice != 5 && choice != -1);
}

void loginMenu(AccountManager& mgr, Admin& admin) {
    vector<string> mainMenu = {"Login", "Register", "Exit"};
    int choice;

    do {
        system("cls");
        choice = showHighlightMenu(mainMenu);

        if (choice == 0) {
            system("cls");
            string uname, pass;
            cout << "Username: "; cin >> uname;
            cout << "Password: "; cin >> pass;

            bool found = false;
            for (auto c : mgr.getAllClients()) {
                if (c->login(uname, pass)) {
                    clientMenu(c, mgr);
                    found = true;
                    break;
                }
            }

            if (!found) {
                if (admin.login(uname, pass)) {
                    adminMenu(&admin, mgr);
                    found = true;
                }
            }

            if (!found) {
                system("cls");
                cout << "Invalid credentials!\n";
                system("pause");
            }
        }
        else if (choice == 1) {
            system("cls");
            string uname, password, phone;
            double balance;

            cout << "--- Client Registration ---\n";

            do {
                cout << "Enter Username: "; cin >> uname;
                if (mgr.isUsernameTaken(uname))
                    cout << "Username already taken! Try another.\n";
                else break;
            } while (true);

            cout << "Enter Password: "; cin >> password;

            do {
                cout << "Enter Phone: "; cin >> phone;
                if (mgr.isPhoneTaken(phone))
                    cout << "Phone number already registered! Try another.\n";
                else break;
            } while (true);

            cout << "Enter Initial Balance: "; cin >> balance;

            Client* newClient = new Client(uname, password, phone, balance);
            mgr.registerClient(newClient);

            system("cls");
            cout << "\nRegistration successful!\nYour Account ID is: " << newClient->getAccID() << endl;
            system("pause");
        }

    } while (choice != 2 && choice != -1);
    system("cls");
    cout << "Exiting program...\n";
}

int main() {
    AccountManager mgr;
    Client* c1 = new Client("ahmed","123","0101",3000);
    Client* c2 = new Client("youssef","123","0102",1500);
    mgr.registerClient(c1); mgr.registerClient(c2);

    Admin admin("A001","admin","admin","012");

    loginMenu(mgr,admin);

    return 0;
}
