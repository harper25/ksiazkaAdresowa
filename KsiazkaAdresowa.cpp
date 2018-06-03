#include <iostream>
#include <windows.h>
//#include <conio.h>
#include <fstream>
//#include <cstdlib>
#include <vector>
//#include <algorithm>
#include "User.h"
#include "UsersManager.h"
#include "File.h"
#include "FileUsers.h"

using namespace std;

void showWelcomeMenu()
{
    system("cls");
    cout << "Phone Book" << endl;
    cout << "1. Create a new account" << endl;
    cout << "2. Log in" << endl;
    cout << "9. Exit" << endl << endl;
}

void showUserMenu()
{
    system("cls");
    cout << "Phone Book --> User Menu: " << endl;
    cout << "1. " << endl;
    cout << "2. " << endl;
    cout << "3. " << endl;
    cout << "4. " << endl;
    cout << "5. " << endl;
    cout << "6. " << endl;
    cout << "7. Change password" << endl;
    cout << "8. Log out" << endl << endl;
}


int main()
{
    UsersManager usersManager;
    char choice;

    while(1)
    {
        if (usersManager.getLoggedUserId() == 0)
        {
            showWelcomeMenu();
            cout << "Your choice: ";
            cin >> choice;

            switch (choice)
            {
            case '1':
                usersManager.registerNewUser();
                break;
            case '2':
                usersManager.logging();
                break;
            case '9':
                system("cls");
                cout << "Good bye!" << endl;
                exit(0);
            default:
                cout << "Invalid choice!" << endl;
                Sleep(1000);
            }
        }
        else
        {
            showUserMenu();
            cout << "Your choice: ";
            cin >> choice;

            switch (choice)
            {
            case '1':
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break;
            case '5':
                break;
            case '6':
                break;
            case '7':
                usersManager.changePassword();
                break;
            case '8':
                usersManager.setLoggedUserId(0);
                break;
            default:
                continue;
            }
        }
    }
}
