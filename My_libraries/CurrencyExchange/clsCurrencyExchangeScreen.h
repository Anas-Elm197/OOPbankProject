#pragma once
#include "ScreenLibrary/clsScreen.h"
#include <iostream>
#include <iomanip>
#include "InputValidateLibrary/clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "ScreenLibrary/clsMainScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"



class clsCurrencyExchange : protected clsScreen
{
private:

    enum enCurrencyExchangeMenueOptions {
        eListCurrencies = 1, eFindCurrency = 2, eUpdateRate = 3, eCurrencyCalculator = 4, eMainMenue = 5
    };
	

    static short ReadCurrencyExchangeMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadNumberBetween(1, 5, "Enter Number between 1 to 5? ");
        return Choice;
    }
	
    static void _GoBackToCurrencyExchangeMenue()
    {
        cout << "\n\nPress any key to go back to Currency Exchange Menue...";
        system("pause>0");
        ShowCurrencyExchangeScreen();
    }

    static void _ShowListCurrenciesScreen()
    {
        //cout << "\n Currencies list screen will be here.....\n";
        clsCurrenciesListScreen::ShowCurrenciesListScreen();
    }
    static void _ShowFindCurrenciesScreen()
    {
        //cout << "\n Find Currencies screen will be here.....\n";
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }
    static void _ShowUpdateRateScreen()
    {
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
    }

    static void _ShowCurrencyCalculatorScreen()
    {
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
    }


    static void _PerformCurrencyExchangeMenueOptions(enCurrencyExchangeMenueOptions CurrencyExchangeOption)
    {
        switch (CurrencyExchangeOption)
        {
        case enCurrencyExchangeMenueOptions::eListCurrencies:
        {
            system("cls");
            _ShowListCurrenciesScreen();
            _GoBackToCurrencyExchangeMenue();
            break;
        }
        case enCurrencyExchangeMenueOptions::eFindCurrency:
        {
            system("cls");
            _ShowFindCurrenciesScreen();
            _GoBackToCurrencyExchangeMenue();
            break;
        }
        case enCurrencyExchangeMenueOptions::eUpdateRate:
        {
            system("cls");
            _ShowUpdateRateScreen();
            _GoBackToCurrencyExchangeMenue();
            break;
        }
        case enCurrencyExchangeMenueOptions::eCurrencyCalculator:
        {
            system("cls");
            _ShowCurrencyCalculatorScreen();
            _GoBackToCurrencyExchangeMenue();
            break;
        }
        case enCurrencyExchangeMenueOptions::eMainMenue:
        {

        }

        }
    }

public:

	static void ShowCurrencyExchangeScreen()
	{
        system("cls");
        _DrawScreenHeader("Currency Exchnage Main Screen\n");
			
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Currency Exchnage Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currencies.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";


        _PerformCurrencyExchangeMenueOptions(enCurrencyExchangeMenueOptions(ReadCurrencyExchangeMenueOption()));
	}

};