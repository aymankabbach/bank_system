#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsString.h"
#include <vector>
#include <iomanip>

using namespace std;

class clsTransferLogScreen: protected clsScreen
{
private:
    static vector <string> _get_records()
    {
        vector <string> vLines;
        fstream MyFile;
        MyFile.open("transferLog.txt", ios::in);
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
    static void _Print_Transfer_Log_Record_Line(vector <string> record)
    {

        cout << setw(8) << left << "" << "| " << setw(23) << left << record[0];
        cout << "| " << setw(8) << left << record[1];
        cout << "| " << setw(8) << left << record[2];
        cout << "| " << setw(14) << left << record[3];
        cout << "| " << setw(14) << left << record[4];
        cout << "| " << setw(14) << left << record[5];
        cout << "| " << setw(8) << left << record[6];
        cout<<endl;
    }
public:
    static void show_transfer_log_screen()
    {
        vector <string> vLines=_get_records();
        string Title = "\t  Transfers List Screen";
        string SubTitle ="\t    (" + to_string(vLines.size()) + ") Client(s).";
        _DrawScreenHeader(Title,SubTitle);
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
        cout << "| " << left << setw(8) << "sender";
        cout << "| " << left << setw(8) << "receiver";
        cout << "| " << left << setw(14) << "Amount";
        cout << "| " << left << setw(14) << "s.Balance";
        cout << "| " << left << setw(14) << "r.Balance";
        cout << "| " << left << setw(8) << "User";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        if (vLines.size() == 0)
        {
            cout << "\t\t\t\tNo Transfers Available In the System!";
        }
        else
        {
            for (string Line : vLines)
            {
                vector <string> record=clsString::split(Line,"////");
                _Print_Transfer_Log_Record_Line(record);
            }
        }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};