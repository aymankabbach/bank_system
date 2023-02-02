#pragma once
#include <iostream>
#include <limits>
using namespace std;

class clsInputValidate
{
public:
    static bool is_number_between(int number,int from, int to)
    {
        if (from<number && number<=to)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    static bool is_number_between(double number, double from, double to)
    {
        if (from<number && number<=to)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    static double ReadNumber(string message)
    {
        double number;
        cout<<"enter a number"<<endl;
        cin>>number;
        while (cin.fail())
        {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout<<message<<endl;
        cin>>number;
        }
        return number;
    }
    static short read_short_number_between(short from, short to, string message)
    {
        short number;
        cin>>number;
        while (from>number || number>to)
        {
            cout<<message<<endl;
            cin>>number;
        }
        return number;
    }
    static short Read_short_number(string message)
    {
        short number;
        cin>>number;
        while (cin.fail())
        {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout<<message<<endl;
        cin>>number;
        }
        return number;
    }
};