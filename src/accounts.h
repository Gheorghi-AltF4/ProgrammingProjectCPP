//
// Created by Andrei-Claudiu Gheorghiță on 26.05.2024.
//

#ifndef C__PP_ACCOUNTS_H
#define C__PP_ACCOUNTS_H
#include "string"

using namespace std;

enum currency
{
    RON = 0,
    EUR,
    USD
};

class Account
{
private:
    std::string IBAN;
    std::string owner;
    currency coin;
    int amount;

public:
    Account(std::string owner, currency coin);
    Account(std::string IBAN, string owner, currency coin, int amount);
    void edit(int amount, currency coin);
    void transfer(Account &dst, int amount);
    std::string get_IBAN();
    std::string get_owner();
    void add_amount(int amount);
    currency get_currency();
    static std::string generate_IBAN();
    static int exchange(int amount, currency from, currency to);
    friend std::ostream &operator<<(std::ostream &os, Account a);
};

std::istream &operator>>(std::istream &is, currency &coin);
std::ostream &operator<<(std::istream &os, currency coin);

class Accounts
{
private:
    Account *accounts[100];
    int size;

public:
    Accounts();
    ~Accounts();
    void create(string name, currency coin);
    void close(string name, string iban);
    void view(string name);
    void edit(string name, string IBAN, int amount, currency coin);
    void perform_transaction(string iban_src, string iban_dst, int amount, string name);
};

#endif // C__PP_ACCOUNTS_H

