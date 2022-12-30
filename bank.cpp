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
    cout<<"please, enter client data : \n\n";
    sClient client;
    client=read_new_client_info();
    string line;
    line=convert_client_info_to_line(client,"////");
    add_data_to_file(line);
}
void go_to_choice(int user_choice)
{
    if (user_choice==2)
    {
        add_new_client();
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