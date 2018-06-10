#include "User.h"

int User::nextId = 1;

User::User(std::string login, std::string password)
{
    setId(nextId++);
    setLogin(login);
    setPassword(password);
}

User::User(int id, std::string login, std::string password)
{
    setId(id);
    setLogin(login);
    setPassword(password);
    if (id >= nextId)
        nextId = id + 1;
}

std::string User::getLogin()
{
    return login;
}

void User::setLogin(std::string ilogin)
{
    login = ilogin;
}

std::string User::getPassword()
{
    return password;
}

void User::setPassword(std::string ipassword)
{
    password = ipassword;
}

int User::getNextId()
{
    return nextId;
}

void User::setId(int iid)
{
    id = iid;
}

int User::getId()
{
    return id;
}


