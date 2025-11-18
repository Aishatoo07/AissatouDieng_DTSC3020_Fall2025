#ifndef PROJECT2_H
#define PROJECT2_H

#include "Account.h"
#include <vector>
#include <iostream>
using namespace std;

void displayHeader();
void displayMenu();
void openAccount(vector<Account>& accounts);
void depositToAccount(vector<Account>& accounts);
void withdrawFromAccount(vector<Account>& accounts);
void printAccounts(const vector<Account>& accounts);
Account* findAccount(vector<Account>& accounts, int accNumber);

#endif


#include "project2.h"
#include <iomanip>

void displayHeader() {
    cout << "+ +\n"
         << "| Computer       Science and Engineering |\n"
         << "| CSCE 1040 - Computer Programming II |\n"
         << "| Ad1620       aissatoudieng@my.unt.edu |\n"
         << "+ +\n";
}

void displayMenu() {
    cout << "+ +\n"
         << "| Enter account selection |\n"
         << "| 1 : Open new account |\n"
         << "| 2 : Deposit into account |\n"
         << "| 3 : Withdraw from account |\n"
         << "| 4 : Print a list of all accounts |\n"
         << "| 5 : End transaction (Exit) |\n"
         << "+ +\n> ";
}

Account* findAccount(vector<Account>& accounts, int accNumber) {
    for (auto& acc : accounts) {
        if (acc.getAccountNumber() == accNumber)
            return &acc;
    }
    return nullptr;
}

void openAccount(vector<Account>& accounts) {
    string name;
    float deposit;
    cout << "Enter customer account name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter initial deposit amount: $ ";
    cin >> deposit;

    Account newAcc(name, deposit);
    accounts.push_back(newAcc);
    cout << "Account opened: " << newAcc.getAccountNumber() << " --- "
         << newAcc.getName() << " : $" << fixed << setprecision(2)
         << newAcc.getBalance() << endl;
}

void depositToAccount(vector<Account>& accounts) {
    int accNum;
    float deposit;
    cout << "Enter account number: ";
    cin >> accNum;

    Account* acc = findAccount(accounts, accNum);
    if (!acc) {
        cout << "Account number " << accNum << " not found.\n";
        return;
    }

    cout << "Enter deposit amount: $";
    cin >> deposit;
    acc->deposit(deposit);
    cout << "Deposit successful. New balance: $" << fixed << setprecision(2)
         << acc->getBalance() << endl;
}

void withdrawFromAccount(vector<Account>& accounts) {
    int accNum;
    float amount;
    cout << "Enter account number: ";
    cin >> accNum;

    Account* acc = findAccount(accounts, accNum);
    if (!acc) {
        cout << "Account number " << accNum << " not found.\n";
        return;
    }

    cout << "Enter withdrawal amount: $";
    cin >> amount;

    if (!acc->withdraw(amount)) {
        cout << "Insufficient funds.\n";
    } else {
        cout << "Withdrawal successful. New balance: $" << fixed << setprecision(2)
             << acc->getBalance() << endl;
    }
}

void printAccounts(const vector<Account>& accounts) {
    if (accounts.empty()) {
        cout << "No accounts available.\n";
        return;
    }

    cout << "+ +\n| Acct Number | Name         | Balance   |\n+ +\n";
    for (const auto& acc : accounts) {
        acc.displayAccount();
    }
    cout << "+ +\n";
}

int main() {
    vector<Account> accounts;
    int choice;

    displayHeader();

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: openAccount(accounts); break;
            case 2: depositToAccount(accounts); break;
            case 3: withdrawFromAccount(accounts); break;
            case 4: printAccounts(accounts); break;
            case 5: cout << "Thank you! Goodbye.\n"; break;
            default: cout << "Invalid selection. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}


