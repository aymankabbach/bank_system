#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>

using namespace std;

class clsFindUserScreen: protected clsScreen
{
private:
    static void _Print_user_record_line(clsUser User)
    {
        cout << setw(8) << left << "" << "| " << setw(15) << left << User.get_name();
        cout << "| " << setw(20) << left << User.get_username();
        cout << "| " << setw(12) << left << User.get_Password();
        cout << "| " << setw(12) << left << User.get_Permissions();
    }
public:
    static void Show_User()
    {
        string Username=clsUser::get_username_from_user();
        while (clsUser::IsUserExist(Username)==false)
        {
            cout<<"User with "+Username+" ID does not exit"<<endl;
            Username=clsUser::get_username_from_user();
        }
        system("cls");
        _DrawScreenHeader("User :",Username);
        clsUser User=clsUser::Find(Username);
        _Print_user_record_line(User);
    }
};