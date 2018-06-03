#include "UsersManager.h"
#include <iostream>
#include <windows.h>
#include <fstream>

UsersManager::UsersManager(std::string ifilename)
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
    std::string login, password;
    int usersCount = users.size();
    system("cls");
    std::cout << "Phone Book --> New Account" << std::endl;
    std::cout << "Please, enter your username: ";
    std::cin.sync();
    getline(std::cin, login);
    int i = 0;
    while (i < usersCount)
    {
        if (users[i].getLogin() == login)
        {
            std::cout << "This username already exists in database! Please, enter another username: ";
            std::cin.sync();
            getline(std::cin, login);
            i = 0;
        }
        else
        {
            i++;
        }
    }
    std::cout << "Please, enter your password: ";
    std::cin.sync();
    getline(std::cin, password);

    User newUser(login, password);
    users.push_back(newUser);
    std::cout << "Account created!" << std::endl;
    fileUsers.saveUsersToFile(users);
    Sleep(1000);
}

void UsersManager::logging()
{
    std::string login, password;
    int usersCount = users.size();

    if (usersCount == 0)
    {
        std::cout << "No users in database! Please, create a new account." << std::endl;
        Sleep(1000);
        return;
    }

    system("cls");
    std::cout << "Phone Book --> Logging" << std::endl;
    std::cout << "Please, give your login: ";
    std::cin.sync();
    getline(std::cin, login);
    int i = 0;
    while(i < usersCount)
    {
        if (users[i].getLogin() == login)
        {
            const int MAX_ATTEMPTS_COUNT = 3;
            for (int attempts = 0; attempts < MAX_ATTEMPTS_COUNT; attempts++)
            {
                std::cout << "Please, give your password. Attempts left: " << MAX_ATTEMPTS_COUNT - attempts << ": ";
                std::cin >> password;
                if (users[i].getPassword() == password)
                {
                    std::cout << "Login and password correct!" << std::endl;
                    Sleep(1000);
                    loggedUserId = users[i].getId();
                    return;
                }
            }
            std::cout << MAX_ATTEMPTS_COUNT << " attempts to log in failed. Wait for 3 seconds before another try." << std::endl;
            Sleep(1000);
            return;
        }
        i++;
    }
    std::cout << "There is no such user!" << std::endl;
    Sleep(1000);
}


void UsersManager::changePassword()
{
    std::string password;
    system("cls");
    std::cout << "Phone Book --> User Menu --> Password change" << std::endl;
    std::cout << "Type in your new password: ";
    std::cin.sync();
    getline(std::cin, password);
    int usersCount = users.size();

    for (int i = 0; i < usersCount; i++)
    {
        if (users[i].getId() == getLoggedUserId())
        {
            users[i].setPassword(password);
            fileUsers.saveUsersToFile(users);
            std::cout << "Password changed!" << std::endl;
            Sleep(1000);
        }
    }
}



