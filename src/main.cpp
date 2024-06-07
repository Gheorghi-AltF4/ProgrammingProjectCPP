#include <iostream>
#include <vector>
#include "accounts.h"

using namespace std;

bool validate_name(string s)
{
    for (string::iterator it = s.begin(); it != s.end(); it++)
    {
        if (!isalpha(*it))
            return false;
    }
    return true;
}

void handle_input_error()
{
    cout << "Invalid input provided!\n";
}

void print_menu()
{
    cout << "\n 1 = Create Account \n 2 = View Account \n 3 = Delete Account \n 4 = Edit Account \n 5 = Perform Transaction \n 0 = Exit \n\n";
}

int main(int argc, char *argv[])
{
    string user;
    try
    {
        if (argc != 4)
        {
            throw runtime_error("Invalid arguments!\nusage: PP login [NAME] [SURNAME]");
        }
        else
        {
            string command = argv[1];
            if (command != "login")
                throw runtime_error("Invalid arguments!\nusage: PP login [NAME] [SURNAME]");
        }
        string name = argv[2], surname = argv[3];
        if (!validate_name(name))
            throw runtime_error("Invalid name, use only letters");
        if (!validate_name(surname))
            throw runtime_error("Invalid surname, use only letters");
        user = name + surname;
        cout << "Successfully logged in\nHello, " << user << "!\n";
    }
    catch (runtime_error e)
    {
        cout << e.what();
        return 1;
    }
    Accounts accounts;
    while (1)
    {
        try
        {
            print_menu();
            int input = -1;
            // char input_string[64];
            // scanf("%63s", input_string);
            // if (strlen(input_string) != 1 || sscanf(input_string, "%d", &input) == 0)
            //     input = -1;
            cin >> input;
            if (input == 1)
            {
                currency input_currency;
                cout << "Choose a currency: RON = 0, EUR = 1, USD = 2\n";
                cin >> input_currency;
                accounts.create(user, (currency)input_currency);
            }
            else if (input == 2)
            {
                accounts.view(user);
            }
            else if (input == 3)
            {
                string iban;
                cout << "Provide an IBAN:\n";
                cin >> iban;
                if (iban.length() != 24)
                {
                    handle_input_error();
                    continue;
                }
                accounts.close(user, iban);
            }
            else if (input == 4)
            {
                string iban;
                cout << "Provide an IBAN: ";
                cin >> iban;
                if (iban.length() != 24)
                {
                    handle_input_error();
                    continue;
                }
                int amount = -1;
                cout << "Provide an amount: ";
                cin >> amount;
                if (amount <= 0)
                {
                    handle_input_error();
                    continue;
                }
                currency input_currency;
                cout << "Choose a currency: RON = 0, EUR = 1, USD = 2 ";
                cin >> input_currency;
                accounts.edit(user, iban, amount, input_currency);
            }
            else if (input == 5)
            {
                string IBAN_src;
                cout << "Provide a source IBAN: ";
                cin >> IBAN_src;
                if (IBAN_src.length() != 24)
                {
                    handle_input_error();
                    continue;
                }
                string IBAN_dst;
                cout << "Provide a destination IBAN: ";
                cin >> IBAN_dst;
                if (IBAN_dst.length() != 24)
                {
                    handle_input_error();
                    continue;
                }
                int amount = -1;
                cout << "Provide an amount:\n";
                cin >> amount;
                if (amount <= 0)
                {
                    handle_input_error();
                    continue;
                }
                accounts.perform_transaction(IBAN_src, IBAN_dst, amount, user);
            }
            else if (input == 0)
            {
                cout << "Goodbye!...\n";
                break;
            }
            else
            {
                handle_input_error();
            }
        }
        catch (runtime_error e)
        {
            cout << e.what() << endl;
        }
    }
    return 0;
}