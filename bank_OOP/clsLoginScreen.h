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
    static bool _login()
    {
        bool login_failed=false;
        short attempts=0;
        string username,Password;
        do 
        {
            if (login_failed)
            {
                    if (attempts==3)
                {
                    cout<<"login failed 3 times"<<endl;
                    return false;
                }
                cout<<"invalid username/Password\n";
                cout<<"you have "<<3-attempts<<" trials to login"<<endl; 
            }
            cout<<"enter the username\n";
            cin>>username;
            cout<<"enter the password"<<endl;
            cin>>Password;
            Current_User=clsUser::Find(username,Password);
            login_failed=Current_User.IsEmpty();
            if (login_failed)
            {
                attempts+=1;
            }
        } while (login_failed);
        clsMainScreen::Show_Main_Menu();
        return true;
    }
public:
    static bool show_login_screen()
    {
        system("cls");
        _DrawScreenHeader("login screen");
        return _login();
    }
};