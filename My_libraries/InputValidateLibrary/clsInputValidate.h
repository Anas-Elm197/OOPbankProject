#pragma once

#include <iostream>
#include <string>
#include <limits>
#include <type_traits>
#include "StringLibrary/clsDate.h"
#include "Utility_library/clsUtil.h"
using namespace std;

class clsInputValidate
{
public:

	static string ReadString()
	{
		string s1 = "";
		getline(cin >> ws, s1);
		return s1;
	}

	template <typename T>
	static bool IsNumberBetween(T num, T from, T to)
	{
		if (num >= from && num <= to)
			return true;
		else
			return false;
	}

	/*static bool IsNumberBetween(float num, float from, float to)
	{
		if (num >= from && num <= to)
			return true;
		else
			return false;
	}

	static bool IsNumberBetween(int num, int from, int to)
	{
		if (num >= from && num <= to)
			return true;
		else
			return false;
	}

	static bool IsNumberBetween(double num, double from, double to)
	{
		if (num >= from && num <= to)
			return true;
		else
			return false;
	}*/

	static bool IsDateBetween(clsDate Date1, clsDate From, clsDate To)
	{
		if ((clsDate::IsDate1AfterDate2(Date1, From) || (clsDate::IsDate1EqualDate2(Date1, To))) && (clsDate::IsDate1BeforeDate2(Date1, To) || clsDate::IsDate1EqualDate2(Date1, To)))
		{
			return true;
		}
		if ((clsDate::IsDate1AfterDate2(Date1, To) || clsDate::IsDate1EqualDate2(Date1, To)) && (clsDate::IsDate1BeforeDate2(Date1, From) || clsDate::IsDate1EqualDate2(Date1, From)))
		{
			return true;
		}
		return false;

	}

	template <typename T>
	static T ReadNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		T Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	/*static int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		int Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static int ReadIntNumberBetween(int from, int to, string message = "Number is not within range, Enter again:")
	{
		int number;
		number = ReadIntNumber();
		while (!IsNumberBetween(number, from, to))
		{
			cout << message << endl;
			number = ReadIntNumber();
		}
		return number;
	}
	
	static short ReadShortNumberBetween(short from, short to, string message = "Number is not within range, Enter again:")
	{
		short number;
		number = ReadIntNumber();
		while (!IsNumberBetween(number, from, to))
		{
			cout << message << endl;
			number = ReadIntNumber();
		}
		return number;
	}

	static double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		double Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}
	*/
	template <typename T>
	static T ReadNumberBetween(T from, T to, string message = "Number is not within range, Enter again:")
	{
		T number;
		number = ReadNumber<T>();
		while (!IsNumberBetween(number, from, to))
		{
			cout << message << endl;
			number = ReadNumber<T>();
		}
		return number;
	}

	static bool IsValideDate(clsDate Date)
	{
		return	clsDate::IsValidDate(Date);
	}

	

};