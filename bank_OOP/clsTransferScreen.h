#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <vector>

using namespace std;

class clsTransferScreen : protected clsScreen
{
private:
    static float _get_withdraw_value(clsBankClient client)
    {
        cout<<"how much do you want to send\n";
        cout<<"your balance is "+to_string(client.get_Balance())<<endl;
        string message="invalid, please enter a number between "+to_string(0)+" and "+to_string(client.get_Balance());
        float amount=clsInputValidate::read_float_number_between(0,client.get_Balance(),message);
        return amount;
    }
    static clsBankClient get_client_ID(string message)
    {
        string ID=clsBankClient::get_ID_from_user(message);
        while (clsBankClient::IsClientExist(ID)==false)
        {
            cout<<"Client with "+ID+" does not exist"<<endl;
            ID=clsBankClient::get_ID_from_user(message);
        }
        clsBankClient client=clsBankClient::Find(ID);
        return client;
    }
public:
    static void Show_transfer_Screen()
    {
        _DrawScreenHeader("Transfer screen");
        clsBankClient client_sender=get_client_ID("\nPlease Enter ID to Transfer From: ");
        clsBankClient client_receiver=get_client_ID("\nPlease Enter ID to Transfer to: ");
        float amount=_get_withdraw_value(client_sender);
        cout << "\nAre you sure you want to perform this operation? y/n? ";
        char answer;
        cin >> answer;
        if (answer=='y'|| answer=='Y')
        {
            client_sender.transfer(amount,client_receiver);
            cout << "\nTransfer done successfully\n";
        }
        else
        {
            cout<<"transfer canceled"<<endl;
        }
    }
};