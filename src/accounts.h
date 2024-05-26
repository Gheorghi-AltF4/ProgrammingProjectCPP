//
// Created by Andrei-Claudiu Gheorghiță on 26.05.2024.
//

#ifndef C__PP_ACCOUNTS_H
#define C__PP_ACCOUNTS_H
#include "string"

enum currency
{
    RON = 0,EUR,USD
};
const std::string currencies[] = {"RON","EUR","USD"};
class Account
{
private:
    std::string IBAN;
    std::string owner;
    currency coin;
    int amount;
public:
    Account(std::string IBAN,std::string owner,currency coin,int amount);
    void edit(int amount, currency coin);
    void transfer(Account dst, int amount);
    std::string get_owner();
    void add_amount(int amount);
    currency get_currency();
    static std::string generate_IBAN();
    static int exchange(int amount, currency from, currency to);
    friend std::ostream& operator<<(std::ostream& os, Account a);
};

#endif //C__PP_ACCOUNTS_H
