#include "User.h"
using namespace std;

int User::nextId = 1;

User::User(string login, string password)
{
    setId(nextId++);
    setLogin(login);
    setPassword(password);
}

User::User(int id, string login, string password)
{
    setId(id);
    setLogin(login);
    setPassword(password);
    if (id >= nextId)
        nextId = id + 1;
}

string User::getLogin()
{
    return login;
}

void User::setLogin(string ilogin)
{
    login = ilogin;
}

string User::getPassword()
{
    return password;
}

void User::setPassword(string ipassword)
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


