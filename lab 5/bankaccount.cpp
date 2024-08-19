#include "BankAccount.h"
#include <iostream>
#include <iomanip>
using namespace std;

BankAccount::BankAccount(int id,string name) : name(name), id(id) {}

string BankAccount::getName()  {
    return name;
}

int BankAccount::getID()  {
    return id;
}

BankAccount::~BankAccount() = default;

// CheckingAccount
CheckingAccount::CheckingAccount()
    : BankAccount(0,""), amount(0.00f) {}

CheckingAccount::CheckingAccount(float initialAmount, int id, string name)
    : BankAccount(id,name), amount(initialAmount) {}

void CheckingAccount::setAmount(float newAmount) {
    amount = newAmount;
}

float CheckingAccount::getAmount() {
    return amount;
}

void CheckingAccount::Display() {
    cout << getName() << " (" << getID() << "):\n";
    cout<< fixed<<"\t Checking Account: $" << setprecision(2)<<amount << endl;
}

void CheckingAccount::Deposit(float deposit) {
    amount += deposit;
}

bool CheckingAccount::Withdraw(float amountToWithdraw) {
    if (amountToWithdraw <= amount) {
        amount -= amountToWithdraw;
        return true;
    } else {
        return false;
    }
}

// SavingsAccount
SavingsAccount::SavingsAccount()
    : BankAccount(0,""), amount(0.00f) {}

SavingsAccount::SavingsAccount(float initialAmount, int id, string name)
    : BankAccount(id, name), amount(initialAmount) {}

void SavingsAccount::setAmount(float newAmount) {
    amount = newAmount;
}

float SavingsAccount::getAmount() {
    return amount;
}

void SavingsAccount::Display() {
    cout << getName() << " (" << getID() << "):\n";
    cout<< fixed<< "\t Savings Account: $" << setprecision(2)<<amount << endl;
}

void SavingsAccount::Deposit(float deposit) {
    amount += deposit;
}

float SavingsAccount::CompoundEarnings(float percent) {
    if (percent < 0) {
        cerr << "Percent must be positive." << endl;
        return 0.00f;
    }
    float earnedAmount = amount * percent;
    setAmount(amount * (1 + percent));
    return earnedAmount;
}

bool SavingsAccount::Transfer(CheckingAccount& targetAccount, float transferAmount) {
    if (transferAmount <= amount) {
        setAmount(amount - transferAmount);
        targetAccount.Deposit(transferAmount);
        return true;
    } else {
        cerr << "Insufficient funds for transfer." << endl;
        return false;
    }
}

// InvestmentAccount
InvestmentAccount::InvestmentAccount(float initialAmount, int id,  string name)
    : BankAccount(id, name), checkingAmount(0.00f), savingsAmount(initialAmount) {}

void InvestmentAccount::setCheckingAmount(float newAmount) {
    checkingAmount = newAmount;
}

void InvestmentAccount::setSavingsAmount(float newAmount) {
    savingsAmount = newAmount;
}

float InvestmentAccount::getAmount() {
    return checkingAmount+savingsAmount;
}

void InvestmentAccount::Display()  {
    cout << getName() << " (" << getID() << "):\n";
    cout << fixed<< "\t Total: $" << setprecision(2)<< getAmount() << "\n";
    cout << fixed<< "\t\t Immediate Funds: $" << setprecision(2)<<checkingAmount << "\n";
    cout << fixed<< "\t\t Investment: $" << setprecision(2)<<savingsAmount << "\n";
}

void InvestmentAccount::Deposit(float amount) {
    savingsAmount += amount;
}

bool InvestmentAccount::Withdraw(float amountToWithdraw) {
    if (amountToWithdraw <= checkingAmount) {
        checkingAmount -= amountToWithdraw;
        return true;
    }
    return false;
}

float InvestmentAccount::CompoundEarnings(float percent) {
    if (percent < 0) {
        cerr << "Percent must be positive." << endl;
        return 0.00f;
    }
    float earnedAmount = savingsAmount * percent;
    savingsAmount *= (1 + percent);
    checkingAmount += earnedAmount;
    savingsAmount -= earnedAmount;
    return earnedAmount;
}