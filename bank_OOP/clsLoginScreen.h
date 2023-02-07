#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "clsDate.h"
#include "clsGlobal.h"
#include <iomanip>

using namespace std;

class clsLoginScreen: protected clsScreen
{
private:
    static string _convert_user_object_to_line(string delim="////")
    {
        string Line;
        Line+=clsDate::get_current_complet_date()+delim;
        Line+=Current_User.get_username()+delim+Current_User.get_Password()+delim+to_string(Current_User.get_Permissions());
        return Line;
    }
    static void _regist_login()
    {
        fstream MyFile;
        string Line;
        MyFile.open("Login_Register.txt", ios::out | ios::app);
        if (MyFile.is_open())
        {
            Line=_convert_user_object_to_line();
            MyFile << Line << endl;
            MyFile.close();
        }
    } 
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
        _regist_login();
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