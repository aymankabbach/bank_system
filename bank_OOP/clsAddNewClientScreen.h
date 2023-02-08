#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <vector>
#include <iomanip>

using namespace std;

class clsAddNewClientScreen: protected clsScreen
{
public:
    static void show_AddNewClient_screen()
    {
        if (!Check_Access_Rights(clsUser::enPermissions::pAddNewClient))
        {
            return;
        } 
        _DrawScreenHeader("Add new client screen");
        string ID=clsBankClient::get_ID_from_user("enter client's ID");
        while (clsBankClient::IsClientExist(ID))
        {
            cout<<"client's ID already exist"<<endl;
            ID=clsBankClient::get_ID_from_user("enter client's ID");
        }
        clsBankClient new_client=clsBankClient::get_add_new_client_object(ID);
        new_client.update_info(new_client);
        clsBankClient::enSaveResults SaveResults=clsBankClient::save(new_client);
        switch (SaveResults)
        { 
            case clsBankClient::enSaveResults::svSucceeded:
            {
                cout<<"account was added successfully\n";
                break;
            }
            case clsBankClient::enSaveResults::svFailEmptyObject:
            {
                cout<<"\nError, Account as not saved because it is empty";
                break;
            }
            case clsBankClient::enSaveResults::svFailIdExists:
            {
                cout<<"client already exists"<<endl;
                break;
            }
        }
    }
};