#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsInputValidate.h"
#include <fstream>

using namespace std;

class clsUser : public clsPerson
{
private:
    enum enMode {Empty_Mode=0, Update_Mode=1, Add_New_Mode=2};
    enMode _Mode;
    string _Username;
    string _Password;
    bool _Marked_For_Delete = false;
    int _Permissions;
    static clsUser _Convert_Line_to_User_Object(string Line, string Seperator = "////")
    {
        vector<string> vUserData;
        vUserData = clsString::split(Line, Seperator);
        return clsUser(enMode::Update_Mode,vUserData[0],vUserData[1],vUserData[2],stoi(vUserData[3]));
    }
    static clsUser _Get_Empty_User_Object()
    {
        return clsUser(enMode::Empty_Mode, "", "", "",0);
    }
    static string _Convert_User_Object_To_Line(clsUser User, string Seperator = "////")
    {

        string Line = "";
        Line += User.get_name() + Seperator;
        Line += User.get_username() + Seperator;
        Line += User.get_Password() + Seperator;
        Line += to_string(User.get_Permissions());
        return Line;

    }
    static  vector <clsUser> _Load_Users_Data_From_File()
    {
        vector <clsUser> vUsers;
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _Convert_Line_to_User_Object(Line);
                vUsers.push_back(User);
            }
            MyFile.close();
        }
        return vUsers;
    }
    static void _Save_Users_Data_To_File(vector <clsUser> vUsers)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out);
        string Line;
        if (MyFile.is_open())
        {
            for (clsUser User : vUsers)
            {
                if (User._Marked_For_Delete == false)
                { 
                    Line = _Convert_User_Object_To_Line(User);
                    MyFile << Line << endl;
                }
            }
            MyFile.close();
        }
    }
    void _AddNew()
    {
        _Add_Data_Line_To_File(_Convert_User_Object_To_Line(*this));
    }
    void _Add_Data_Line_To_File(string  Line)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::app);
        if (MyFile.is_open())
        {
            MyFile << Line << endl;
            MyFile.close();
        }
    }
    void _get_info()
    {
        string name;
        cout<<"enter user's name"<<endl;
        cin>>name;
        string Password;
        cout<<"enter user's password"<<endl;
        cin>>Password;
        set_name(name);
        set_Password(Password);
    }
    void _Update()
    {
        vector <clsUser> _vUsers;
        _vUsers = _Load_Users_Data_From_File();
        for (clsUser& User : _vUsers)
        {
            if (User.get_username() == _Username)
            {
                User = *this;
                break;
            }
        }
        _Save_Users_Data_To_File(_vUsers);

    }
    static string _get_username_from_user()
    {
        string Username;
        cout<<"enter user's username"<<endl;
        cin>>Username;
        return Username;
    }
    static char _confirm_delete()
    {
        char answer;
        cout<<"do you want to delete this client ? (y/n)"<<endl;
        cin>>answer;
        return answer;
    }
public:
    enum enPermissions {
        eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64
    };
    clsUser(enMode Mode,string Name,string Username,string Password,int Permissions) : clsPerson(Name)
    {
        _Mode=Mode;
        _Username=Username;
        _Password=Password;
        _Permissions=Permissions;
    };
    bool Is_Empty()
    {
        return (_Mode == enMode::Empty_Mode);
    }
    void set_Username(string Username)
    {
        _Username=Username;
    }
    string get_username()
    {
        return _Username;
    }
    void set_Password(string Password)
    {
        _Password=Password;
    }
    string get_Password()
    {
        return _Password;
    }
    void set_Permissions(int Permission)
    {
        _Permissions=Permission;
    }
    int get_Permissions()
    {
        return _Permissions;
    }
    bool IsEmpty()
    {
        return (_Mode == enMode::Empty_Mode);
    }
    bool get_Marked_For_Deleted()
    {
        return _Marked_For_Delete;
    }
    bool Delete()
    {
        vector <clsUser> vUsers;
        vUsers = _Load_Users_Data_From_File();
        for (clsUser& User : vUsers)
        {
            if (User.get_username() == _Username)
            {
                User._Marked_For_Delete = true;
                break;
            }
        }
        _Save_Users_Data_To_File(vUsers);
        *this = _Get_Empty_User_Object();
        return true;
    }
    static bool IsUserExist(string UserName)
    {
        
        clsUser User = clsUser::Find(UserName);
        return (!User.IsEmpty());
    }
    static clsUser Find(string UserName)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User =  _Convert_Line_to_User_Object(Line);
                if (User.get_username() == UserName)
                {
                    MyFile.close();
                    return User;
                }
            }
            MyFile.close();
        }
        return _Get_Empty_User_Object();
    }
    static clsUser Find(string UserName, string Password)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _Convert_Line_to_User_Object(Line);
                if (User.get_username() == UserName && User.get_Password() == Password)
                {
                    MyFile.close();
                    return User;
                }
            }
            MyFile.close();
        }
        return _Get_Empty_User_Object();
    }
    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };
    enSaveResults Save()
    {
        switch (_Mode)
        {
        case enMode::Empty_Mode:
        {
            if (IsEmpty())
            {
                return enSaveResults::svFaildEmptyObject;
            }
        }
        case enMode::Update_Mode:
        {
            _Update();
            return enSaveResults::svSucceeded;
            break;
        }
        case enMode::Add_New_Mode:
        {
            _AddNew();
            _Mode = enMode::Update_Mode;
            return enSaveResults::svSucceeded;
            break;
        }
        }
    }
    static clsUser Get_Add_New_User_Object(string UserName)
    {
        return clsUser(enMode::Add_New_Mode, "",UserName, "", 0);
    }
    static vector <clsUser> Get_Users_List()
    {
        return _Load_Users_Data_From_File();
    }
    static string get_username_from_user()
    {
        return _get_username_from_user();
    }
    void get_info()
    {
        _get_info();
    }
    static char confirm_answer()
    {
        return _confirm_delete();
    }
};