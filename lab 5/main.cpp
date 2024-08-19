#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include "BankAccount.h"

using namespace std;

struct AccountReader {
    map<int, BankAccount*> idMap;
    map<string, BankAccount*> nameMap;

    void operator()(const string filePath) {
        ifstream file(filePath);
        if (!file.is_open()) {
            cerr << "Failed to open file: " << filePath << endl;
            return;
        }

        string line;
        getline(file, line);

        while (getline(file, line)) {
            stringstream ss(line);
            string typeStr, name, amountStr, idStr;

            getline(ss, typeStr, ',');
            getline(ss, name, ',');
            getline(ss, amountStr, ',');
            getline(ss, idStr);

            int type = stoi(typeStr);
            float amount = stof(amountStr);
            int id = stoi(idStr);

            BankAccount* account = nullptr;
            switch (type) {
                case 1:
                    account = new CheckingAccount(amount, id, name);
                    break;
                case 2:
                    account = new SavingsAccount(amount, id, name);
                    break;
                case 3:
                    account = new InvestmentAccount(amount, id, name);
                    break;
                default:
                    cerr << "Unknown account type: " << type << endl;
                    continue;
            }

            if (account) {
                idMap[id] = account;
                nameMap[name] = account;
            }
        }
        file.close();
    }

    void displayAllAccounts() const {
        vector<pair<int, BankAccount*>> sortedAccounts(idMap.begin(), idMap.end());

        sort(sortedAccounts.begin(), sortedAccounts.end(),
            [](const pair<int, BankAccount*>& a, const pair<int, BankAccount*>& b) {
                return a.first < b.first;
            });

        for (const auto& entry : sortedAccounts) {
            entry.second->Display();
            cout << endl;
        }
    }

void displayAccountType(int pro) {
    vector<BankAccount*> accountsToDisplay;

    for (const auto& entry : idMap) {
        BankAccount* account = entry.second;
        bool shouldAdd = false;

        switch (pro) {
            case 1: 
                if (!dynamic_cast<SavingsAccount*>(account)) {
                    shouldAdd = true;
                }
                break;
            case 2: 
                if (!dynamic_cast<CheckingAccount*>(account)) {
                    shouldAdd = true;
                }
                break;
            case 3: 
                if (dynamic_cast<InvestmentAccount*>(account)) {
                    shouldAdd = true;
                }
                break;
            default:
                cerr << "Invalid account type specified." << endl;
                return;
        }

        if (shouldAdd) {
            accountsToDisplay.push_back(account);
        }
    }

    for (BankAccount* account : accountsToDisplay) {
        account->Display();
        cout << endl;
    }
}

    void findAccount(const string& search) const {
        try {
            int id = stoi(search);
            auto it = idMap.find(id);
            if (it != idMap.end()) {
                it->second->Display();
            } else {
                cout << "Could not find account!" << endl;
            }
        } catch (const invalid_argument&) {
            auto it = nameMap.find(search);
            if (it != nameMap.end()) {
                it->second->Display();
            } else {
                cout << "Could not find account!" << endl;
            }
        }
    }

    ~AccountReader() {
        for (auto& entry : idMap) {
            delete entry.second;
        }
        idMap.clear();
        nameMap.clear();
    }
};

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " path/to/accounts.csv" << endl;
        return 1;
    }

    string filePath = argv[1];
    AccountReader reader;
    reader(filePath);

    while (true) {
        cout << "1. Display all accounts" << endl;
        cout << "2. Display all of account type" << endl;
        cout << "3. Find account" << endl;

        string optionS;
        int option;
        getline(cin, optionS);
        option = stoi(optionS);

        switch (option) {
            case 1:{
                reader.displayAllAccounts();
                return false;
            }
            case 2: {
                string info;
                getline(cin, info);
                int pro = stoi(info);
                reader.displayAccountType(pro);
                return false;
            }
            case 3: {
                string search;
                getline(cin, search);
                reader.findAccount(search);
                return false;
            }
            default:
                cout << "Invalid option. Please enter a number between 0 and 3." << endl;
                break;
        }
    }
}