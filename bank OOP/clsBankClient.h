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
    enum enMode {Empty_Mode=0, Update_Mode=1, AddNew_Mode=2};
    enMode _Mode;
    string _ID;
    double _Balance;
    enum enSaveResults {svFailEmptyObject=0 , svSucceeded=1,svFailIdExists=2};
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
    static void _update_info(clsBankClient& client)
    {
        string name;
        double Balance;
        cout<<"enter the client's name\n";
        cin>>name;
        client.set_name(name);
        cout<<"enter Balance"<<endl;
        cin>>Balance;
        client.set_Balance(Balance);
    }
    static enSaveResults save(clsBankClient client)
    {
        switch(client._Mode)
        {
        case enMode::Empty_Mode:
        {
            return enSaveResults::svFailEmptyObject;
        }
        case enMode::Update_Mode:
        {
            _update(client);
            return enSaveResults::svSucceeded;
        }
        case enMode::AddNew_Mode:
        {
            return enSaveResults::svFailIdExists;
        }
        }
    }
    static string _convert_client_object_to_Line(clsBankClient client,string delim)
    {
        string Line;
        Line+=client.get_ID()+delim;
        Line+=client.get_name()+delim;
        Line+=to_string(client.get_Balance());
        return Line;
    }
    static vector <clsBankClient> _load_data_from_File()
    {
        vector <clsBankClient> vClientsData;
        fstream MyFile;
        MyFile.open("clients.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient client=_convert_line_to_client_object(Line, "////");
                vClientsData.push_back(client);
            }
            MyFile.close();
        } 
        return vClientsData;
    }
    static void _save_data_in_file(vector <clsBankClient> vClients)
    {
        fstream MyFile;
        MyFile.open("clients.txt", ios::out);
        string Line;
        if (MyFile.is_open())
        {
          for (clsBankClient client : vClients)
            {
                Line = _convert_client_object_to_Line(client,"////");
                MyFile << Line << endl;
            }  
        }
        MyFile.close();
    }
    static void _update(clsBankClient client)
    {
        vector <clsBankClient> _vClients;
        _vClients = _load_data_from_File();
        for (clsBankClient& C : _vClients)
        {
            if (C.get_ID() == client.get_ID())
            {
                C = client;
                break;
            }
        }
        _save_data_in_file(_vClients);
    }
    static clsBankClient _get_add_new_client_object(string ID)
    {
        return clsBankClient(enMode::AddNew_Mode,ID,"",0);
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
        while (!clsBankClient::IsClientExist(ID))
        {
            ID=_get_ID_from_user();
        }
        clsBankClient client=clsBankClient::Find(ID);
        client._update_info(client);
        enSaveResults SaveResults=save(client);
        switch (SaveResults)
        { 
            case enSaveResults::svSucceeded:
            {
                cout<<"account was updated successfully\n";
                break;
            }
            case enSaveResults::svFailEmptyObject:
            {
                cout<<"\nError, Account as not saved because it is empty";
                break;
            }
        }
    }
    static void Add_new_client()
    {
        string ID=_get_ID_from_user();
        while (IsClientExist(ID))
        {
            cout<<"client's ID qlready exist"<<endl;
            ID=_get_ID_from_user();
        }
        clsBankClient new_client=_get_add_new_client_object(ID);
        new_client._update_info(new_client);
        enSaveResults SaveResults=save(new_client);
        switch (SaveResults)
        { 
            case enSaveResults::svSucceeded:
            {
                cout<<"account was added successfully\n";
                break;
            }
            case enSaveResults::svFailEmptyObject:
            {
                cout<<"\nError, Account as not saved because it is empty";
                break;
            }
            case enSaveResults::svFailIdExists:
            {
                cout<<"client already exists"<<endl;
                break;
            }
        }
    }
};