#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include <vector>
#include <iomanip>

using namespace std;
class clsUpdateCurrencyScreen: protected clsScreen
{
public:
    static void Show_update_screen()
    {
        _DrawScreenHeader("Update Currency's info screen");
        string code;
        cout<<"enter currency's code ";
        cin>>code;
        bool currency_found=clsCurrency::Is_Currency_Exist(code);
        if (currency_found)
        {
            clsCurrency currency=clsCurrency::FindByCode(code);
            float newRate=clsInputValidate::ReadNumber("invalid , enter a number");
            currency.Update_Rate(newRate);
        }
        else
        {
            cout<<"currency not found"<<endl;
        }
    }
};