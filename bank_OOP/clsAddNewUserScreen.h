#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <vector>
#include <iomanip>

using namespace std;

class clsAddNewUserScreen: protected clsScreen
{
private:
    static int _Read_Permissions_To_Set()
    {
        int Permissions = 0;
        char Answer = 'n';
        cout << "\nDo you want to give full access? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }
        cout << "\nDo you want to give access to : \n ";
        cout << "\nShow Client List? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pListClients;
        }
        cout << "\nAdd New Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pAddNewClient;
        }
        cout << "\nDelete Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pDeleteClient;
        }
        cout << "\nUpdate Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pUpdateClients;
        }
        cout << "\nFind Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pFindClient;
        }
        cout << "\nTransactions? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pTranactions;
        }
        cout << "\nManage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pManageUsers;
        }
        return Permissions;
    }
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
        new_user.set_Permissions(_Read_Permissions_To_Set());
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