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
    static short _get_withdraw_value(clsBankClient client)
    {
        cout<<"how much do you want to send\n";
        cout<<"your balance is "+to_string(client.get_Balance())<<endl;
        string message="invalid, please enter a number between "+to_string(0)+" and "+to_string(client.get_Balance());
        short amount=clsInputValidate::read_short_number_between(0,client.get_Balance(),message);
        return amount;
    }
public:
    static void Show_transfer_Screen()
    {
        _DrawScreenHeader("Transfer screen");
        string ID_1=clsBankClient::get_ID_from_user();
        while (clsBankClient::IsClientExist(ID_1)==false)
        {
            cout<<"Client with "+ID_1+" does not exist"<<endl;
            ID_1=clsBankClient::get_ID_from_user();
        }
        clsBankClient client_sender=clsBankClient::Find(ID_1);
        string ID_2=clsBankClient::get_ID_from_user();
        while (clsBankClient::IsClientExist(ID_2)==false)
        {
            cout<<"Client with "+ID_2+" does not exist"<<endl;
            ID_2=clsBankClient::get_ID_from_user();
        }
        clsBankClient client_receiver=clsBankClient::Find(ID_2);
        short amount=_get_withdraw_value(client_sender);
        client_sender.withdraw(amount);
        client_receiver.deposit(amount);
        clsBankClient::enSaveResults SaveResults1=clsBankClient::save(client_receiver);
        clsBankClient::enSaveResults SaveResults2=clsBankClient::save(client_sender);
    }
};