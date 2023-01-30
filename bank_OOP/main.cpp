#include <iostream>
#include "clsBankClient.h"
using namespace std;

int main()
{
    clsBankClient::Delete_client();
    cout<<"-------"<<endl;
    clsBankClient Client1=clsBankClient::Find("A12");
    Client1.get_info();
    system("pause");
    return 0;
}