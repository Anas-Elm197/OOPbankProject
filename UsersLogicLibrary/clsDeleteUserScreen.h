#pragma once
#include "ScreenLibrary/clsScreen.h"
#include "UsersLogicLibrary/clsUser.h"
#include "InputValidateLibrary/clsInputValidate.h"
#include <iostream>
using namespace std;



class clsDeleteUser : protected clsScreen
{

private:

    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUser Name   : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________\n";

    }


public:

    static void DeleteUser()
    {
        _DrawScreenHeader("\t Delete User Screen");

        string UserName = "";

        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();
        while (!(clsUser::IsUserExist(UserName)))
        {
            cout << "\nUserName number is not found, Choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::Find(UserName);
        _PrintUser(User);


        cout << "\nAre you sure you want to delete this User? y/n \n";
        char answer = 'n';
        cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {
            if (User.Delete())
            {
                cout << "\nUser Deleted Successfully \n";
                _PrintUser(User);

            }
            else
            {
                cout << "\nError User was not deleted \n";
            }
        }
    }
};