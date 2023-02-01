#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <vector>
#include <iomanip>

using namespace std;

class clsDeleteClientScreen: protected clsScreen
{
public:
    static void show_DeleteClient_screen()
    {
        _DrawScreenHeader("Delete client screen");
        string ID=clsBankClient::get_ID_from_user();
        while (clsBankClient::IsClientExist(ID)==false)
        {
            cout<<"client with "+ID+" does not already exist"<<endl;
            ID=clsBankClient::get_ID_from_user();
        }
        clsBankClient client=clsBankClient::Find(ID);
        char answer=clsBankClient::confirm_answer();
        if (answer=='Y' || answer=='y')
        {
            vector <clsBankClient> vClients=clsBankClient::load_data_from_File();
            clsBankClient::delete_client_from_file(vClients,client);
            cout<<"client deleted successfully"<<endl;
        }
        else
        {
            cout<<"error, client was not deleted"<<endl;
        }
    }
};