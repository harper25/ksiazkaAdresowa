#include "UsersManager.h"
#include <iostream>
#include <windows.h>
#include <fstream>
using namespace std;

UsersManager::UsersManager(string ifilename)
: fileUsers(ifilename)
{
    setLoggedUserId(0);
    users = fileUsers.readUsersFromFile();
}

void UsersManager::setLoggedUserId(int id)
{
    loggedUserId = id;
}

int UsersManager::getLoggedUserId()
{
    return loggedUserId;
}

void UsersManager::registerNewUser()
{
    string login, password;
    int usersCount = users.size();
    system("cls");
    cout << "Phone Book --> New Account" << endl << endl;
    cout << "Please, enter your username: ";
    cin.sync();
    getline(cin, login);
    int i = 0;
    while (i < usersCount)
    {
        if (users[i].getLogin() == login)
        {
            cout << "This username already exists in database! Please, enter another username: ";
            cin.sync();
            getline(cin, login);
            i = 0;
        }
        else
        {
            i++;
        }
    }
    cout << "Please, enter your password: ";
    cin.sync();
    getline(cin, password);

    User newUser(login, password);
    users.push_back(newUser);
    cout << "Account created!" << endl;
    fileUsers.saveUsersToFile(users);
    Sleep(1000);
}

void UsersManager::logging()
{
    string login, password;
    int usersCount = users.size();

    if (usersCount == 0)
    {
        cout << "No users in database! Please, create a new account." << endl;
        Sleep(1000);
        return;
    }

    system("cls");
    cout << "Phone Book --> Logging" << endl << endl;
    cout << "Please, give your login: ";
    cin.sync();
    getline(cin, login);
    int i = 0;
    while(i < usersCount)
    {
        if (users[i].getLogin() == login)
        {
            const int MAX_ATTEMPTS_COUNT = 3;
            for (int attempts = 0; attempts < MAX_ATTEMPTS_COUNT; attempts++)
            {
                cout << "Please, give your password. Attempts left: " << MAX_ATTEMPTS_COUNT - attempts << ": ";
                cin >> password;
                if (users[i].getPassword() == password)
                {
                    loggedUserId = users[i].getId();
                    cout << "Login and password correct!" << endl;
                    Sleep(1000);
                    return;
                }
            }
            cout << MAX_ATTEMPTS_COUNT << " attempts to log in failed. Wait for 3 seconds before another try." << endl;
            Sleep(1000);
            return;
        }
        i++;
    }
    cout << "There is no such user!" << endl;
    Sleep(1000);
}


void UsersManager::changePassword()
{
    string password;
    system("cls");
    cout << "Phone Book --> User Menu --> Password change" << endl << endl;
    cout << "Type in your new password: ";
    cin.sync();
    getline(cin, password);
    int usersCount = users.size();

    for (int i = 0; i < usersCount; i++)
    {
        if (users[i].getId() == getLoggedUserId())
        {
            users[i].setPassword(password);
            fileUsers.saveUsersToFile(users);
            cout << "Password changed!" << endl;
            Sleep(1000);
        }
    }
}



