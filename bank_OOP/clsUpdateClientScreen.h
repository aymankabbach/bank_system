#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <vector>
#include <iomanip>

class clsUpdateClientScreen: protected clsScreen
{
public:
    static void Show_update_screen()
    {
        if (!Check_Access_Rights(clsUser::enPermissions::pUpdateClients))
        {
            return;
        } 
        _DrawScreenHeader("Update client's info screen");
        string ID=clsBankClient::get_ID_from_user("enter client's ID");
        while (clsBankClient::IsClientExist(ID)==false)
        {
            cout<<"client with "+ID+" ID does not exit"<<endl;
            ID=clsBankClient::get_ID_from_user("enter client's ID");
        }
        clsBankClient client=clsBankClient::Find(ID);
        client.update_info(client);
        clsBankClient::enSaveResults SaveResults=clsBankClient::save(client);
        switch (SaveResults)
        { 
            case clsBankClient::enSaveResults::svSucceeded:
            {
                cout<<"account was updated successfully\n";
                break;
            }
            case clsBankClient::enSaveResults::svFailEmptyObject:
            {
                cout<<"\nError, Account as not saved because it is empty";
                break;
            }
        }
    }
};