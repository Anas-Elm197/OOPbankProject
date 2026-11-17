#pragma once
#include <iostream>
#include "BankClientlibrary/clsBankClient.h"
#include "ScreenLibrary/clsScreen.h"
#include "InputValidateLibrary/clsInputValidate.h"
using namespace std;

class clsDepositScreen : protected clsScreen
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

	static void ShowDepositScreen()
	{
		_DrawScreenHeader("\t  Deposit to client Screen");

		string AccountNumber = _ReadAccountNumber();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "Client with [" << AccountNumber << "] doesn't exict. \n";
			AccountNumber = _ReadAccountNumber();
		}
		clsBankClient client = clsBankClient::Find(AccountNumber);
		_PrintClient(client);


		double Amount = 0;
		cout << "\nEnter How Much you want to add to your acc: ";
		Amount = clsInputValidate::ReadNumber<double>();

		cout << "\nAre you sure you want to perform this transaction? y/n";
		char Answer = 'n';
		cin >> Answer;


		if (Answer == 'Y' || Answer == 'y')
		{
			client.Deposit(Amount);
			cout << "\nAmount Deposited Successfully.\n";
			cout << "\nNew Balance Is: " << client.AccountBalance;

		}
		else
		{
			cout << "\nOperation was cancelled.\n";
		}


	}

};