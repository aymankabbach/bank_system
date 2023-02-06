#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>

using namespace std;

class clsFindClientScreen: protected clsScreen
{
private:
    static void _Print_client_record_line(clsBankClient Client)
    {
        cout << setw(8) << left << "" << "| " << setw(15) << left << Client.get_ID();
        cout << "| " << setw(20) << left << Client.get_name();
        cout << "| " << setw(12) << left << Client.get_Balance();
    }
public:
    static void Show_client()
    {
        if (!Check_Access_Rights(clsUser::enPermissions::pFindClient))
        {
            return;
        } 
        string ID=clsBankClient::get_ID_from_user();
        while (clsBankClient::IsClientExist(ID)==false)
        {
            cout<<"client with "+ID+" ID does not exit"<<endl;
            ID=clsBankClient::get_ID_from_user();
        }
        system("cls");
        _DrawScreenHeader("Client :",ID);
        clsBankClient client=clsBankClient::Find(ID);
        _Print_client_record_line(client);
    }
};