#include "FileUsers.h"
#include <iostream>
#include <windows.h>

FileUsers::FileUsers(std::string ifilename)
{
    filename = ifilename;
}

bool FileUsers::isFileEmpty()
{
    return (userData.peek() == std::ifstream::traits_type::eof());
}

std::string FileUsers::getFilename()
{
    return filename;
}

void FileUsers::saveUsersToFile(std::vector <User> &users)
{
    userData.open(filename, std::ios::out);
    int usersCount = users.size();

    for (int i = 0; i < usersCount; i++)
    {
        userData << users[i].getId() << "|";
        userData << users[i].getLogin() << "|";
        userData << users[i].getPassword() << "|" << std::endl;
    }
    userData.close();
}

User FileUsers::readOneUserData(std::string &line)
{
    std::string sign = "|";
    std::string login, password;
    int id;
    int oldSignPosition = -1;
    int newSignPosition = line.find(sign, 0);
    int numberOfAttribute = 0;
    std::string attribute;

    while(newSignPosition != std::string::npos)
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


std::vector <User> FileUsers::readUsersFromFile()
{
    std::vector <User> users;
    std::string line;

    userData.open(filename, std::ios::in);

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



