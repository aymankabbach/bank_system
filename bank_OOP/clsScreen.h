#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsGlobal.h"
#include "clsDate.h"

using namespace std;

class clsScreen
{
protected :
    static void _DrawScreenHeader(string Title,string SubTitle ="")
    {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << "user : "<<Current_User.get_username();
        cout << "\n\n\t\t\t\t\t  " << "date : "<<clsDate::get_current_day()<<"/"<<clsDate::get_current_month()<<"/"
        <<clsDate::get_current_year();
        cout << "\n\t\t\t\t\t______________________________________\n\n";
    }
    static bool Check_Access_Rights(clsUser::enPermissions Permission)
    {
     
            if (!Current_User.Check_Access_Permission(Permission))
            {
                cout << "\t\t\t\t\t______________________________________";
                cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";   
                cout << "\n\t\t\t\t\t______________________________________\n\n";
                return false;
            }
            else
            {
                return true;
            }

    }


};