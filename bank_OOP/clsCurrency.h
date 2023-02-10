#pragma once
#include<iostream>
#include<string>
#include "clsString.h"
#include <vector>
#include <fstream>
class clsCurrency
{
private:
    enum enMode { EmptyMode = 0, UpdateMode = 1 };
    enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

    static clsCurrency _Convert_Line_to_Currency_Object(string Line, string Seperator = "#//#")
    {
        vector <string> vCurrency_Data;
        vCurrency_Data = clsString::split(Line, Seperator);
        return clsCurrency(enMode::UpdateMode, vCurrency_Data[0], vCurrency_Data[1], vCurrency_Data[2],
            stod(vCurrency_Data[3]));
    }
    static string _Convert_Currency_Object_To_Line(clsCurrency Currency, string Seperator = "#//#")
    {
        string stCurrency_Record = "";
        stCurrency_Record += Currency.Country() + Seperator;
        stCurrency_Record += Currency.CurrencyCode() + Seperator;
        stCurrency_Record += Currency.CurrencyName() + Seperator;
        stCurrency_Record += to_string(Currency.Rate());       
        return stCurrency_Record;
    }
    static  vector <clsCurrency> _Load_Currencies_Data_From_File()
    {
        vector <clsCurrency> vCurrencies;
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _Convert_Line_to_Currency_Object(Line);
                vCurrencies.push_back(Currency);
            }
            MyFile.close();
        }
        return vCurrencies;
    }
    static void _Save_Currency_Data_To_File(vector <clsCurrency> vCurrencies)
    {
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::out);
        string Line;
        if (MyFile.is_open())
        {
            for (clsCurrency C : vCurrencies)
            {
                Line = _Convert_Currency_Object_To_Line(C);
                MyFile << Line << endl;
            }
            MyFile.close();
        }
    }
    void _Update()
    {
        vector <clsCurrency> _vCurrencies;
        _vCurrencies = _Load_Currencies_Data_From_File();
        for (clsCurrency& Currency : _vCurrencies)
        {
            if (Currency.CurrencyCode() == CurrencyCode())
            {
                Currency = *this;
                break;
            }
        }
        _Save_Currency_Data_To_File(_vCurrencies);
    }
    static clsCurrency _Get_Empty_Currency_Object()
    {
        return clsCurrency(enMode::EmptyMode, "", "", "", 0);
    }
public:
	clsCurrency(enMode Mode,string Country,string CurrencyCode,string CurrencyName,float Rate)
	{
        _Mode = Mode;
        _Country = Country;
        _CurrencyCode = CurrencyCode;
        _CurrencyName = CurrencyName;
        _Rate = Rate;
	}

	static vector <clsCurrency> Get_All_USD_Rates()
	{
        return _Load_Currencies_Data_From_File();
	}
    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }
    string Country()
    {
        return _Country;
    }
    string CurrencyCode()
    {
        return _CurrencyCode;
    }
    string CurrencyName()
    {
        return _CurrencyName;
    }
    void Update_Rate(float NewRate)
    {
        _Rate = NewRate;
        _Update();
    }
    float Rate()
    {
        return _Rate;
    }
    static clsCurrency FindByCode(string CurrencyCode)
    {
     
        CurrencyCode = clsString::upper(CurrencyCode);
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _Convert_Line_to_Currency_Object(Line);
                if (Currency.CurrencyCode() == CurrencyCode)
                {
                    MyFile.close();
                    return Currency;
                }
            }
            MyFile.close();
        }
        return _Get_Empty_Currency_Object();
    }
    static clsCurrency Find_By_Country(string Country)
    {
      Country = clsString::upper(Country);
      fstream MyFile;
      MyFile.open("Currencies.txt", ios::in);
      if (MyFile.is_open())
      {
          string Line;
          while (getline(MyFile, Line))
          {
              clsCurrency Currency = _Convert_Line_to_Currency_Object(Line);
              if (clsString::upper(Currency.Country()) == Country)
              {
                  MyFile.close();
                  return Currency;
              }
          }
          MyFile.close();
      }
      return _Get_Empty_Currency_Object();
    }
    static bool Is_Currency_Exist(string CurrencyCode)
    {
        clsCurrency C1 = clsCurrency::FindByCode(CurrencyCode);
        return (!C1.IsEmpty());
    }
    static vector <clsCurrency> Get_Currencies_List()
    {
      return _Load_Currencies_Data_From_File();
    }
};


