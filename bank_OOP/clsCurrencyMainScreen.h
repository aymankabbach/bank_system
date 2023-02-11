#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsAllCurrencyScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyScreen.h"
#include "clsCurrencyCalculatorScreen.h"
#include "clsInputValidate.h"
#include <vector>
#include <iomanip>

using namespace std;

class clsCurrencyMenuScreen: protected clsScreen
{ 
private:
    enum enCurrency_menu_options {enall=1,enFind=2,enUpdate=3,enExchange=4,enExit=5
    };
    static short _read_user_choice(short size)
    {
        cout <<setw(37) << left << ""<< "Choose what do you want to do? [1 to "+to_string(size)+"]? ";
        short user_choice = clsInputValidate::read_short_number_between(1,size,"Enter Number between 1 to "+to_string(size)+" ?");
        return user_choice;
    }
    static void _back_to_Currency_menu()
    {
        cout<<"\npress any key to go back to Transaction Menu"<<endl;
        system("pause>0");
        Show_Currency_main_menu_screen();
    }
    static void _Perfrom_Currency_main_menu_option(enCurrency_menu_options Currency_menu_option)
        {
            switch (Currency_menu_option)
            {
            case enCurrency_menu_options::enall:
            {
                system("cls");
                clsAllCurrencyScreen::Show_Currencies_List();
                _back_to_Currency_menu();
                break;
            }
            case enCurrency_menu_options::enFind:
            {
                system("cls");
                clsFindCurrencyScreen::Show_Currency();
                _back_to_Currency_menu();
                break;
            }
            case enCurrency_menu_options::enUpdate:
            {
                system("cls");
                clsUpdateCurrencyScreen::Show_update_screen();
                _back_to_Currency_menu();
                break;
            }
            case enCurrency_menu_options::enExchange:
            {
                system("cls");
                clsCurrencyCalculatorScreen::Show_Currency_calculator_screen();
                _back_to_Currency_menu();
                break;
            }
            case enCurrency_menu_options::enExit:
            {
                system("cls");
                break;
            }
            }
        }                
public:
    static void Show_Currency_main_menu_screen()
    {
        system("cls");
        _DrawScreenHeader("\t\tCurrrency Exchange Menu Screen");
        cout << setw(37) << left <<""<< "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        vector <string> choices={"Show all currencies","Find currency","Update rate",
        "currency calculator","Main Menu"};
        for (short x=0;x<choices.size();x++)
        {
            cout << setw(37) << left << "" << "\t"<<x+1<<" "<<choices[x]<<".\n";
        }
        cout << setw(37) << left << "" << "===========================================\n";
        _Perfrom_Currency_main_menu_option((enCurrency_menu_options)_read_user_choice(choices.size()));
    }
};