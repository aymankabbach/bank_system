#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <vector>

using namespace std;

class clsDepositScreen : protected clsScreen
{
private:
    static short _get_deposit_value()
    {
        cout<<"how much do you want to deposit\n";
        short amount=clsInputValidate::Read_short_number("invalid, please enter a number");
        return amount;
    }
public:
    static void Show_deposit_screen()
    {
        _DrawScreenHeader("Deposit screen");
        string ID=clsBankClient::get_ID_from_user("enter client's ID");
        while (clsBankClient::IsClientExist(ID)==false)
        {
            cout<<"Client with "+ID+" does not exist"<<endl;
            ID=clsBankClient::get_ID_from_user("enter client's ID");
        }
        clsBankClient client=clsBankClient::Find(ID);
        client.deposit(_get_deposit_value());
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