#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <vector>
#include <iomanip>

using namespace std;

class clsAddNewUserScreen: protected clsScreen
{
public:
    static void show_AddNewUser_screen()
    {
        _DrawScreenHeader("Add new user screen");
        string Username=clsUser::get_username_from_user();
        while (clsUser::IsUserExist(Username))
        {
            cout<<"user with the ussername "+Username+" already exist"<<endl;
            Username=clsUser::get_username_from_user();
        }
        clsUser new_user=clsUser::Get_Add_New_User_Object(Username);
        new_user.get_info(new_user);
        clsUser::enSaveResults SaveResults=new_user.Save();
        switch (SaveResults)
        { 
            case clsUser::enSaveResults::svSucceeded:
            {
                cout<<"User was added successfully\n";
                break;
            }
            case clsUser::enSaveResults::svFaildEmptyObject:
            {
                cout<<"\nError, User was not saved because it is empty";
                break;
            }
            case clsUser::enSaveResults::svFaildUserExists:
            {
                cout<<"user already exists"<<endl;
                break;
            }
        }
    }
};