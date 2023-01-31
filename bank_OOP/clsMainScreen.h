#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <vector>
#include <iomanip>

using namespace std;

class clsMainScreen: protected clsScreen
{
private:
    enum enMainMenueOptions {
            enListClients = 1, enAddNewClient = 2, enUpdateClient = 3, enFindClient = 4, 
            enShowTransactionsMenue = 5,enManageUsers = 6, enDeleteClient = 7, enExit = 8
    };
    static short _read_user_choice()
    {
        cout <<setw(37) << left << ""<< "Choose what do you want to do? [1 to 8]? ";
        short user_choice = clsInputValidate::read_short_number_between(1,8,"Enter Number between 1 to 8? ");
        return user_choice;
    }
public:
    static void Show_Main_Menu()
    {
        system("cls");
        _DrawScreenHeader("\t\tMain Screen");
        vector <string> choices={"Show Client List","Add New Client","Update Client Info","Find Client",
        "Transactions","Manage Users","Delete Client","Logout"};
        cout << setw(37) << left <<""<< "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        for (short x=0;x<choices.size();x++)
        {
            cout << setw(37) << left << "" << "\t"<<x+1<<" "<<choices[x]<<".\n";
        }
        cout << setw(37) << left << "" << "===========================================\n";
        short user_choice=_read_user_choice();
    } 
};