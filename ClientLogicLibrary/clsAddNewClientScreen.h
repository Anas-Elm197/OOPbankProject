#pragma once
#include <iostream>
#include "BankClientlibrary/clsBankClient.h"
#include "ScreenLibrary/clsScreen.h"
#include "InputValidateLibrary/clsInputValidate.h"

using namespace std;

class clsAddNewClientScreen : protected clsScreen
{
private:

   static void _ReadClientInfo(clsBankClient& client)
    {
        cout << "\nEnter First name: ";
        client.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter last name: ";
        client.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Phone number: ";
        client.Phone = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        client.Email = clsInputValidate::ReadString();

        cout << "\nEnter Pin code: ";
        client.PinCode = clsInputValidate::ReadString();

        cout << "\nEnter Account balance: ";
        client.AccountBalance = clsInputValidate::ReadNumber<float>();
    }

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

public :
   static void AddNewClient()
    {

       if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
       {
           return;// this will exit the function and it will not continue
       }

       _DrawScreenHeader("\t   Add New Client Screen");

        string AccountNumber = "";

        cout << "\nEnter Account number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is Already used, Choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Newclient = clsBankClient::GetAddNewClientObject(AccountNumber);

        _ReadClientInfo(Newclient);
        clsBankClient::enSaveResult SaveResult;

        SaveResult = Newclient.Save();

        switch (SaveResult)
        {
        case clsBankClient::enSaveResult::svSucceded:
        {
            cout << "\nClient Added Successfully :-)\n";
            _PrintClient(Newclient);
            break;
        }
        case clsBankClient::enSaveResult::svFailedEmptyObject:
        {
            cout << "\nError, account was not saved because it's empty\n";
            break;

        }
        case clsBankClient::svFailedAccountNumberExicts:
        {
            cout << "\nCan't Save this account because it already exict\n";
            break;
        }
        }
    }

};