#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
struct sClient
{
    string AccountNumber;
    string Name;
    double Balance; 
};
void show_choices(vector <string> choices)
{
    for (int x=0;x<choices.size();x++)
    {
    cout<<x+1<<" "<<choices[x]<<"\n";
    }
    cout<<"-----------";
    cout<<endl;
}
void create_main_menu()
{
    cout<<"Main Menu :\n";
    vector <string> choices={"Show Client List","Add new Client","Update Client Info","Delete Client","Find Client","Exit"};
    show_choices(choices);
}
int read_user_choice()
{
    int number;
    cout<<"what do you want to do ?";
    cin >> number;
    return number;
}
int valid_user_choice()
{
    int choice=read_user_choice();
    while (choice<1 || choice>6)
    {
        cout<<"error, please choose an option between 1 and 6\n";
        choice=read_user_choice();
    }
    return choice;
}
sClient read_new_client_info()
{
    sClient client;

    cout<< "Enter Account Number ?";
    getline(cin >> ws, client.AccountNumber);

    cout<< "Enter Name ?";
    getline(cin, client.Name);

    cout<< "Enter Balance ?";
    cin>>client.Balance;
    
    return client;
}
string convert_client_info_to_line(sClient client, string seperator)
{
    string line="";
    line+=client.AccountNumber+seperator;
    line+=client.Name+seperator;
    line+=to_string(client.Balance);
    return line;
}
void add_data_to_file(string line)
{
    fstream file;
    file.open("clients.txt",ios::out | ios::app);
    if (file.is_open())
    {
        file<<line<<endl;
        file.close();
    }
    
}
void add_new_client()
{
    cout<<"please, enter client infos : \n\n";
    sClient client;
    client=read_new_client_info();
    string line;
    line=convert_client_info_to_line(client,"////");
    add_data_to_file(line);
}
vector <string> Load_data_from_file()
{
    vector <string> vClients;
    fstream file;
    file.open("clients.txt", ios::in);
    if (file.is_open())
    {
        string Line;
        while (getline(file,Line))
        {
            vClients.push_back(Line);
        }
        file.close();
    }
    return vClients;
}
vector <string> SplitString(string Line, string seperator)
{
    vector <string> vString;
    string Info;
    short pos=0;
    while ((pos=Line.find(seperator)) != std::string::npos)
    {
        Info=Line.substr(0,pos);
        if (Info != "")
        {
            vString.push_back(Info);
        }
        Line.erase(0,pos+seperator.length());
    }
    if (Line!="")
    {
        vString.push_back(Line);
    }
    return vString;
}
vector <sClient> convert_Line_to_struct(vector<string>vLines,string seperator)
{
    vector <sClient> vClients;
    sClient Client;
    vector <string> vClientData;
    for (string Line : vLines)
    {
        vClientData=SplitString(Line,seperator);
        Client.AccountNumber=vClientData[0];
        Client.Name=vClientData[1];
        Client.Balance=stod(vClientData[2]);
        vClients.push_back(Client);
    }
    return vClients;
}
void print_clients_details(vector <sClient> vClients)
{
    cout<<"all clients details : \n";
    cout<<"Acc Number\tName\tBalance\n";
    for (sClient Client : vClients)
    {
        cout<<Client.AccountNumber<<"\t\t"<<Client.Name<<"\t"<<Client.Balance<<endl;
    }
}
void show_all_clients_details()
{
    vector <string> vLines;
    vLines=Load_data_from_file();
    vector <sClient> vClients;
    vClients=convert_Line_to_struct(vLines,"////");
    print_clients_details(vClients);
}
void go_to_choice(int user_choice)
{
    switch (user_choice)
    {
    case 1:
        show_all_clients_details();
        break;
    case 2:
        add_new_client();
        break;
    }   
}
int main()
{
    create_main_menu();
    int user_choice=valid_user_choice();
    go_to_choice(user_choice);
    system("pause");
    return 0;
}