#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include "clsString.h"
#include <vector>
#include <iomanip>

using namespace std;

class clsCurrencyCalculatorScreen: protected clsScreen
{
private:
    static clsCurrency _get_currency(string message)
    {
        bool currency_found=false;
        while (currency_found==false)
        {
            string code;
            cout<<message<<"\n";
            cin>>code;
            currency_found=clsCurrency::Is_Currency_Exist(code);
            if (currency_found==false)
            {
                cout<<"currency not found"<<endl;
            }
            else
            {
                return clsCurrency::FindByCode(code);
            }
        }
    }
public:
    static void Show_Currency_calculator_screen()
    {
        _DrawScreenHeader(" Currency Calculator Screen");
        clsCurrency currency1=_get_currency("enter currency's code to convert from");
        clsCurrency currency2=_get_currency("enter currency's code to convert to");
        float amount=clsInputValidate::ReadNumber("invalid, please enter a number");
        if (currency2.get_CurrencyCode()=="USD")
        {
            cout<<amount<<" "<<currency1.get_CurrencyCode()<<" = "<<amount/currency1.get_Rate()<<" "<<currency2.get_CurrencyCode()<<endl;
        }
        else if (currency1.get_CurrencyCode()=="USD")
        {
            float converted_amount=amount*currency2.get_Rate();
            cout<<amount<<" "<<currency1.get_CurrencyCode()<<" = "<<converted_amount<<" "<<currency2.get_CurrencyCode()<<endl;
        }
        else
        {
            clsCurrency currency3=clsCurrency::FindByCode("USD");
            float dollar_amount=amount/currency1.get_Rate();
            float converted_amount=dollar_amount*currency2.get_Rate();
            cout<<amount<<" "<<currency1.get_CurrencyCode()<<" = "<<converted_amount<<" "<<currency2.get_CurrencyCode()<<endl;
        }
    }
};