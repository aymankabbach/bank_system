#include <iostream>
#include "clsLoginScreen.h"
using namespace std;

int main()
{
    while (true)
    {
        if (!clsLoginScreen::show_login_screen())
        {
            break;
        }
    }
    system("pause");
    return 0;
}