#pragma once

#include "Global.h"
#include "UsersLogicLibrary/clsUser.h"
#include "ScreenLibrary/clsScreen.h"
#include "ScreenLibrary/clsMainScreen.h"
#include <iomanip>
#include <iostream>

class clsLoginScreen : protected clsScreen
{
private:

    static  bool _Login()
    {
        bool LoginFaild = false;
        short FailedLoginCount = 0;

        string Username, Password;
       
        do
        {
            if (LoginFaild)
            {
                FailedLoginCount++;
                cout << "\nInvlaid Username/Password!\n";
                cout << "You Have " << (3-FailedLoginCount) << " Trials To Login\n\n";
                
            }
            
            if (FailedLoginCount == 3)
            {
                cout << "\n You are Locked after 3 failed logins\n\n";
                return false;
            }
            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);
            
        CurrentUser.RegisterLogIn();
        clsMainScreen::ShowMainMenue();
        return true;
    }

public:


    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
       return  _Login();

    }




};