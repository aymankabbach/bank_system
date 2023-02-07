#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <vector>
#include <iomanip>

class clsUpdateUserScreen: protected clsScreen
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
        cout << "\nRegister Login? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pLogInRegister;
        }
        return Permissions;
    }
public:
    static void Show_update_screen()
    {
        _DrawScreenHeader("Update User's info screen");
        string Username=clsUser::get_username_from_user();
        while (clsUser::IsUserExist(Username)==false)
        {
            cout<<"client with "+Username+" ID does not exit"<<endl;
            Username=clsUser::get_username_from_user();
        }
        clsUser User=clsUser::Find(Username);
        User.get_info();
        User.set_Permissions(_Read_Permissions_To_Set());
        clsUser::enSaveResults SaveResults=User.Save();
        switch (SaveResults)
        { 
            case clsUser::enSaveResults::svSucceeded:
            {
                cout<<"user was updated successfully\n";
                break;
            }
            case clsUser::enSaveResults::svFaildEmptyObject:
            {
                cout<<"\nError, user as not saved because it is empty";
                break;
            }
        }
    }
};