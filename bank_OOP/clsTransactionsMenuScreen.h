#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsInputValidate.h"
#include <vector>
#include <iomanip>

using namespace std;

class clsTransactionsMenuScreen: protected clsScreen
{
private:
    enum enTransactions_menu_options {
            enDeposit = 1, enWithdraw = 2, enTotal_Balances = 3, enExit = 4,
    };
    static short _read_user_choice(short size)
    {
        cout <<setw(37) << left << ""<< "Choose what do you want to do? [1 to "+to_string(size)+"]? ";
        short user_choice = clsInputValidate::read_short_number_between(1,size,"Enter Number between 1 to "+to_string(size)+" ?");
        return user_choice;
    }
    static void _back_to_transactions_menu()
    {
        cout<<"\npress any key to go back to Transaction Menu"<<endl;
        system("pause>0");
        Show_Transactions_main_menu_screen();
    }
    static void _Perfrom_transactions_main_menu_option(enTransactions_menu_options Transaction_Menu_option)
        {
            switch (Transaction_Menu_option)
            {
            case enTransactions_menu_options::enDeposit:
            {
                system("cls");
                clsDepositScreen::Show_deposit_screen();
                _back_to_transactions_menu();
                break;
            }
            case enTransactions_menu_options::enWithdraw:
            {
                system("cls");
                clsWithdrawScreen::Show_withdraw_screen();
                _back_to_transactions_menu();
                break;
            }
            case enTransactions_menu_options::enTotal_Balances:
            {
                system("cls");
                cout<<"total_balances choice"<<endl;
                _back_to_transactions_menu();
                break;
            }
            case enTransactions_menu_options::enExit:
            {
                break;
            }
            }
        }
public:
    static void Show_Transactions_main_menu_screen()
    {
        system("cls");
        _DrawScreenHeader("\t\tTransaction Menu Screen");
        vector <string> choices={"Deposit","Withdraw","Total Balances","Back to main Menu"};
        cout << setw(37) << left <<""<< "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        for (short x=0;x<choices.size();x++)
        {
            cout << setw(37) << left << "" << "\t"<<x+1<<" "<<choices[x]<<".\n";
        }
        cout << setw(37) << left << "" << "===========================================\n";
        _Perfrom_transactions_main_menu_option((enTransactions_menu_options)_read_user_choice(choices.size()));
    } 
};