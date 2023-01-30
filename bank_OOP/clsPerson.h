#pragma once
#include <iostream>

using namespace std;

class clsPerson
{
private:
    string _Name;
public:
    clsPerson(string Name)
    {
        _Name=Name;
    }
    void set_name(string Name)
    {
        _Name=Name;
    }
    string get_name()
    {
        return _Name;
    }
    void get_info()
    {
        cout<<"Client Info \n";
        cout<<"\n";
        cout<<"Name : "<<get_name();
        cout<<endl;
    }
};