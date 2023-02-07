#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsString.h"
#include <vector>
#include <iomanip>

using namespace std;

class clsRegisterLoginScreen: protected clsScreen
{
private:
    static void _Print_user_record(vector <string> vUserRecords)
    {
        cout << setw(8) << left << "" << "| " << setw(35) << left <<vUserRecords[0];
        cout << "| " << setw(20) << left <<vUserRecords[1];
        cout << "| " << setw(20) << left <<vUserRecords[2];
        cout << "| " << setw(10) << left <<vUserRecords[3];
    }
    static vector <string> _get_records()
    {
        vector <string> vLines;
        fstream MyFile;
        MyFile.open("Login_Register.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                vLines.push_back(Line);
            }
            MyFile.close();
        } 
        return vLines;
    }
public:
    static void Show_Register_login_List()
    {
        vector <string> vRecords=_get_records();
        string Title = "\t  Login register List Screen";
        string SubTitle ="\t    (" + to_string(vRecords.size()) + ") user(s).";
        _DrawScreenHeader(Title,SubTitle);
        cout <<  setw(8) << left << "" << "| " << left << setw(15) << "date/time";
        cout << "| " << left << setw(20) << "Username";
        cout << "| " << left << setw(12) << "Password";
        cout << "| " << left << setw(12) <<"Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        if (vRecords.size() == 0)
            cout << "\t\t\t\tNo users Available In the System!";
        else
            for (string record : vRecords)
            {
                vector <string> vUserRecords=clsString::split(record,"////");
                _Print_user_record(vUserRecords);
                cout << endl;
            }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};