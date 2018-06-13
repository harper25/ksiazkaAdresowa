#include "FileUsers.h"
#include <iostream>
#include <windows.h>
using namespace std;

FileUsers::FileUsers(string ifilename)
{
    filename = ifilename;
}

bool FileUsers::isFileEmpty()
{
    return (userData.peek() == ifstream::traits_type::eof());
}

string FileUsers::getFilename()
{
    return filename;
}

void FileUsers::saveUsersToFile(vector <User> &users)
{
    userData.open(filename, ios::out);
    int usersCount = users.size();

    for (int i = 0; i < usersCount; i++)
    {
        userData << users[i].getId() << "|";
        userData << users[i].getLogin() << "|";
        userData << users[i].getPassword() << "|" << endl;
    }
    userData.close();
}

User FileUsers::readOneUserData(string &line)
{
    string sign = "|";
    string login, password;
    int id;
    int oldSignPosition = -1;
    int newSignPosition = line.find(sign, 0);
    int numberOfAttribute = 0;
    string attribute;

    while(newSignPosition != string::npos)
    {
        numberOfAttribute++;
        attribute = line.substr(oldSignPosition + 1, newSignPosition - oldSignPosition - 1);

        switch(numberOfAttribute)
        {
        case 1:
            id = conversion.string2int(attribute);
            break;
        case 2:
            login = attribute;
            break;
        case 3:
            password = attribute;
            break;
        }
        oldSignPosition = newSignPosition;
        newSignPosition = line.find(sign,oldSignPosition+1);
    }

    User newUser(id, login, password);
    return newUser;
}


vector <User> FileUsers::readUsersFromFile()
{
    vector <User> users;
    string line;

    userData.open(filename, ios::in);

    if (!isFileEmpty())
    {
        while(getline(userData, line))
        {
            User newUser = readOneUserData(line);
            users.push_back(newUser);
        }
    }
    userData.close();
    return users;
}



