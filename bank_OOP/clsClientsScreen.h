#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <vector>
#include <iomanip>

using namespace std;

class clsClientsScreen: protected clsScreen
{
private:
    static void _Print_client_record_line(clsBankClient Client)
    {
        cout << setw(8) << left << "" << "| " << setw(15) << left << Client.get_ID();
        cout << "| " << setw(20) << left << Client.get_name();
        cout << "| " << setw(12) << left << Client.get_Balance();
    }
public:
    static void ShowClientsList()
    {
        if (!Check_Access_Rights(clsUser::enPermissions::pListClients))
        {
            return;
        } 
        vector <clsBankClient> vClients = clsBankClient::get_Clients_List();
        string Title = "\t  Client List Screen";
        string SubTitle ="\t    (" + to_string(vClients.size()) + ") Client(s).";
        _DrawScreenHeader(Title,SubTitle);
        cout <<  setw(8) << left << "" << "| " << left << setw(15) << "ID";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
         if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsBankClient Client : vClients)
            {

                _Print_client_record_line(Client);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }
};