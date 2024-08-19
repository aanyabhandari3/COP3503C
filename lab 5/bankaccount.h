#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
#include <iostream>
#include <map>
using namespace std;

class BankAccount {
private:
    int id;
    string name;

public:
    BankAccount(int id, string name);
    string getName() ;
    int getID() ;

    virtual float getAmount() = 0;
    virtual void Display() = 0;
    virtual void Deposit(float amount) = 0;

    

    virtual ~BankAccount();
};

class CheckingAccount : virtual public BankAccount {
private:
    float amount;

protected:
    void setAmount(float Amount);

public:
    CheckingAccount();
    CheckingAccount(float Amount,  int id, string name);

    float getAmount() override;
    void Display() override;
    void Deposit(float deposit) override;

    bool Withdraw(float amountToWithdraw);
};

class SavingsAccount : virtual public BankAccount {
private:
    float amount;

protected:
    void setAmount(float Amount);

public:
    SavingsAccount();
    SavingsAccount(float Amount, int id, string name);

    float getAmount() override;
    void Display() override;
    void Deposit(float deposit) override;

    float CompoundEarnings(float percent);
    bool Transfer(CheckingAccount& Other, float Amount);
};

class InvestmentAccount : public CheckingAccount, private SavingsAccount {
private:
    float checkingAmount;
    float savingsAmount;

protected:
    void setCheckingAmount(float newAmount);
    void setSavingsAmount(float newAmount);

public:
    InvestmentAccount(float initialAmount, int id, string name);

    float getAmount() override;
    void Display() override;
    void Deposit(float amount) override;

    bool Withdraw(float amountToWithdraw);
    float CompoundEarnings(float percent);
    virtual ~InvestmentAccount() {}
};
#endif