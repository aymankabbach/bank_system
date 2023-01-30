#include <iostream>
#include "clsBankClient.h"
using namespace std;

int main()
{
    clsBankClient::Add_new_client();
    cout<<"-------"<<endl;
    clsBankClient Client1=clsBankClient::Find("A13");
    Client1.get_info();
    system("pause");
    return 0;
}