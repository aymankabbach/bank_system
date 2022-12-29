#include <iostream>
#include <string>
#include <vector>
using namespace std;
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
int main()
{
    create_main_menu();
    int user_choice=valid_user_choice();
    cout<<user_choice<<endl;
    system("pause");
    return 0;
}