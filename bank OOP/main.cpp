#include <iostream>
#include "clsBankClient.h"
using namespace std;

int main()
{
    clsBankClient Client1=clsBankClient::Find("A10");
    Client1.get_info();
    clsBankClient::update_client_info();
    cout<<"-------"<<endl;
    Client1.get_info();
    system("pause");
    return 0;
}