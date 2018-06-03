#ifndef FILEUSERS_H
#define FILEUSERS_H

#include <File.h>
#include "User.h"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <windows.h>

class FileUsers : public File
{
    public:
        FileUsers(std::string);
        std::string getFilename();
        bool isFileEmpty();
        void saveUsersToFile(std::vector <User> &users);
        std::vector <User> readUsersFromFile();

    protected:

    private:
        std::string filename;
        std::fstream userData;
        User readOneUserData(std::string&);
};

#endif // FILEUSERS_H
