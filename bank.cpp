#include <iostream>
#include <string>
#include <vector>
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
void add_new_client()
{
    cout<<"please, enter client data : \n\n";
    sClient client;
    client=read_new_client_info();
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