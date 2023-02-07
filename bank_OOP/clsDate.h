#pragma once
#include <iostream>
#include <time.h>
#include <vector>
using namespace std;

class clsDate
{
private:
    short _day=1;
    short _month=1;
    short _year=1900;
public:
    clsDate()
    {
        time_t theTime = time(NULL);
        struct tm *aTime = localtime(&theTime);
        short day = aTime->tm_mday;
        short month = aTime->tm_mon + 1;
        short year = aTime->tm_year + 1900;
        _day=day;
        _month=month;
        _year=year;
    }
    clsDate(short day, short month, short year)
    {
        if (0<day && day<=31)
        {
            _day=day;
        }
        if (0<month && month<=12)
        {
            _month=month;
        }
        _year=year;
    }
    clsDate(short days,short year)
    {
        vector <short> Days_in_Months={31,28,31,30,31,30,31,31,30,31,30,31};
        short months=0;
        while (days>0 && days>Days_in_Months[months])
        {
            days-=Days_in_Months[months];
            months++;
        }
        _day=days;
        _month=months+1;
        _year=year;
    }
    clsDate(string date)
    {
        vector <string> vSplit_date;
        string sword;
        string delim="/";
        short pos=0;
        while ((pos = date.find(delim)) != std::string::npos)
        {
            sword=date.substr(0,pos);
            if (sword!="")
            {
                vSplit_date.push_back(sword);
            }
            date.erase(0,pos+delim.length());
        }
        if (date!="")
        {
            vSplit_date.push_back(date);
        }
        _day=stoi(vSplit_date[0]);
        _month=stoi(vSplit_date[1]);
        _year=stoi(vSplit_date[2]);
    }
    void set_day(short day)
    {

        if (0<day && day<=31)
        { 
            _day=day;
        }
        else
        {
            cout<<"day "<<day<<" is invalid"<<endl;
        }
    }
    short get_day()
    {
        return _day;
    }
    void set_month(short month)
    {
        if (0<month && month<=12)
        { 
            _month=month;
        }
        else
        {
            cout<<"month "<<month<<" is invalid"<<endl;
        }
    }
    short get_month()
    {
        return _month;
    }
    void set_year(short year)
    {
        _year=year;
    }
    short get_year()
    {
        return _year;
    }
    void get_date()
    {
        cout<<get_day()<<"/"<<get_month()<<"/"<<get_year()<<endl;
    }
    short getagebydays(short day,short month, short year)
    {
        short days=0;
        vector <short> Days_in_Months={31,28,31,30,31,30,31,31,30,31,30,31};
        time_t theTime = time(NULL);
        struct tm *aTime = localtime(&theTime);
        short current_day = aTime->tm_mday;
        short current_month = aTime->tm_mon + 1;
        short current_year = aTime->tm_year + 1900;
        /* */
        days+=Days_in_Months[month-1]-day;
        for (short x=month ; x<Days_in_Months.size(); x++)
        {
            days+=Days_in_Months[x];

        }
        for (short x=year; x<current_year-1;x++)
        {
            days+=365;
        }
        for (short x=0 ; x<current_month-1; x++)
        {
            days+=Days_in_Months[x];
        }
        days+=current_day;
        return days;
    }
    bool isDateValid()
    {
        short month=get_month();
        short day=get_day();
        vector <short> Days_in_Months={31,28,31,30,31,30,31,31,30,31,30,31};
        if (month<0 || month>12)
        {
            cout<<"month not valid"<<endl;
            return false;
        }
        if (day<0 || day>Days_in_Months[month-1])
        {
            cout<<"day not valid"<<endl;
            return false;
        }
        return true;
    }
    static string get_current_complet_date()
    {
        string Line;
        time_t theTime = time(NULL);
        struct tm *aTime = localtime(&theTime);
        short day = aTime->tm_mday;
        short month = aTime->tm_mon + 1;
        short year = aTime->tm_year + 1900;
        short hour =aTime->tm_hour;
        short minutes=aTime->tm_min;
        short seconds=aTime->tm_sec;
        Line+=to_string(day)+"/"+to_string(month)+"/"+to_string(year);
        Line+=" ";
        Line+=to_string(hour)+":"+to_string(minutes)+":"+to_string(seconds);
        return Line;
    }
    static void get_current_date()
    {
        time_t theTime = time(NULL);
        struct tm *aTime = localtime(&theTime);
        short day = aTime->tm_mday;
        short month = aTime->tm_mon + 1;
        short year = aTime->tm_year + 1900;
        cout<<day<<"/"<<month<<"/"<<year<<endl;
    }
    static short get_current_day()
    {
        time_t theTime = time(NULL);
        struct tm *aTime = localtime(&theTime);
        short day = aTime->tm_mday;
        return day;
    }
    static short get_current_month()
    {
        time_t theTime = time(NULL);
        struct tm *aTime = localtime(&theTime);
        short month=aTime->tm_mon+1;
        return month;
    }
    static short get_current_year()
    {
        time_t theTime = time(NULL);
        struct tm *aTime = localtime(&theTime);
        short year = aTime->tm_year + 1900;
        return year;
    }
};