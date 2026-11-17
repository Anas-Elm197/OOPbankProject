#pragma once
#include <iostream>
#include "BankClientlibrary/clsBankClient.h"
#include "ScreenLibrary/clsScreen.h"
#include "InputValidateLibrary/clsInputValidate.h"
using namespace std;

class clsWithdrawScreen : protected clsScreen
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

	static string _ReadAccountNumber()
	{
		string AccountNumber = "";
		cout << "\nPlease enter AccountNumber? ";
		cin >> AccountNumber;
		return AccountNumber;
	}


public:

	static void ShowWithdrawScreen()
	{
		_DrawScreenHeader("\t  Withdraw Screen");

		string AccountNumber = _ReadAccountNumber();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "Client with [" << AccountNumber << "] doesn't exict. \n";
			AccountNumber = _ReadAccountNumber();
		}
		clsBankClient client = clsBankClient::Find(AccountNumber);
		_PrintClient(client);


		double Amount = 0;
		cout << "\nEnter How Much you want to withdraw from your acc: ";
		Amount = clsInputValidate::ReadNumber<double>();

		cout << "\nAre you sure you want to perform this transaction? y/n ";
		char Answer = 'n';
		cin >> Answer;


		if (Answer == 'Y' || Answer == 'y')
		{
			if ( client.Withdraw(Amount) )
			{
				cout << "\nAmount Withdrew Successfully.\n";
				cout << "\nNew Balance Is: " << client.AccountBalance;
			}
			else
			{
				cout << "\nCannot withdraw, Insuffecient Balance!\n";
				cout << "\nAmout to withdraw is: " << Amount;
				cout << "\nYour Balance is: " << client.AccountBalance;

			}

		}
		else
		{
			cout << "\nOperation was cancelled.\n";
		}


	}

};