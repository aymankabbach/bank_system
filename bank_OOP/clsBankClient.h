#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
# include "clsString.h"
#include "clsDate.h"
#include <fstream>
using namespace std;

class clsBankClient : public clsPerson
{
private:
    enum enMode {Empty_Mode=0, Update_Mode=1, AddNew_Mode=2};
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
    static string _get_ID_from_user(string message)
    {
        string ID;
        cout<<message<<endl;
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
    void _update()
    {
        vector <clsBankClient> _vClients=_load_data_from_File();
        for (clsBankClient& C : _vClients)
        {
            if (C.get_ID() == _ID)
            {
                C = *this;
                break;
            }
        }
        _save_data_in_file(_vClients);
    }
    static clsBankClient _get_add_new_client_object(string ID)
    {
        return clsBankClient(enMode::AddNew_Mode,ID,"",0);
    }
    static void _add_client_to_file(clsBankClient client)
    {
        fstream MyFile;
        MyFile.open("clients.txt", ios::app);
        string Line;
        if (MyFile.is_open())
        {
            Line = _convert_client_object_to_Line(client,"////");
            MyFile << Line << endl;
        }  
        MyFile.close();
    }
    static void _delete_client_from_file(vector <clsBankClient> vClients,clsBankClient client)
    {

        fstream MyFile;
        MyFile.open("clients.txt", ios::out);
        string Line;
        if (MyFile.is_open())
        {
            for (clsBankClient clt : vClients)
            {
                if (clt.get_ID() != client.get_ID())
                {
                    Line = _convert_client_object_to_Line(clt,"////");
                    MyFile << Line << endl;
                }
            }  
        }
        MyFile.close();
    }
    static char _confirm_delete()
    {
        char answer;
        cout<<"do you want to delete this client ? (y/n)"<<endl;
        cin>>answer;
        return answer;
    }
    static void _show_details(clsBankClient client)
    {
        cout<<client.get_ID()<<"\t"<<client.get_name()<<"\t"<<client.get_Balance()<<endl;
    }
    static void _get_details(vector <clsBankClient> vClients)
    {
        cout<<"all clients details :\n";
        cout<<"ID\tname\tBalance\n";
        for (clsBankClient client : vClients)
        {
            _show_details(client);
        }
    }
    static void _show_total_balances(vector <clsBankClient> vClients)
    {
        double total_balances=0;
        cout<<"all clients details :\n";
        cout<<"ID\tname\tBalance\n";
        for (clsBankClient client : vClients)
        {
            total_balances+=client.get_Balance();
            _show_details(client);
        }
        cout<<"\ntotal : "<<total_balances<<endl;
    }
    string _convert_record_to_Line(clsBankClient client,float amount)
    {
        string Line;
        Line+=clsDate::get_current_complet_date()+"////";
        Line+=get_ID()+"////";
        Line+=client.get_ID()+"////";
        Line+=to_string(amount)+"////";
        Line+=to_string(get_Balance())+"////";
        Line+=to_string(client.get_Balance())+"////";
        Line+=Current_User.get_username();
        return Line;
    }
    static void _save_transfer(string Line)
    {
        {
        fstream MyFile;
        MyFile.open("transferLog.txt", ios::out | ios::app);
        if (MyFile.is_open())
        {
            MyFile << Line << endl;
        }  
        MyFile.close();
        }
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
    enum enSaveResults {svFailEmptyObject=0 , svSucceeded=1,svFailIdExists=2};
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
            client._update();
            return enSaveResults::svSucceeded;
        }
        case enMode::AddNew_Mode:
        {
            _add_client_to_file(client);
            return enSaveResults::svSucceeded;
        }
        }
    }
    static void update_client_info()
    {
        string ID=_get_ID_from_user("enter client's ID");
        while (!clsBankClient::IsClientExist(ID))
        {
            ID=_get_ID_from_user("enter client's ID");
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
        string ID=_get_ID_from_user("enter client's ID");
        while (IsClientExist(ID))
        {
            cout<<"client's ID already exist"<<endl;
            ID=_get_ID_from_user("enter client's ID");
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
    static void Delete_client()
    {
        string ID=_get_ID_from_user("enter client's ID");
        while (IsClientExist(ID)==false)
        {
            cout<<"client with "+ID+" does not already exist"<<endl;
            ID=_get_ID_from_user("enter client's ID");
        }
        clsBankClient client=Find(ID);
        char answer=_confirm_delete();
        if (answer=='y' || answer=='Y')
        {
            vector <clsBankClient> vClients=_load_data_from_File();
            _delete_client_from_file(vClients,client);
            cout<<"client deleted successfully"<<endl;
        }
        else
        {
            cout<<"error, client was not deleted"<<endl;
        }
    }
    static void show_all_clients()
    {
        vector <clsBankClient> vClients=_load_data_from_File();
        _get_details(vClients);
    }
    static void get_total_balances()
    {
        vector <clsBankClient> vClients=_load_data_from_File();
        _show_total_balances(vClients);
    }
    static vector <clsBankClient> get_Clients_List()
    {
        return _load_data_from_File();
    }
    static string get_ID_from_user(string message)
    {
        return _get_ID_from_user(message);
    }
    static clsBankClient get_add_new_client_object(string ID)
    {
        return _get_add_new_client_object(ID);
    }
    static void update_info(clsBankClient& client)
    {
        client._update_info(client);
    }
    static char confirm_answer()
    {
        return _confirm_delete();
    }
    static vector <clsBankClient> load_data_from_File()
    {
        return _load_data_from_File();
    }
    static void delete_client_from_file(vector <clsBankClient> vClients,clsBankClient client)
    {
        _delete_client_from_file(vClients,client);
    }
    void deposit(short amount)
    {
        _Balance+=amount;
    }
    void withdraw(short amount)
    {
        _Balance-=amount;
    }
    void transfer(float amount, clsBankClient& client)
    {
        client.deposit(amount);
        withdraw(amount);
        clsBankClient::enSaveResults SaveResults1=clsBankClient::save(*this);
        clsBankClient::enSaveResults SaveResults2=clsBankClient::save(client);
        string Line=_convert_record_to_Line(client,amount);
        _save_transfer(Line);
    }
};