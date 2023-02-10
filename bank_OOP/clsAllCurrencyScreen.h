#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include <vector>
#include <iomanip>

using namespace std;

class clsAllCurrencyScreen: protected clsScreen
{
private:
    static void _Print_cureency_record_line(clsCurrency Currency)
    {
        cout << setw(8) << left << "" << "| " << setw(35) << left <<Currency.get_Country();
        cout << "| " << setw(20) << left << Currency.get_CurrencyCode();
        cout << "| " << setw(45) << left << Currency.get_CurrencyName();
        cout << "| " << setw(12) << left << Currency.get_Rate();
    }
public:
    static void Show_Currencies_List()
    {
        vector <clsCurrency> vCurrencies=clsCurrency::Get_Currencies_List();
        string Title = "\t  Currencies List Screen";
        string SubTitle ="\t    (" + to_string(vCurrencies.size()) + ") currencie(s).";
        _DrawScreenHeader(Title,SubTitle);
        cout <<  setw(8) << left << "" << "| " << left << setw(15) << "Country name";
        cout << "| " << left << setw(20) << "Currency Code";
        cout << "| " << left << setw(12) << "Currency name";
        cout << "| " << left << setw(12) << "Rate";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
         if (vCurrencies.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsCurrency Currency : vCurrencies)
            {
                _Print_cureency_record_line(Currency);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};