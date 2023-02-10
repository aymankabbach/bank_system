#pragma once
#include <iostream>
#include <cctype>
#include <vector>
using namespace std;

class clsString
{
    
private:
    string _value;
public:
    clsString()
    {
        _value="";
    }
    clsString(string value)
    {
        _value=value;
    }
    void set_value(string value)
    {
        _value=value;
    }
    string get_value()
    {
        return _value;
    }
    static short get_number_of_words(string value)
    {
        short words_number=0;
        string delim=" ";
        short pos=0;
        string sword;
        while ((pos = value.find(delim)) != std::string::npos)
        {
            sword=value.substr(0,pos);
            if (sword!="")
            {
                words_number++;
            }
            value.erase(0,pos+delim.length());
        }
        if (value!="")
        {
            words_number++;
        }
        return words_number;
    }
    short get_number_of_words()
    {
        return get_number_of_words(get_value());
    }
    static short get_the_length(string value)
    {
        short length=0;
        for (char letter : value)
        {
            length++;
        }
        return length;
    }
    short get_the_length()
    {
        return get_the_length(get_value());
    }
    void append(string new_value)
    {
        string value=get_value();
        value+=new_value;
        set_value(value);
    }
    void upper_first_letter()
    {
        string value=get_value();
        if (islower(value[0]))
        {
            value[0]-=32;
        }
        set_value(value);
    }
    void lower_first_letter()
    {
        string value=get_value();
        if (isupper(value[0]))
        {
            value[0]+=32;
        }
        set_value(value);
    }
    void reverse_cases()
    {
        string value=get_value();
        for (int x=0; x<value.size();x++)
        {
            if (islower(value[x]))
            {
                value[x]-=32;;
            }
            else if (isupper(value[x]))
            {
                value[x]+=32;
            }
        }
        set_value(value);
    }
    void upper()
    {
        string value=get_value();
        for (int x=0; x<value.size();x++)
        {
            if (islower(value[x]))
            {
                value[x]-=32;;
            }
        }
        set_value(value);   
    }
    static string upper(string value)
    {
        for (int x=0; x<value.size();x++)
        {
            if (islower(value[x]))
            {
                value[x]-=32;;
            }
        }
        return value;
    }
    static string lower(string value)
    {
        for (int x=0; x<value.size();x++)
        {
            if (isupper(value[x]))
            {
                value[x]+=32;;
            }
        }
        return value;
    }
    void lower()
    {
      string value=get_value();
        for (int x=0; x<value.size();x++)
        {
            if (isupper(value[x]))
            {
                value[x]+=32;;
            }
        }
        set_value(value);   
    }
    static vector <string> split(string value,string delim)
    {
        vector <string> vSplit_word;
        string sword;
        short pos=0;
        while ((pos = value.find(delim)) != std::string::npos)
        {
            sword=value.substr(0,pos);
            if (sword!="")
            {
                vSplit_word.push_back(sword);
            }
            value.erase(0,pos+delim.length());
        }
        if (value!="")
        {
            vSplit_word.push_back(value);
        }
        return vSplit_word;
    }
    vector <string> split(string delim)
    {
        return split(get_value(),delim);
    }
    void replace(string world_to_replace, string new_world)
    {
        string value;
        vector <string> vSplited_string=split(" ");
        for (string &str : vSplited_string)
        {
            if (str==world_to_replace)
            {
                str=new_world;
            }
        }
        for (string word : vSplited_string)
        {
            value+=word+" ";
        }
        value.erase(value.length()-1,value.length());
        set_value(value);
    }
};