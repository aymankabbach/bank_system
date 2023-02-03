#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include <vector>
#include <iomanip>

class clsManageUsersMenuScreen: protected clsScreen
{
private:
    enum enManagerUsers_menu_options {
            enList_clients = 1, enAdd_new_client = 2, enUpdate_client = 3, enFind_client = 4,
            enDelete_client = 5, enExit = 6,
    };
    static short _read_user_choice(short size)
    {
        cout <<setw(37) << left << ""<< "Choose what do you want to do? [1 to "+to_string(size)+"]? ";
        short user_choice = clsInputValidate::read_short_number_between(1,size,"Enter Number between 1 to "+to_string(size)+" ?");
        return user_choice;
    }
    static void _back_to_ManageUsers_main_menu()
    {
        cout<<"\npress any key to go back to Main Menu"<<endl;
        system("pause>0");
        Show_ManageUsers_Menu_Screen();
    }
    static void _Perfrom_ManageUsers_menu_option(enManagerUsers_menu_options ManagerUsers_Menu_option)
        {
            switch (ManagerUsers_Menu_option)
            {
            case enManagerUsers_menu_options::enList_clients:
            {
                system("cls");
                _back_to_ManageUsers_main_menu();
                break;
            }
            case enManagerUsers_menu_options::enAdd_new_client:
            {
                system("cls");
                _back_to_ManageUsers_main_menu();
                break;
            }
            case enManagerUsers_menu_options::enUpdate_client:
            {
                system("cls");
                _back_to_ManageUsers_main_menu();
                break;
            }
            case enManagerUsers_menu_options::enFind_client:
            {
                system("cls");
                _back_to_ManageUsers_main_menu();
                break;
            }
            case enManagerUsers_menu_options::enDelete_client:
            {
                system("cls");
                _back_to_ManageUsers_main_menu();
                break;
            }
            case enManagerUsers_menu_options::enExit:
            {
                break;
            }
        }
    }
public:
    static void Show_ManageUsers_Menu_Screen()
    {
        system("cls");
        _DrawScreenHeader("\t\tManage User Menu Screen");
        vector <string> choices={"Show Client List","Add New Client","Update Client Info","Find Client"
        ,"Delete Client","Back to Main Menu"};
        cout << setw(37) << left <<""<< "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        for (short x=0;x<choices.size();x++)
        {
            cout << setw(37) << left << "" << "\t"<<x+1<<" "<<choices[x]<<".\n";
        }
        cout << setw(37) << left << "" << "===========================================\n";
        _Perfrom_ManageUsers_menu_option((enManagerUsers_menu_options) _read_user_choice(choices.size()));
    } 
};