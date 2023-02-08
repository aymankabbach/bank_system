#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <vector>

using namespace std;

class clsWithdrawScreen : protected clsScreen
{
private:
    static short _get_withdraw_value(clsBankClient client)
    {
        cout<<"how much do you want to withdraw\n";
        cout<<"your balance is "+to_string(client.get_Balance())<<endl;
        string message="invalid, please enter a number between "+to_string(0)+" and "+to_string(client.get_Balance());
        short amount=clsInputValidate::read_short_number_between(0,client.get_Balance(),message);
        return amount;
    }
public:
    static void Show_withdraw_screen()
    {
        string ID=clsBankClient::get_ID_from_user("enter client's ID");
        while (clsBankClient::IsClientExist(ID)==false)
        {
            cout<<"Client with "+ID+" does not exist"<<endl;
            ID=clsBankClient::get_ID_from_user("enter client's ID");
        }
        clsBankClient client=clsBankClient::Find(ID);
        system("cls");
        _DrawScreenHeader("withdraw screen");
        client.withdraw(_get_withdraw_value(client));
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