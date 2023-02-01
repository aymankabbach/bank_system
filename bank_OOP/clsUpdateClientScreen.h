#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <vector>
#include <iomanip>

class clsAddNewClientScreen: protected clsScreen
{
public:
    static void Show_update_screen()
    {
        _DrawScreenHeader("Update client's info screen");
        string ID=clsBankClient::get_ID_from_user();
        while (clsBankClient::IsClientExist(ID)==false)
        {
            cout<<"client with "+ID+" ID does not exit"<<endl;
            ID=clsBankClient::get_ID_from_user();
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