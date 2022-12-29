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
int main()
{
    create_main_menu();
    system("pause");
    return 0;
}