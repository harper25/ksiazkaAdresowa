#ifndef USERSMANAGER_H
#define USERSMANAGER_H

#include "User.h"
#include "FileUsers.h"
#include <vector>

class UsersManager
{
    public:
        UsersManager(std::string = "userData.txt");
        void registerNewUser();
        void logging();
        void changePassword();
        int getLoggedUserId();
        void setLoggedUserId(int);

    protected:

    private:
        std::vector <User> users;
        FileUsers fileUsers;
        int loggedUserId;
};

#endif // USERSMANAGER_H
