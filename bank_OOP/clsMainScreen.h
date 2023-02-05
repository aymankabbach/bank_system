#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsClientsScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsTransactionsMenuScreen.h"
#include "clsManageUsersScreen.h"
#include "clsGlobal.h"
#include "clsInputValidate.h"
#include <vector>
#include <iomanip>

using namespace std;

class clsMainScreen: protected clsScreen
{
private:
    enum enMain_menu_options {
            enList_clients = 1, enAdd_new_client = 2, enUpdate_client = 3, enFind_client = 4, 
            enShow_transactions_menu = 5,enManage_users = 6, enDelete_client = 7, enExit = 8
    };
    static short _read_user_choice(short size)
    {
        cout <<setw(37) << left << ""<< "Choose what do you want to do? [1 to "+to_string(size)+"]? ";
        short user_choice = clsInputValidate::read_short_number_between(1,size,"Enter Number between 1 to "+to_string(size)+" ?");
        return user_choice;
    }
    static void _Logout()
    {
        Current_User=clsUser::Find("","");
    }
    static void _back_to_main_menu()
    {
        cout<<"\npress any key to go back to Main Menu"<<endl;
        system("pause>0");
        Show_Main_Menu();
    }
    static void _Perfrom_main_menu_option(enMain_menu_options Main_Menu_option)
        {
            switch (Main_Menu_option)
            {
            case enMain_menu_options::enList_clients:
            {
                system("cls");
                clsClientsScreen::ShowClientsList();
                _back_to_main_menu();
                break;
            }
            case enMain_menu_options::enAdd_new_client:
            {
                system("cls");
                clsAddNewClientScreen::show_AddNewClient_screen();
                _back_to_main_menu();
                break;
            }
            case enMain_menu_options::enUpdate_client:
            {
                system("cls");
                clsUpdateClientScreen::Show_update_screen();
                _back_to_main_menu();
                break;
            }
            case enMain_menu_options::enFind_client:
            {
                system("cls");
                clsFindClientScreen::Show_client();
                _back_to_main_menu();
                break;
            }
            case enMain_menu_options::enShow_transactions_menu:
            {
                system("cls");
                clsTransactionsMenuScreen::Show_Transactions_main_menu_screen();
                _back_to_main_menu();
                break;
            }
            case enMain_menu_options::enManage_users:
            {
                system("cls");
                clsManageUsersMenuScreen::Show_ManageUsers_Menu_Screen();
                _back_to_main_menu();
                break;
            }
            case enMain_menu_options::enDelete_client:
            {
                system("cls");
                clsDeleteClientScreen::show_DeleteClient_screen();
                _back_to_main_menu();
                break;
            }
            case enMain_menu_options::enExit:
            {
                system("cls");
                _Logout();
                break;
            }
            }
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
        _Perfrom_main_menu_option((enMain_menu_options)_read_user_choice(choices.size()));
    } 
};