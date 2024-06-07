//
// Created by Andrei-Claudiu Gheorghiță on 26.05.2024.
//

#include "accounts.h"
#include <fstream>
#include <iostream>
#include <sstream>

#define FILENAME "Data.csv"
#define HEADER "IBAN,owner,coin,amount"

Accounts::Accounts()
{
    size = 0;
    ifstream fin(FILENAME);
    if (fin.is_open())
    {
        string header;
        getline(fin, header);
        if (header != HEADER)
        {
            throw runtime_error("Malformed database!");
        }
        while (!fin.eof())
        {
            string line;
            getline(fin, line);
            if (line == "")
                return;
            stringstream ss(line);
            string IBAN, owner, coin;
            currency coin_c;
            int amount;
            getline(ss, IBAN, ',');
            getline(ss, owner, ',');
            getline(ss, coin, ',');
            ss >> amount;
            if (coin == "RON")
            {
                coin_c = RON;
            }
            else if (coin == "EUR")
            {
                coin_c = EUR;
            }
            else if (coin == "USD")
            {
                coin_c = USD;
            }
            accounts[size] = new Account(IBAN, owner, coin_c, amount);
            size++;
        }
    }
    else
    {
        cout << "No database found. Initializing database...";
        ofstream fout(FILENAME);
        fout << HEADER << endl;
        fout.close();
    }
}

Accounts::~Accounts()
{
    ofstream fout(FILENAME);
    fout << HEADER << endl;
    for (int i = 0; i < size; i++)
    {
        fout << *accounts[i];
    }
    fout.close();
}


