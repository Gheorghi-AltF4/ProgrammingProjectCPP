#include <string>
#include "accounts.h"
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <iostream>
using namespace std;
//
// Created by Andrei-Claudiu Gheorghiță on 26.05.2024.
//

float usd_value[] = {0.21, 1.07, 1};

std::string Account::generate_IBAN()
{
    stringstream ss;
    srand(time(NULL));
    ss << setfill('0') <<"RO"<< setw(2) << rand() % 100 << "RNCB" << setw(8) << rand() % 100000000 << rand() % 100000000;
    return ss.str();
}

int Account::exchange(int amount, currency from, currency to)
{
    amount = amount * usd_value[from];
    amount = amount / usd_value[to];
    return amount;
}

Account::Account(std::string IBAN,std::string owner,currency coin,int amount) {
        this->amount = 0;
        this->owner = owner;
        this->coin = coin;}

void Account::edit(int amount, currency coin) {
    this->amount=amount;
    this->coin=coin;
}

std::string Account::get_owner()
{
    return this->owner;
}

currency Account::get_currency()
{
    return this->coin;
}



void Account::transfer(Account dst, int amount)
{
    if(this->amount < amount) {
        std::cout << "Insufficient funds!\n";
        return;
    }
    if (this->coin == dst.get_currency())
    {
        this->amount -= amount;
        dst.amount += amount;
        cout<<"Transaction performed successfully!\n";
        return;
    }
    int decision = 0;
    printf("Your destination account has a different coin!\n Do you wish to continue?\n 0 = No \n 1 = Yes\n");
    cin>>decision;
        if (decision == 0)
        {
            printf("Transaction aborted!\n");
            return;
        } else
        {
            this->amount -= exchange(amount,this->coin,dst.get_currency());
            dst.add_amount(amount);
        }
}

ostream& operator<<(ostream& os, Account a)
{
    os << "| " << setw(35) << a.IBAN << " | " << setw(50) << a.owner << " | " << setw(5) << currencies[a.coin] << " | " << setw(10) << " |";
    return os;
}


void Account::add_amount(int amount)
{
    this->amount += amount;
}
