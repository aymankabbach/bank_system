#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
# include "clsString.h"
#include <fstream>
using namespace std;

class clsBankClient : public clsPerson
{
private:
    enum enMode {Empty_Mode=0, Update_Mode=1};
    enMode _Mode;
    string _ID;
    double _Balance;

    static clsBankClient _convert_line_to_client_object(string Line,string delim)
    {
        vector <string> vClient_Data;
        vClient_Data=clsString::split(Line,delim);
        return clsBankClient(enMode::Update_Mode,vClient_Data[0],vClient_Data[1],stod(vClient_Data[2]));
    }
    static clsBankClient _Get_Empty_client_object()
    {
        return clsBankClient(enMode::Empty_Mode,"","",0);
    }
    static string _get_ID_from_user()
    {
        string ID;
        cout<<"enter client's ID"<<endl;
        cin>>ID;
        return ID;
    }

public:
    clsBankClient(enMode Mode,string ID,string Name,double Balance) : clsPerson(Name)
    {
        _Mode=Mode;
        _ID=ID;
        _Balance=Balance;
    };
    bool Is_Empty()
    {
        return (_Mode == enMode::Empty_Mode);
    }
    string get_ID()
    {
        return _ID;
    }
    void set_Balance(double Balance)
    {
        _Balance=Balance;
    }
    double get_Balance()
    {
        return _Balance;
    }
    void get_info()
    {
        cout<<"Client Info \n";
        cout<<"\n";
        cout<<"ID : "<<get_ID()<<"\n";
        cout<<"Name : "<<get_name()<<"\n";
        cout<<"Balance : "<<get_Balance();
        cout<<endl;
    }
    static clsBankClient Find(string ID)
    {
        fstream MyFile;
        MyFile.open("clients.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient client=_convert_line_to_client_object(Line, "////");
                if (client.get_ID()==ID)
                {
                    MyFile.close();
                    return client;
                }
            }
            MyFile.close();
        } 
        return _Get_Empty_client_object();
    }
    static bool IsClientExist(string ID)
    {

        clsBankClient Client = clsBankClient::Find(ID);
        return (!Client.Is_Empty());
    }
    static void update_client_info()
    {
        string ID=_get_ID_from_user();
        clsBankClient client=clsBankClient::Find(ID);
    }
};