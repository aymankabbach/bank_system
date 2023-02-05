#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "clsGlobal.h"
#include <iomanip>

using namespace std;

class clsLoginScreen: protected clsScreen
{
private:
    static void _login()
    {
        bool login_failed=false;
        string username,Password;
        do 
        {
            if (login_failed)
            {
                cout<<"invalid username/Password"<<endl;
            }
            cout<<"enter the username\n";
            cin>>username;
            cout<<"enter the password"<<endl;
            cin>>Password;
            Current_User=clsUser::Find(username,Password);
            login_failed=Current_User.IsEmpty();
        } while (login_failed);
        clsMainScreen::Show_Main_Menu();
    }
public:
    static void show_login_screen()
    {
        system("cls");
        _DrawScreenHeader("login screen");
        _login();
    }
};