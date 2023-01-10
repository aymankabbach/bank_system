#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
using namespace std;
struct sClient
{
    string AccountNumber;
    string Name;
    double Balance; 
    bool to_delete=false;
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
    vector <string> choices={"Show Client List","Add new Client","Update Client Info","Find Client","Transations","Delete Client","Exit"};
    show_choices(choices);
}
int read_user_choice()
{
    int number;
    cout<<"what do you want to do ?";
    cin >> number;
    return number;
}
int valid_user_choice(int first_choice,int last_choice)
{
    int choice=read_user_choice();
    while (choice<first_choice || choice>last_choice)
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
    cout<<"add client menu : \n";
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
bool mark_client_to_delete(vector <sClient>& vClients,string Account_number)
{
    for (sClient& client : vClients)
    {
        if (client.AccountNumber==Account_number)
        {
            client.to_delete=true;
            return true;
        }
    } 
    return false;
}
string get_account_number_from_user()
{
    string Account_number;
    cout<<"enter client's number :\n";
    getline(cin>>ws,Account_number);
    return Account_number;
}
void delete_client(vector <sClient> vClients, bool client_found)
{
    if (client_found)
    {
        fstream file;
        file.open("clients.txt",ios::out);
        if (file.is_open())
        {
            for (sClient client : vClients)
            {
                if (client.to_delete==false)
                {
                    string clients_data=convert_client_info_to_line(client,"////");
                    file<<clients_data<<endl;
                }
            }
            file.close();
        }
    }
    else
    {
        cout<<"error , client not found"<<endl;
    }
}
void delete_client_from_file()
{
    cout<<"delete client menu :\n";
    vector <string> vLines;
    vLines=Load_data_from_file();
    vector <sClient> vClients;
    vClients=convert_Line_to_struct(vLines,"////");
    string Account_number;
    Account_number=get_account_number_from_user();
    bool client_found=mark_client_to_delete(vClients,Account_number);
    delete_client(vClients,client_found);
}
bool search_wanted_client(vector <sClient> vClients,string Account_number, sClient& client)
{
    for (sClient& clt : vClients)
    {
        if (clt.AccountNumber==Account_number)
        {
            client=clt;
            return true;
        }
    }
    return false;
}
void print_client_details(bool client_found,sClient client)
{
    if (client_found)
    {
    cout<<"client's details : \n";
    cout<<"Acc Number\tName\tBalance\n";
    cout<<client.AccountNumber<<"\t\t"<<client.Name<<"\t"<<client.Balance<<endl;
    }
    else
    {
        cout<<"error , client not found"<<endl;
    }
}
void find_client()
{
    cout<<"find client menu :\n";
    sClient client;
    vector <string> vLines;
    vLines=Load_data_from_file();
    vector <sClient> vClients;
    vClients=convert_Line_to_struct(vLines,"////");
    string Account_number;
    Account_number=get_account_number_from_user();
    bool client_found=search_wanted_client(vClients,Account_number,client);
    print_client_details(client_found,client);
}
char get_answer()
{
    char answer;
    cout<<"do you want to exit the program ?(y/n)";
    cin>>answer;
    return answer;
}
void confirm_answer(char answer, int &user_choice)
{
    if (answer=='Y' || answer=='y')
    {
        user_choice=6;
    }
    else
    {
        user_choice=0;
    }
}
void exit_program(int &user_choice)
{
    char answer;
    answer=get_answer();
    confirm_answer(answer,user_choice);
}
sClient update_client_info(sClient &client)
{
    cout<<"Enter client' name\n";
    getline(cin >>ws, client.Name);

    cout<<"Enter client's Balance\n";
    cin>>client.Balance;
    return client;
}
vector <string> convert_clients_info_to_line(vector <sClient> vClients, sClient client)
{
    vector <string> Lines;
    for (sClient clt : vClients)
    {
        string Line;
        if (clt.AccountNumber==client.AccountNumber)
        {   
            Line=convert_client_info_to_line(client,"////");
        }
        else
        {
            Line=convert_client_info_to_line(clt,"////");
        }
        Lines.push_back(Line);
    }
    return Lines;
}
void save_in_file(vector <string> Lines)
{
    fstream file;
    file.open("clients.txt",ios::out);
    if (file.is_open())
    {
        for (string Line : Lines)
        {
            file<<Line<<endl;
        }
        file.close();
    }
}
void save_new_data(bool client_found,sClient client,vector <sClient> vClients)
{
    if (client_found)
    {
        client=update_client_info(client);
        vector <string> Lines=convert_clients_info_to_line(vClients,client);
        save_in_file(Lines);
    }
    else
    {
        cout<<"error , client not found"<<endl;
    }
}
void update_client()
{
    cout<<"update client menu :\n";
    sClient client;
    vector <string> vLines;
    vLines=Load_data_from_file();
    vector <sClient> vClients;
    vClients=convert_Line_to_struct(vLines,"////");
    string Account_number;
    Account_number=get_account_number_from_user();
    bool client_found=search_wanted_client(vClients,Account_number,client);
    save_new_data(client_found,client,vClients);
}
void go_to_choice(int user_choice)
{
    enum enChoice{eDeposit=1,
    eWithdraw=2,
    eTotalBalance=3,
    eReturn_to_mainMenu=4};
    switch (user_choice)
    {
    case enChoice::eDeposit:
        system("cls");
        cout<<"Deposit"<<endl;
        break;
    case enChoice::eWithdraw:
        system("cls");
        cout<<"Withdraw"<<endl;
        break;
    case enChoice::eTotalBalance:
        system("cls");
        cout<<"T Balance"<<endl;
        break;
    case enChoice::eReturn_to_mainMenu:
        cout<<"Return to Main Menu"<<endl;
        break;
    }
}
void create_transaction_menu()
{
    cout<<"Transactions Menu :\n";
    vector <string> choices={"Deposit","Withdraw","Total Balances","Main Menu"};
    show_choices(choices);
}
void go_to_transaction_menu()
{
    int user_choice;
    do
    {
        create_transaction_menu();
        user_choice=valid_user_choice(1,4);
        go_to_choice(user_choice);
    }while (user_choice!=4);
}
void execute_the_choice(int &user_choice)
{
    enum enOptions {
    eShowClient=1,
    eAddnewClient=2,
    eUpdateClient=3,
    eFindClient=4,
    eTransactions=5,
    eDeleteClient=6,
    eExit=7};
    switch (user_choice)
    {
    case enOptions::eShowClient:
        system("cls");
        show_all_clients_details();
        cout<<"Enter any key to go back to main menu..."<<endl;
        system("pause>0");
        break;
    case enOptions::eAddnewClient:
        system("cls");
        add_new_client();
        cout<<"Enter any key to go back to main menu..."<<endl;
        system("pause>0");
        break;
    case enOptions::eUpdateClient:
        system("cls");
        update_client();
        cout<<"Enter any key to go back to main menu..."<<endl;
        system("pause>0");
        break;
    case enOptions::eFindClient:
        system("cls");
        find_client();
        cout<<"Enter any key to go back to main menu..."<<endl;
        system("pause>0");
        break;
    case enOptions::eTransactions:
        system("cls");
        go_to_transaction_menu();
        break;
    case enOptions::eDeleteClient:
        system("cls");
        delete_client_from_file();
        cout<<"Enter any key to go back to main menu..."<<endl;
        system("pause>0");
        break;
    case enOptions::eExit:
        exit_program(user_choice);
        break;
    }   
}
void run_program(int &user_choice)
{
    create_main_menu();
    user_choice=valid_user_choice(1,7);
    execute_the_choice(user_choice);
}
int main()
{
    int user_choice;
    do
    {
        system("cls");
        run_program(user_choice);
    }while (user_choice!=6);
    return 0;
}