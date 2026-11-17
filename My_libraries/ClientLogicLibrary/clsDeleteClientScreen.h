#pragma once
#include <iostream>
#include "BankClientlibrary/clsBankClient.h"
#include "personLibrary/clsPerson.h"
#include "ScreenLibrary/clsScreen.h"
#include "InputValidateLibrary/clsInputValidate.h"


class clsDeleteClientScreen : protected clsScreen
{
private:

    static void _PrintClient(clsBankClient client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << client.FirstName;
        cout << "\nLastName    : " << client.LastName;
        cout << "\nFull Name   : " << client.FullName();
        cout << "\nEmail       : " << client.Email;
        cout << "\nPhone       : " << client.Phone;
        cout << "\nAcc. Number : " << client.AccountNumber();
        cout << "\nPassword    : " << client.PinCode;
        cout << "\nBalance     : " << client.AccountBalance;
        cout << "\n___________________\n";

    }
public: 

    static void ShowDeleteClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
        {
            return;// this will exit the function and it will not continue
        }

        _DrawScreenHeader("\t  Delete Client Screen");

        string AccountNumber = "";

        cout << "\nEnter Account number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, Choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient client = clsBankClient::Find(AccountNumber);
        _PrintClient(client);

        cout << "\nAre you sure you want to delete this client? y/n \n";
        char answer = 'n';
        cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {
            if (client.DeleteClient())
            {
                cout << "\nClient Deleted Successfully \n";
                _PrintClient(client);

            }
            else
            {
                cout << "\nError client was not deleted \n";
            }
        }
    }

};