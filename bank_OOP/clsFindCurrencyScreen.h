#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include "clsString.h"
#include <vector>
#include <iomanip>

using namespace std;

class clsFindCurrencyScreen: protected clsScreen
{
private:
    enum enChoices {enCode=1,enCountry=2};
    static void _Perfrom_user_choice(enChoices Choice)
    {
        switch (Choice)
        {
        case enChoices::enCode:
        {
            string code;
            cout<<"enter currency's code ";
            cin>>code;
            system("cls");
            _DrawScreenHeader("Find Currency Screen");
            clsCurrency Currency=clsCurrency::FindByCode(code);
            _Print_cureency_record_line(Currency);
            break;
        }
        case enChoices::enCountry:
        { 
            string country;
            cout<<"enter country's name ";
            cin.ignore(1, '\n');
            getline(cin, country);
            system("cls");
            _DrawScreenHeader("Find Currency Screen");
            clsCurrency Currency=clsCurrency::Find_By_Country(country);
            _Print_cureency_record_line(Currency);
            break;
        }
    }
    }
    static void _Print_cureency_record_line(clsCurrency Currency)
    {
        cout << setw(8) << left << "" << "| " << setw(35) << left <<Currency.get_Country();
        cout << "| " << setw(20) << left << Currency.get_CurrencyCode();
        cout << "| " << setw(45) << left << Currency.get_CurrencyName();
        cout << "| " << setw(12) << left << Currency.get_Rate();
    }
public:
    static void Show_Currency()
    {
        _DrawScreenHeader("Find Currency Screen");
        vector <string> vChoices={"Code","Country"};
        cout<<"Find by \n";
        for (short x=0 ; x<vChoices.size();x++)
        {
            cout<<x+1<<"\t"<<vChoices[x]<<endl;
        }
        short answer=clsInputValidate::read_short_number_between(1,vChoices.size(),"invalid");
        _Perfrom_user_choice((enChoices) answer);   
    }
};
