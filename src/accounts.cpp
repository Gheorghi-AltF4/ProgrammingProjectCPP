#include <string>
#include "accounts.h"
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <typeinfo>

using namespace std;

const string out_sep = " ===============================================================================================================\n";
const string in_sep = "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

//
// Created by Andrei-Claudiu Gheorghiță on 26.05.2024.
//

const float usd_value[] = {0.21, 1.07, 1};

std::string Account::generate_IBAN()
{
    stringstream ss;
    srand(time(NULL));
    ss << setfill('0') << "RO" << setw(2) << rand() % 100 << "RNCB" << setw(8) << rand() % 100000000 << rand() % 100000000;
    return ss.str();
}

int Account::exchange(int amount, currency from, currency to)
{
    amount = amount * usd_value[from];
    amount = amount / usd_value[to];
    return amount;
}

Account::Account(std::string owner, currency coin)
{
    this->amount = 0;
    this->owner = owner;
    this->coin = coin;
    this->IBAN = generate_IBAN();
    cout << "Created new account with IBAN: " << this->IBAN;
}

Account::Account(std::string IBAN, string owner, currency coin, int amount)
{
    this->amount = amount;
    this->owner = owner;
    this->coin = coin;
    this->IBAN = IBAN;
}

void Account::edit(int amount, currency coin)
{
    this->amount = amount;
    this->coin = coin;
}

std::string Account::get_owner()
{
    return this->owner;
}

currency Account::get_currency()
{
    return this->coin;
}

void Account::transfer(Account &dst, int amount)
{
    if (this->amount < amount)
    {
        std::cout << "Insufficient funds!\n";
        return;
    }
    if (this->coin == dst.get_currency())
    {
        this->amount -= amount;
        dst.amount += amount;
        cout << "Transaction performed successfully!\n";
        return;
    }
    int decision = 0;
    cout << "Your destination account has a different coin!\n Do you wish to continue?\n 0 = No \n 1 = Yes\n";
    cin >> decision;
    if (decision == 0)
    {
        cout << "Transaction aborted!\n";
        return;
    }
    else
    {
        this->amount -= exchange(amount, dst.get_currency(), this->coin);
        dst.add_amount(amount);
        cout << "Transaction successful!" << endl;
    }
}

istream &operator>>(istream &is, currency &coin)
{
    int a = -1;
    is >> a;
    if (a < 0 || a > 2)
        throw runtime_error("invalid currency provided");
    coin = (currency)a;
    return is;
}

ostream &operator<<(ostream &os, currency coin)
{
    const string currencies[] = {"RON", "EUR", "USD"};
    os << currencies[coin];
    return os;
}

ostream &operator<<(ostream &os, Account a)
{
    if (typeid(os) == typeid(cout))
    {
        os << left << "| " << setw(35) << a.IBAN << " | " << setw(50) << a.owner << " | " << setw(5) << a.coin << " | " << setw(10) << a.amount << " |";
    }
    else
    {
        os << a.IBAN << "," << a.owner << "," << a.coin << "," << a.amount << "\n";
    }
    return os;
}

string Account::get_IBAN()
{
    return IBAN;
}

void Account::add_amount(int amount)
{
    this->amount += amount;
}

void Accounts::create(string name, currency coin)
{
    accounts[size] = new Account(name, coin);
    size++;
}

void Accounts::close(string name, string IBAN)
{
    for (int i = 0; i < size; i++)
    {
        if (accounts[i]->get_IBAN() == IBAN)
        {
            if (accounts[i]->get_owner() == name)
            {
                delete accounts[i];
                accounts[i] = accounts[size - 1];
                size--;
                cout << "Successfully deleted account!";
                return;
            }
            throw runtime_error("You're not the owner of the account!");
        }
    }
    throw runtime_error("Account not found!");
}

void Accounts::view(string name)
{
    cout << out_sep;
    cout << left << "| " << setw(35) << "IBAN" << " | " << setw(50) << "owner" << " | " << setw(5) << "coin" << " | " << setw(10) << "amount" << " |" << endl;
    for (int i = 0; i < size; i++)
    {
        cout << in_sep;
        if (accounts[i]->get_owner() == name)
            cout << *accounts[i] << endl;
    }
    cout << out_sep;
}
void Accounts::edit(string name, string IBAN, int amount, currency coin)
{
    for (int i = 0; i < size; i++)
    {
        if (accounts[i]->get_IBAN() == IBAN)
        {
            if (accounts[i]->get_owner() == name)
            {
                accounts[i]->edit(amount, coin);
                return;
            }
            else
            {
                throw runtime_error("You're not the owner of the account!");
            }
        }
    }
    throw runtime_error("Account not found!");
}
void Accounts::perform_transaction(string iban_src, string iban_dst, int amount, string name)
{
    if (iban_dst == iban_src)
        throw runtime_error("Cannot perform transaction on the same account!");
    int src_index = -1, dst_index = -1;
    for (int i = 0; i < size; i++)
    {
        if (accounts[i]->get_IBAN() == iban_src)
        {
            if (accounts[i]->get_owner() != name)
                throw runtime_error("You're not the owner of the account!");
            src_index = i;
        }
        if (accounts[i]->get_IBAN() == iban_dst)
            dst_index = i;
    }
    if (src_index == -1)
    {
        throw runtime_error("Source account not found!");
    }
    if (dst_index == -1)
    {
        throw runtime_error("Destination account not found!");
    }
    accounts[src_index]->transfer(*accounts[dst_index], amount);
}