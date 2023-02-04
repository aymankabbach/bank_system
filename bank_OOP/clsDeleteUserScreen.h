#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <vector>
#include <iomanip>

using namespace std;

class clsDeleteUserScreen: protected clsScreen
{
public:
    static void show_Delete_User_screen()
    {
        _DrawScreenHeader("Delete User screen");
        string Username=clsUser::get_username_from_user();
        while (clsUser::IsUserExist(Username)==false)
        {
            cout<<"User with "+Username+" does already exist"<<endl;
            Username=clsUser::get_username_from_user();
        }
        clsUser user=clsUser::Find(Username);
        char answer=clsUser::confirm_answer();
        if (answer=='Y' || answer=='y')
        {
            vector <clsUser> vUsers=clsUser::Get_Users_List();
            user.Delete();
            cout<<"user deleted successfully"<<endl;
        }
        else
        {
            cout<<"error, user was not deleted"<<endl;
        }
    }
};